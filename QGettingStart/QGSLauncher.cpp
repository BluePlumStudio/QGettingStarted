#include "QGSLauncher.h"

#include <iostream>

#define ARM		"arm"
#define ARM64	"arm64"
#define I386	"i386"
#define IA64	"ia64"
#define MIPS	"mips"
#define MIPS64	"mips64"
#define POWER	"power"
#define POWER64 "power64"
#define SPARC	"sparc"
#define SPARCV9 "sparcv9"
#define X86_64	"x86_64"

#define XMX_SMALLEST_M 128
#define CHAR_SPACE ' '
#define STRING_SPACE " "

using namespace std;

QGSLauncher::QGSLauncher()
{
}


QGSLauncher::~QGSLauncher()
{
}

QGSAbstractLauncher::LauncherError QGSLauncher::getLaunchString(QGSAbstractGame * game, QString & item)
{
#ifdef Q_OS_WIN
	const QString replacement0("\\");
#elif
	const QString replacement0("/");
#endif
	auto gamePtr = static_cast<QGSGame *>(game);

	if (!gamePtr)
	{
		return QGSAbstractLauncher::LauncherError("game为空！", QGSAbstractLauncher::LauncherError::Error::POINTER_IS_NULL);
	}

	QGSUtil * instance = QGSUtil::getInstance();
	const QString JavaPath(gamePtr->getJavaPath());
	const QString nativePath(gamePtr->getNativePath());
	const QString playerName(gamePtr->getPlayerName());
	const QString userType(gamePtr->getUserType());
	const int Xmx = gamePtr->getXmx();
	const int Xmn = gamePtr->getXmn();
	
	//错误检查。
	if (JavaPath.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Java路径为空！"), QGSAbstractLauncher::LauncherError::Error::JAVA_PATH_NOT_INCLUDED);
	}
	if (nativePath.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Native文件夹路径为空！"), QGSAbstractLauncher::LauncherError::Error::NATIVE_PATH_NOT_INCLUDED);
	}
	if (playerName.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("用户名为空！"), QGSAbstractLauncher::LauncherError::Error::PLAYER_NAME_NOT_INCLUDED);
	}
	if (userType.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("用户类型为空！"), QGSAbstractLauncher::LauncherError::Error::USER_TYPE_NOT_INCLUDED);
	}
	if (Xmx < Xmn)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("最大内存小于最小内存！"), QGSAbstractLauncher::LauncherError::Error::XMX_LESS_THAN_XMN);
	}
	if (Xmx < XMX_SMALLEST_M)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("最大内存过小！"), QGSAbstractLauncher::LauncherError::Error::XMX_LESS_TOO_SMALL);
	}
	if (Xmn <= 0)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("最小内存小于等于0！"), QGSAbstractLauncher::LauncherError::Error::XMN_LESS_THAN_OR_EQUAL_TO_0);
	}

	const QString preInstruction(gamePtr->getPreInstruction());
	const QString JVMArgument(gamePtr->getJVMArgument());
	const QString serverAddress(gamePtr->getServerAddress());
	const QString gameArgument(gamePtr->getGameArgument());

	QVector<QString> librariesStringVector;
	//获取LibrariesStringVector。
	auto ret = instance->getLibrariesStringVector(gamePtr, librariesStringVector);
	if (ret.mLaunchError != QGSAbstractLauncher::LauncherError::Error::NO_ERROR)
	{
		return ret;
	}
	//获取minecraftArguments。
	QString minecraftArguments;
	ret = instance->getMinecraftArgumentsString(gamePtr, minecraftArguments);
	if (ret.mLaunchError != QGSAbstractLauncher::LauncherError::Error::NO_ERROR)
	{
		return ret;
	}

	//拼接前置指令。
	if (!preInstruction.isEmpty())
	{
		item.append(preInstruction + STRING_SPACE);
	}

	//拼接Java路径。
	item.append(QString("\"%1\" ").arg(JavaPath));

	//拼接JVM参数。
	if (!JVMArgument.isEmpty())
	{
		item.append(QString("%1 ").arg(JVMArgument));
	}
	else
	{
		item.append(QString("%1 ").arg("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow"));
	}

	//拼接最小内存，最大内存。
	item.append(QString("-Xmn%1m ").arg(Xmn));
	item.append(QString("-Xmx%1m ").arg(Xmx));

	//拼接Native文件夹路径。
	item.append(QString("\"-Djava.library.path=%1\" ").arg(nativePath));

	//拼接固定参数。
	item.append("-Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true -cp ");
	
	//拼接Libraries。

		//开始"。
	item.append("\"");

	for (auto jarFilePath : librariesStringVector)
	{
		item.append(gamePtr->getGamePath() + replacement0 + "libraries" + replacement0 + jarFilePath + ";");
	}

	//拼接核心版本jar文件。
	QFile jarFile;
	while (gamePtr)
	{
		
		QString mainJarFileName(gamePtr->getGameVersion() + ".jar");
		jarFile.setFileName(gamePtr->getGamePath() +
			replacement0 +
			"versions" +
			replacement0 +
			gamePtr->getGameVersion() +
			replacement0 +
			mainJarFileName);
		if (jarFile.exists())
		{
			break;
		}
		gamePtr = gamePtr->getFatherPtr();
	}
	item.append(jarFile.fileName());

		//结束" 。
	item.append("\" ");

	//拼接mainClass。
	QString mainClass(gamePtr->getJsonDocument().object().value("mainClass").toString());
	item.append(mainClass + " ");

	//拼接minecraftArguments。
	item.append(minecraftArguments + " ");

	//拼接服务器直连ip地址
	if (!serverAddress.isEmpty())
	{
		QString address;
		QString port;

		instance->praseServerAddress(serverAddress, address, port);
		item.append(QString("--server %1 --port %2 ").arg(address).arg(port));
	}
	
	//拼接游戏额外参数
	if (!gameArgument.isEmpty())
	{
		item.append(gameArgument);
	}

	return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("获取LaunchString成功！"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}
