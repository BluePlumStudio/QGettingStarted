#include <QStringList>
#include <QSharedPointer>

#include "QGSGeneralLauncherStrategy.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QuaZip/JlCompress.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

QGSGeneralLauncherStrategy::QGSGeneralLauncherStrategy() 
{
}

QGSGeneralLauncherStrategy::~QGSGeneralLauncherStrategy()
{
}

QGSGeneralLauncherStrategy::Error QGSGeneralLauncherStrategy::generateLaunchCommand(const Version & version,
	QGSGameDirectory & gameDirectory,
	const QGSLaunchOptions * launchOptions,
	QString & command)
{
	if (!launchOptions)
	{
		return Error::POINTER_IS_NULL;
	}

	QStringList launchCommandList;//launchCommand
	auto rootVersionId{ version.getId() };
	Version rootVersion;
	//获取根版本
	try
	{
		while (!gameDirectory.getVersion(rootVersionId).getInheritsFrom().isEmpty())
		{
			rootVersionId = gameDirectory.getVersion(rootVersionId).getInheritsFrom();
		}
		rootVersion = gameDirectory.getVersion(rootVersionId);
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		return Error::JAR_FILE_NOT_FOUND;
	}

	//根版本Jar文件
	QSharedPointer<QFile> rootVersionJarFile{ gameDirectory.generateVersionJarFile(rootVersionId) };
	if (!rootVersionJarFile->exists())
	{
		return Error::JAR_FILE_NOT_FOUND;
	}
	//前置指令
	const auto && wrapper{ launchOptions->getWrapper() };
	if (!wrapper.isEmpty())
	{
		launchCommandList.append(wrapper);
	}
	//Java路径
	const auto && JavaPath{ launchOptions->getJavaPath() };
	if (JavaPath.isEmpty())
	{
		return Error::JAVA_PATH_NOT_INCLUDED;
	}
	launchCommandList.append(QString{ "\"%1\"" }.arg(JavaPath));
	//JVM虚拟机参数
	if (launchOptions->getGeneratedJVMArguments())
	{
		//自定义JVM虚拟机参数
		const auto && JVMArguments{ launchOptions->getJVMArguments() };
		if (!JVMArguments.isEmpty())
		{
			launchCommandList.append(JVMArguments);
		}
		
		launchCommandList.append(QString("\"-Dminecraft.client.jar=%1\"").
			arg(rootVersionJarFile->fileName()));
		//最大内存（MB）
		launchCommandList.append(QString("-Xmx%1m").arg(launchOptions->getMaxMemory()));
		//最小内存（MB）
		launchCommandList.append(QString("-Xmn%1m").arg(launchOptions->getMinMemory()));
		//内存永久保存区域（MB）
		if (launchOptions->getMetaspaceSize() > 0)
		{
			launchCommandList.append(QString("-XX:PermSize=%1m").arg(launchOptions->getMetaspaceSize()));
		}
		//-Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true
		launchCommandList.append("-Dfml.ignoreInvalidMinecraftCertificates=true");
		launchCommandList.append("-Dfml.ignorePatchDiscrepancies=true");
	}
	//新版json包含"arguments"属性
	auto && arguments{ rootVersion.getArguments() };
	auto && JVMList{ arguments.getJVM() };
	if (!JVMList.isEmpty())
	{
		for (auto & i : JVMList)
		{
			if (isRulesAllowing(i.getRules()))
			{
				auto && valueList{ i.getValue() };
				for (auto & j : valueList)
				{
					//防止value中等号后的值带有空格所导致的问题
					int equalSignLocation = j.indexOf("=");
					if (equalSignLocation != -1)
					{
						if (j.right(equalSignLocation).contains(" "))
						{
							j = j.left(equalSignLocation + 1) + "\"" + j.mid(equalSignLocation + 1) + "\"";
						}
					}
					launchCommandList.append(j);
				}
			}
		}
	}
	else
	{
		launchCommandList.append("-Djava.library.path=${natives_directory}");
		launchCommandList.append("-Dminecraft.launcher.brand=${launcher_name}");
		launchCommandList.append("-Dminecraft.launcher.version=${launcher_version}");
		launchCommandList.append("-cp");
		launchCommandList.append("${classpath}");
	}
	//natives目录
	auto nativesDirectory{ gameDirectory.generateNativesDirectory(version.getId()) };
	nativesDirectory.mkdir(nativesDirectory.absolutePath());
	//launcherName
	const QString launcherName{ "\"QGettingStarted\"" };
	//launcherVersion
	const QString launcherVersion{ "\"Beta 1.0.0\"" };
	//libraries
	auto inheritsVersionId{ version.getId() };
	QStringList libraryPathList;
	do
	{
		auto & version{ gameDirectory.getVersion(inheritsVersionId) };
		auto && libraryList{ version.getLibraries() };

		for (auto & i : libraryList)
		{
			if (!isRulesAllowing(i.getRules()))
			{
				continue;
			}

			QSharedPointer<QFile> fileLibrary{ gameDirectory.generateLibraryFile(i) };
			auto libraryPath{ fileLibrary->fileName() };
			if (i.getNative())
			{
				//解压natives
				auto extractList{ JlCompress::extractDir(libraryPath, nativesDirectory.absolutePath()) };
				if (extractList.isEmpty())
				{
					throw QGSExceptionFileIO(nativesDirectory.absolutePath());
				}
				auto && extract{ i.getExtract() };
				auto && excludeList{ extract.getExclude() };
				for (auto & exclude : excludeList)
				{
					nativesDirectory.rmdir(nativesDirectory.absolutePath() + SEPARATOR + exclude);
				}
				continue;
			}

			libraryPathList.append(libraryPath);
		}

		QSharedPointer<QFile> fileInheritsVersionJar{ gameDirectory.generateVersionJarFile(inheritsVersionId) };
		libraryPathList.append(fileInheritsVersionJar->fileName());//版本".jar"文件
	} while (!(inheritsVersionId = gameDirectory.getVersion(inheritsVersionId).getInheritsFrom()).isEmpty());
	//mainClass
	launchCommandList.append(version.getMainClass());
	//minecraftArguments
	auto && game{ arguments.getGame() };
	QString minecraftArguments;
	if (!game.isEmpty())
	{
		QStringList argumentList;
		for (auto & i : game)
		{
			if (i.getRules().getRules().isEmpty())
			{
				argumentList.append(i.getValue());
			}
		}
		minecraftArguments = argumentList.join(" ");
	}
	else
	{
		minecraftArguments = version.getMinecraftArguments();
	}
	auto && authInfo{ launchOptions->getAuthInfo() };
	minecraftArguments.replace("${auth_player_name}", authInfo.getSelectedProfile().getName())
		.replace("${version_name}", version.getId())
		.replace("${game_directory}", QString{ "\"%1\"" }.arg(gameDirectory.getBaseDir().absolutePath()))
		.replace("${assets_root}",
			QString{ "\"%1\"" }.arg(gameDirectory.generateAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath()))
		.replace("${assets_index_name}", rootVersion.getAssetIndex().getId())
		.replace("${auth_uuid}", authInfo.getSelectedProfile().getId())
		.replace("${auth_access_token}", authInfo.getAccessToken())
		.replace("${user_type}", authInfo.getUserType())
		.replace("${version_type}", "\"QGettingStarted\"")
		.replace("${user_properties}", "{}")
		.replace("${auth_session}", authInfo.getAccessToken())
		.replace("${game_assets}",
			QString{ "\"%1\"" }.arg(gameDirectory.generateAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath()))
		.replace("${profile_name}", "Minecraft");
	launchCommandList.append(minecraftArguments);
	//其他参数
	//窗口大小
	auto && windowSize{ launchOptions->getWindowSize() };
	if (!windowSize.isEmpty())
	{
		launchCommandList.append(QString("--height %1").arg(windowSize.height()));
		launchCommandList.append(QString("--width %1").arg(windowSize.width()));
	}
	//直连服务器
	auto && serverInfo{ launchOptions->getServerInfo() };
	if (!serverInfo.address.isEmpty() && !serverInfo.port.isEmpty())
	{
		launchCommandList.append(QString("--server %1").arg(serverInfo.address));
		launchCommandList.append(QString("--port %1").arg(serverInfo.port));
	}
	//代理
	auto && proxyInfo{ launchOptions->getProxyInfo() };
	if (!proxyInfo.address.isEmpty() && !proxyInfo.port.isEmpty())
	{
		launchCommandList.append(QString("--proxyHost %1").arg(proxyInfo.address));
		launchCommandList.append(QString("--proxyPort %1").arg(proxyInfo.port));
		if (!proxyInfo.user.isEmpty() && !proxyInfo.password.isEmpty())
		{
			launchCommandList.append(QString("--proxyUser %1").arg(proxyInfo.user));
			launchCommandList.append(QString("--proxyPass %1").arg(proxyInfo.password));
		}
	}
	//游戏额外参数
	auto gameArguments{ launchOptions->getGameArguments() };
	if (!gameArguments.isEmpty())
	{
		launchCommandList.append(gameArguments);
	}

	command = launchCommandList.join(" ")
		.replace("${natives_directory}", "\"" + nativesDirectory.absolutePath() + "\"")
		.replace("${launcher_name}", launcherName)
		.replace("${launcher_version}", launcherVersion)
		.replace("${classpath}", QString{ "\"%1\"" }.arg(libraryPathList.join(";")));
	return QGSGeneralLauncherStrategy::Error::OK;
}