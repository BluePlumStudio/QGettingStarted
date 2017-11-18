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
		return QGSAbstractLauncher::LauncherError("gameΪ�գ�", QGSAbstractLauncher::LauncherError::Error::POINTER_IS_NULL);
	}

	QGSUtil * instance = QGSUtil::getInstance();
	const QString JavaPath(gamePtr->getJavaPath());
	const QString nativePath(gamePtr->getNativePath());
	const QString playerName(gamePtr->getPlayerName());
	const QString userType(gamePtr->getUserType());
	const int Xmx = gamePtr->getXmx();
	const int Xmn = gamePtr->getXmn();
	
	//�����顣
	if (JavaPath.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Java·��Ϊ�գ�"), QGSAbstractLauncher::LauncherError::Error::JAVA_PATH_NOT_INCLUDED);
	}
	if (nativePath.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Native�ļ���·��Ϊ�գ�"), QGSAbstractLauncher::LauncherError::Error::NATIVE_PATH_NOT_INCLUDED);
	}
	if (playerName.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("�û���Ϊ�գ�"), QGSAbstractLauncher::LauncherError::Error::PLAYER_NAME_NOT_INCLUDED);
	}
	if (userType.isEmpty())
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("�û�����Ϊ�գ�"), QGSAbstractLauncher::LauncherError::Error::USER_TYPE_NOT_INCLUDED);
	}
	if (Xmx < Xmn)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("����ڴ�С����С�ڴ棡"), QGSAbstractLauncher::LauncherError::Error::XMX_LESS_THAN_XMN);
	}
	if (Xmx < XMX_SMALLEST_M)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("����ڴ��С��"), QGSAbstractLauncher::LauncherError::Error::XMX_LESS_TOO_SMALL);
	}
	if (Xmn <= 0)
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��С�ڴ�С�ڵ���0��"), QGSAbstractLauncher::LauncherError::Error::XMN_LESS_THAN_OR_EQUAL_TO_0);
	}

	const QString preInstruction(gamePtr->getPreInstruction());
	const QString JVMArgument(gamePtr->getJVMArgument());
	const QString serverAddress(gamePtr->getServerAddress());
	const QString gameArgument(gamePtr->getGameArgument());

	QVector<QString> librariesStringVector;
	//��ȡLibrariesStringVector��
	auto ret = instance->getLibrariesStringVector(gamePtr, librariesStringVector);
	if (ret.mLaunchError != QGSAbstractLauncher::LauncherError::Error::NO_ERROR)
	{
		return ret;
	}
	//��ȡminecraftArguments��
	QString minecraftArguments;
	ret = instance->getMinecraftArgumentsString(gamePtr, minecraftArguments);
	if (ret.mLaunchError != QGSAbstractLauncher::LauncherError::Error::NO_ERROR)
	{
		return ret;
	}

	//ƴ��ǰ��ָ�
	if (!preInstruction.isEmpty())
	{
		item.append(preInstruction + STRING_SPACE);
	}

	//ƴ��Java·����
	item.append(QString("\"%1\" ").arg(JavaPath));

	//ƴ��JVM������
	if (!JVMArgument.isEmpty())
	{
		item.append(QString("%1 ").arg(JVMArgument));
	}
	else
	{
		item.append(QString("%1 ").arg("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow"));
	}

	//ƴ����С�ڴ棬����ڴ档
	item.append(QString("-Xmn%1m ").arg(Xmn));
	item.append(QString("-Xmx%1m ").arg(Xmx));

	//ƴ��Native�ļ���·����
	item.append(QString("\"-Djava.library.path=%1\" ").arg(nativePath));

	//ƴ�ӹ̶�������
	item.append("-Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true -cp ");
	
	//ƴ��Libraries��

		//��ʼ"��
	item.append("\"");

	for (auto jarFilePath : librariesStringVector)
	{
		item.append(gamePtr->getGamePath() + replacement0 + "libraries" + replacement0 + jarFilePath + ";");
	}

	//ƴ�Ӻ��İ汾jar�ļ���
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

		//����" ��
	item.append("\" ");

	//ƴ��mainClass��
	QString mainClass(gamePtr->getJsonDocument().object().value("mainClass").toString());
	item.append(mainClass + " ");

	//ƴ��minecraftArguments��
	item.append(minecraftArguments + " ");

	//ƴ�ӷ�����ֱ��ip��ַ
	if (!serverAddress.isEmpty())
	{
		QString address;
		QString port;

		instance->praseServerAddress(serverAddress, address, port);
		item.append(QString("--server %1 --port %2 ").arg(address).arg(port));
	}
	
	//ƴ����Ϸ�������
	if (!gameArgument.isEmpty())
	{
		item.append(gameArgument);
	}

	return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��ȡLaunchString�ɹ���"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}
