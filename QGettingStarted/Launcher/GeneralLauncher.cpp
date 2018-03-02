#include <QStringList>
#include <QSharedPointer>

#include "GeneralLauncher.h"

GeneralLauncher::GeneralLauncher(const QString version, QGSGameDirectory & gameDirectory) :QGSILauncher(version, gameDirectory)
{
}

GeneralLauncher::~GeneralLauncher()
{
}

GeneralLauncher::Error GeneralLauncher::generateLaunchCommand(const QGSLaunchOptions * launchOptions, QString & command)
{
	QStringList listLaunchCommand;//launchCommand

	if (!launchOptions)
	{
		return Error::POINTER_IS_NULL;
	}

	auto rootVersionId{ mVersion };
	//��ȡ���汾
	while (!mGameDirectory.getVersion(rootVersionId).getInheritsFrom().isEmpty())
	{
		rootVersionId = mGameDirectory.getVersion(rootVersionId).getInheritsFrom();
	}
	auto & rootVersion{ mGameDirectory.getVersion(rootVersionId) };
	//���汾Jar�ļ�
	QSharedPointer<QFile> fileRootVersionJar{ mGameDirectory.getVersionJarFile(rootVersionId) };
	if (!fileRootVersionJar->exists())
	{
		return Error::JAR_FILE_NOT_FOUND;
	}
	//ǰ��ָ��
	const auto && wrapper{ launchOptions->getWrapper() };
	if (!wrapper.isEmpty())
	{
		listLaunchCommand.append(wrapper);
	}
	//Java·��
	const auto && JavaPath{ launchOptions->getJavaPath() };
	if (JavaPath.isEmpty())
	{
		return Error::JAVA_PATH_NOT_INCLUDED;
	}
	listLaunchCommand.append(QString{ "\"%1\"" }.arg(JavaPath));
	//JVM���������
	if (launchOptions->getGeneratedJVMArguments())
	{
		//�Զ���JVM���������
		const auto && JVMArguments{ launchOptions->getJVMArguments() };
		if (!JVMArguments.isEmpty())
		{
			listLaunchCommand.append(JVMArguments);
		}
		
		listLaunchCommand.append(QString("\"-Dminecraft.client.jar=%1\"").
			arg(fileRootVersionJar->fileName()));
		//����ڴ棨MB��
		listLaunchCommand.append(QString("-Xmx%1m").arg(launchOptions->getMaxMemory()));
		//��С�ڴ棨MB��
		listLaunchCommand.append(QString("-Xmn%1m").arg(launchOptions->getMinMemory()));
		//�ڴ����ñ�������MB��
		if (launchOptions->getMetaspaceSize() > 0)
		{
			listLaunchCommand.append(QString("-XX:PermSize=%1m").arg(launchOptions->getMetaspaceSize()));
		}
		//-Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true
		listLaunchCommand.append("-Dfml.ignoreInvalidMinecraftCertificates=true");
		listLaunchCommand.append("-Dfml.ignorePatchDiscrepancies=true");
	}
	//�°�json����"arguments"����
	auto && arguments{ rootVersion.getArguments() };
	auto && listJVM{ arguments.getJVM() };
	if (!listJVM.isEmpty())
	{
		for (auto & i : listJVM)
		{
			if (isRulesAllowing(i.getRules()))
			{
				listLaunchCommand.append(i.getValue());
			}
		}
	}
	else
	{
		listLaunchCommand.append("-Djava.library.path=${natives_directory}");
		listLaunchCommand.append("-Dminecraft.launcher.brand=${launcher_name}");
		listLaunchCommand.append("-Dminecraft.launcher.version=${launcher_version}");
		listLaunchCommand.append("-cp");
		listLaunchCommand.append("${classpath}");
	}
	//nativesĿ¼
	auto && nativesDirectory{
		QString{ "\"%1\"" }.arg(mGameDirectory.getNativesDirectory(mVersion).absolutePath()) };
	//launcherName
	const QString launcherName{ "\"QGettingStarted\"" };
	//launcherVersion
	const QString launcherVersion{ "\"Beta 1.0.0\"" };
	//libraries
	auto inheritsVersionId{ mVersion };
	QStringList listLibraryPaths;
	do
	{
		auto & version{ mGameDirectory.getVersion(inheritsVersionId) };
		auto && listLibraries{ version.getLibraries() };

		for (auto & i : listLibraries)
		{
			if (!isRulesAllowing(i.getRules()) || i.getNative())
			{
				continue;
			}
			QSharedPointer<QFile> fileLibrary{ mGameDirectory.getLibraryFile(i) };
			auto && libraryPath{ fileLibrary->fileName() };
			listLibraryPaths.append(libraryPath);
		}

		QSharedPointer<QFile> fileInheritsVersionJar{ mGameDirectory.getVersionJarFile(inheritsVersionId) };
		listLibraryPaths.append(fileInheritsVersionJar->fileName());//�汾".jar"�ļ�
	} while (!(inheritsVersionId = mGameDirectory.getVersion(inheritsVersionId).getInheritsFrom()).isEmpty());
	//mainClass
	listLaunchCommand.append(mGameDirectory.getVersion(mVersion).getMainClass());
	//minecraftArguments
	auto && game{ arguments.getGame() };
	QString minecraftArguments;
	if (!game.isEmpty())
	{
		QStringList listArguments;
		for (auto & i : game)
		{
			if (isRulesAllowing(i.getRules()))
			{
				//�޳�--demo
				if (i.getValue().contains("--demo"))
				{
					continue;
				}
				listArguments.append(i.getValue());
			}
		}
		minecraftArguments = listArguments.join(" ");
	}
	else
	{
		minecraftArguments = mGameDirectory.getVersion(mVersion).getMinecraftArguments();
	}
	auto && authInfo{ launchOptions->getAuthInfo() };
	minecraftArguments.replace("${auth_player_name}", authInfo.getSelectedProfile().getName())
		.replace("${version_name}", mVersion)
		.replace("${game_directory}", QString{ "\"%1\"" }.arg(mGameDirectory.getBaseDir().absolutePath()))
		.replace("${assets_root}",
			QString{ "\"%1\"" }.arg(mGameDirectory.getAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath()))
		.replace("${assets_index_name}", rootVersion.getAssetIndex().getId())
		.replace("${auth_uuid}", authInfo.getSelectedProfile().getId())
		.replace("${auth_access_token}", authInfo.getAccessToken())
		.replace("${user_type}", authInfo.getUserType())
		.replace("${version_type}", "\"QGettingStarted\"")
		.replace("${user_properties}", "{}")
		.replace("${auth_session}", authInfo.getAccessToken())
		.replace("${game_assets}",
			QString{ "\"%1\"" }.arg(mGameDirectory.getAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath()))
		.replace("${profile_name}", "Minecraft");
	listLaunchCommand.append(minecraftArguments);
	//��������
	//���ڴ�С
	auto && windowSize{ launchOptions->getWindowSize() };
	if (!windowSize.isEmpty())
	{
		listLaunchCommand.append(QString("--height %1").arg(windowSize.height()));
		listLaunchCommand.append(QString("--width %1").arg(windowSize.width()));
	}
	//ֱ��������
	auto && serverInfo{ launchOptions->getServerInfo() };
	if (!serverInfo.address.isEmpty() && !serverInfo.port.isEmpty())
	{
		listLaunchCommand.append(QString("--server %1").arg(serverInfo.address));
		listLaunchCommand.append(QString("--port %1").arg(serverInfo.port));
	}
	//����
	auto && proxyInfo{ launchOptions->getProxyInfo() };
	if (!proxyInfo.address.isEmpty() && !proxyInfo.port.isEmpty())
	{
		listLaunchCommand.append(QString("--proxyHost %1").arg(proxyInfo.address));
		listLaunchCommand.append(QString("--proxyPort %1").arg(proxyInfo.port));
		if (!proxyInfo.user.isEmpty() && !proxyInfo.password.isEmpty())
		{
			listLaunchCommand.append(QString("--proxyUser %1").arg(proxyInfo.user));
			listLaunchCommand.append(QString("--proxyPass %1").arg(proxyInfo.password));
		}
	}
	//��Ϸ�������
	auto gameArguments{ launchOptions->getGameArguments() };
	if (!gameArguments.isEmpty())
	{
		listLaunchCommand.append(gameArguments);
	}

	command = listLaunchCommand.join(" ")		
		.replace("${natives_directory}", nativesDirectory)
		.replace("${launcher_name}", launcherName)
		.replace("${launcher_version}", launcherVersion)
		.replace("${classpath}", QString{ "\"%1\"" }.arg(listLibraryPaths.join(";")));
	return GeneralLauncher::Error::OK;
}