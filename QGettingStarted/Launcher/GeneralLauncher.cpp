#include <QStringList>
#include <QSharedPointer>

#include "GeneralLauncher.h"

GeneralLauncher::GeneralLauncher(const QString & version, QGSGameDirectory & gameDirectory) :ILauncher(version, gameDirectory)
{
}

GeneralLauncher::~GeneralLauncher()
{
}

GeneralLauncher::Error GeneralLauncher::generateLaunchCommand(const QGSLaunchOptions & launchOptions, QString & command)
{
	QStringList listCommand;

	auto rootVersionId = mVersion;
	//获取根版本
	while (!mGameDirectory.getVersion(rootVersionId).getInheritsFrom().isEmpty())
	{
		rootVersionId = mGameDirectory.getVersion(rootVersionId).getInheritsFrom();
	}
	auto & rootVersion = mGameDirectory.getVersion(rootVersionId);
	//根版本Jar文件
	QSharedPointer<QFile> fileRootVersionJar{ mGameDirectory.getVersionJarFile(rootVersionId) };
	if (!fileRootVersionJar->exists())
	{
		return Error::JAR_FILE_NOT_FOUND;
	}
	//前置指令
	const auto && wrapper = launchOptions.getWrapper();
	if (!wrapper.isEmpty())
	{
		listCommand.append(wrapper);
	}
	//Java路径
	const auto && JavaPath = launchOptions.getJavaPath();
	if (JavaPath.isEmpty())
	{
		return Error::JAVA_PATH_NOT_INCLUDED;
	}
	listCommand.append(JavaPath);
	//JVM虚拟机参数
	if (launchOptions.getGeneratedJVMArguments())
	{
		//自定义JVM虚拟机参数
		const auto && JVMArguments = launchOptions.getJVMArguments();
		if (!JVMArguments.isEmpty())
		{
			listCommand.append(JVMArguments);
		}
		
		listCommand.append(QString("\"-Dminecraft.client.jar=%1\"").
			arg(fileRootVersionJar->fileName()));
		//最大内存（MB）
		listCommand.append(QString("-Xmx%1m").arg(launchOptions.getMaxMemory()));
		//最小内存（MB）
		listCommand.append(QString("-Xmn%1m").arg(launchOptions.getMinMemory()));
		//内存永久保存区域（MB）
		if (launchOptions.getMetaspaceSize() > 0)
		{
			listCommand.append(QString("-XX:PermSize=%1m").arg(launchOptions.getMetaspaceSize()));
		}
		//-Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true
		listCommand.append("-Dfml.ignoreInvalidMinecraftCertificates=true");
		listCommand.append("-Dfml.ignorePatchDiscrepancies=true");
	}
	//新版json包含"arguments"属性
	auto && arguments = rootVersion.getArguments();
	auto && listJVM = arguments.getJVM();
	if (!listJVM.isEmpty())
	{
		for (auto & i : listJVM)
		{
			if (isRulesAllowing(i.getRules()))
			{
				listCommand.append(i.getValue());
			}
		}
	}
	else
	{
		listCommand.append("-Djava.library.path=${natives_directory}");
		listCommand.append("-Dminecraft.launcher.brand=${launcher_name}");
		listCommand.append("-Dminecraft.launcher.version=${launcher_version}");
		listCommand.append("-cp");
		listCommand.append("${classpath}");
	}
	//natives目录
	auto && nativesDirectory = "\"" + mGameDirectory.getNativesDirectory(mVersion).absolutePath() + "\"";
	//launcherName
	const QString launcherName = "\"QGettingStarted\"";
	//launcherVersion
	const QString launcherVersion = "Beta 1.0.0";
	//libraries
	auto & version = mGameDirectory.getVersion(mVersion);
	auto && listLibraries = version.getLibraries();
	QStringList listLibraryPaths;
	for (auto & i : listLibraries)
	{
		if (!isRulesAllowing(i.getRules()))
		{
			continue;
		}
		QSharedPointer<QFile> fileLibrary{ mGameDirectory.getLibraryFile(i) };
		auto && libraryPath = fileLibrary->fileName();
		if (!libraryPath.contains("natives"))
		{
			listLibraryPaths.append(libraryPath);
		}
	}
	//minecraftArguments
	auto && game = arguments.getGame();
	QString minecraftArguments;
	if (!game.isEmpty())
	{
		QStringList listArguments;
		for (auto & i : game)
		{
			if (isRulesAllowing(i.getRules()))
			{
				//剔除--demo
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
	auto && authInfo = launchOptions.getAuthInfo();
	minecraftArguments.replace("${auth_player_name}", authInfo.getSelectedProfile().getName())
		.replace("${version_name}", mVersion)
		.replace("${game_directory}", "\"" + mGameDirectory.getBaseDir().absolutePath() + "\"")
		.replace("${assets_root}",
			"\"" + mGameDirectory.getAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath() + "\"")
		.replace("${assets_index_name}", rootVersion.getAssetIndex().getId())
		.replace("${auth_uuid}", authInfo.getSelectedProfile().getId())
		.replace("${auth_access_token}", authInfo.getAccessToken())
		.replace("${user_type}", authInfo.getUserType())
		.replace("${version_type}", "\"QGettingStarted\"")
		.replace("${user_properties}", "{}")
		.replace("${auth_session}", authInfo.getAccessToken())
		.replace("${game_assets}",
			"\"" + mGameDirectory.getAssetDirectory(rootVersionId, rootVersion.getAssetIndex()).absolutePath() + "\"")
		.replace("${profile_name}", "Minecraft");
	return GeneralLauncher::Error::OK;
}