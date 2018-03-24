#include <QStringList>
#include <QSharedPointer>

#include "QGSGeneralLauncherStrategy.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSFileTools.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

QGSGeneralLauncherStrategy::QGSGeneralLauncherStrategy() 
{
}

QGSGeneralLauncherStrategy::~QGSGeneralLauncherStrategy()
{
}

LauncherError::ErrorFlags QGSGeneralLauncherStrategy::generateLaunchCommand(const QGSGameVersion & version,
	QGSGameDirectory & gameDirectory,
	const QGSLaunchOptions * launchOptions,
	QString & command)
{
	LauncherError::ErrorFlags ret{ LauncherError::Ok };
	if (!launchOptions)
	{
		return ret |= LauncherError::NullPointer;
	}

	QStringList launchCommandList;//launchCommand
	auto rootVersionId{ version.getId() };
	QGSGameVersion rootVersion;
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
		return ret |= LauncherError::JarFileNotFound;
	}

	//根版本Jar文件
	QSharedPointer<QFile> rootVersionJarFile{ gameDirectory.generateGameVersionJarFile(rootVersionId) };
	if (!rootVersionJarFile->exists())
	{
		return ret |= LauncherError::JarFileNotFound;
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
		ret |= LauncherError::JavaPathNotIncluded;
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
		//logging
		auto && loggingPath{ launchOptions->getLoggingPath() };
		if (!loggingPath.isEmpty())
		{
			auto && argument{ rootVersion.getLogging().value("client").getArgument() };
			if (!argument.isEmpty())
			{
				launchCommandList.append(argument.replace("${path}", "\"" + loggingPath + "\""));
			}
		}
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
	auto && customMinecraftArguments{ launchOptions->getCustomMinecraftArguments() };
	//natives目录
	auto nativesDirectory{ gameDirectory.generateNativesDirectory(version.getId()) };
	nativesDirectory.mkpath(nativesDirectory.absolutePath());
	//launcherName
	const QString launcherName{ customMinecraftArguments.contains("${launcher_name}") ? customMinecraftArguments.value("${launcher_name}") : "\"QGettingStarted\"" };
	//launcherVersion
	const QString launcherVersion{ customMinecraftArguments.contains("${launcher_version}") ? customMinecraftArguments.value("${launcher_version}") : "\"Pre 1.0.0\"" };
	//libraries
	auto inheritsVersionId{ version.getId() };
	QStringList libraryPathList;
	do
	{
		auto & version{ gameDirectory.getVersion(inheritsVersionId) };
		auto && libraryList{ version.getLibraries() };

		//for (auto & i : libraryList)
		for (int i = 0; i < libraryList.size(); ++i)
		{
			if (!isRulesAllowing(libraryList[i].getRules()))
			{
				continue;
			}

			QSharedPointer<QFile> fileLibrary{ gameDirectory.generateLibraryFile(libraryList[i]) };
			auto libraryPath{ fileLibrary->fileName() };
			if (libraryList[i].getNative())
			{
				//解压natives
				auto extractList{ QGSFileTools::extractDirectory(libraryPath, nativesDirectory.absolutePath()) };
				if (extractList.isEmpty())
				{
					//throw QGSExceptionCompress(libraryPath, nativesDirectory.absolutePath());
					ret |= LauncherError::NativesCompressError;
				}

				auto && excludeList{ libraryList[i].getExtract().getExclude() };
				for (auto & exclude : excludeList)
				{
					if (!QGSFileTools::removeDirectory(nativesDirectory.absolutePath() + SEPARATOR + exclude))
					{
						ret |= LauncherError::NativesCompressError;
					}
				}

				continue;
			}

			libraryPathList.append(libraryPath);
		}

		QSharedPointer<QFile> fileInheritsVersionJar{ gameDirectory.generateGameVersionJarFile(inheritsVersionId) };
		libraryPathList.append(fileInheritsVersionJar->fileName());//版本".jar"文件
	} while (!(inheritsVersionId = gameDirectory.getVersion(inheritsVersionId).getInheritsFrom()).isEmpty());
	//mainClass
	launchCommandList.append(version.getMainClass());
	/*minecraftArguments*/
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

	QDir assetsDirectory;
	if (!gameDirectory.generateAssetsDirectory(rootVersionId, rootVersion.getAssetIndex(), assetsDirectory))
	{
		ret |= LauncherError::AssetFirectoryGenerateFailure;
	}
	auto && assetsDirAbsolutePath{ assetsDirectory.absolutePath() };

	auto && authPlayerName{ authInfo.getSelectedProfile().getName() };
	if (authPlayerName.isEmpty())
	{
		return ret |= LauncherError::PlayerNameNotIncluded;
	}

	auto && authUuid{ authInfo.getSelectedProfile().getId() };
	if (authUuid.isEmpty())
	{
		return ret |= LauncherError::AuthUuidNotIncluded;
	}

	auto && authAccessToken{ authInfo.getAccessToken() };
	if (authAccessToken.isEmpty())
	{
		return ret |= LauncherError::AuthAccessTokenNotIncluded;
	}

	auto && userType{ authInfo.getUserType() };
	if (userType.isEmpty())
	{
		return ret |= LauncherError::UserTypeNotIncluded;
	}

	minecraftArguments.replace("${auth_player_name}", customMinecraftArguments.contains("${auth_player_name}") ? customMinecraftArguments.value("${auth_player_name}") : authPlayerName)
		.replace("${version_name}", customMinecraftArguments.contains("${version_name}") ? customMinecraftArguments.value("${version_name}") : version.getId())
		.replace("${game_directory}", customMinecraftArguments.contains("${game_directory}") ? customMinecraftArguments.value("${game_directory}") : QString{ "\"%1\"" }.arg(gameDirectory.getBaseDir().absolutePath()))
		.replace("${assets_root}", customMinecraftArguments.contains("${assets_root}") ? customMinecraftArguments.value("${assets_root}") : QString{ "\"%1\"" }.arg(assetsDirAbsolutePath))
		.replace("${assets_index_name}", customMinecraftArguments.contains("${assets_index_name}") ? customMinecraftArguments.value("${assets_index_name}") : rootVersion.getAssets())
		.replace("${auth_uuid}", customMinecraftArguments.contains("${auth_uuid}") ? customMinecraftArguments.value("${auth_uuid}") : authUuid)
		.replace("${auth_access_token}", customMinecraftArguments.contains("${auth_access_token}") ? customMinecraftArguments.value("${auth_access_token}") : authAccessToken)
		.replace("${user_type}", customMinecraftArguments.contains("${user_type}") ? customMinecraftArguments.value("${user_type}") : userType)
		.replace("${version_type}", customMinecraftArguments.contains("${version_type}") ? customMinecraftArguments.value("${version_type}") : "\"QGettingStarted\"")
		.replace("${user_properties}", customMinecraftArguments.contains("${user_properties}") ? customMinecraftArguments.value("${user_properties}") : authInfo.getTwitchAccessToken())
		.replace("${auth_session}", customMinecraftArguments.contains("${auth_session}") ? customMinecraftArguments.value("${auth_session}") : authInfo.getAccessToken())
		.replace("${game_assets}", customMinecraftArguments.contains("${game_assets}") ? customMinecraftArguments.value("${game_assets}") : QString{ "\"%1\"" }.arg(assetsDirAbsolutePath))
		.replace("${profile_name}", customMinecraftArguments.contains("${profile_name}") ? customMinecraftArguments.value("${profile_name}") : "QGettingStarted");
	launchCommandList.append(minecraftArguments);
	//窗口大小
	auto && windowSize{ launchOptions->getWindowSize() };
	if (!windowSize.isEmpty())
	{
		launchCommandList.append(QString("--height %1").arg(windowSize.height()));
		launchCommandList.append(QString("--width %1").arg(windowSize.width()));
	}
	//直连服务器
	auto && serverInfo{ launchOptions->getServerInfo() };
	if (!serverInfo.getAddress().isEmpty() && !serverInfo.getPort().isEmpty())
	{
		launchCommandList.append(QString("--server %1").arg(serverInfo.getAddress()));
		launchCommandList.append(QString("--port %1").arg(serverInfo.getPort()));
	}
	//代理
	auto && proxy{ launchOptions->getProxy() };
	if (proxy != QNetworkProxy::NoProxy && !proxy.hostName().isEmpty())
	{
		launchCommandList.append(QString("--proxyHost %1").arg(proxy.hostName()));
		launchCommandList.append(QString("--proxyPort %1").arg(proxy.port()));
		if (!proxy.user().isEmpty() && !proxy.password().isEmpty())
		{
			launchCommandList.append(QString("--proxyUser %1").arg(proxy.user()));
			launchCommandList.append(QString("--proxyPass %1").arg(proxy.password()));
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
	return ret;
}