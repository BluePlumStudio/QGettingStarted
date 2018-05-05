#pragma once

#include <QSharedPointer>

#include "QGSILauncherStrategy.h"
#include "QGSGameDirectory.h"

/**

* @brief 启动器

*/
class QGSLauncher :public QObject
{
	Q_OBJECT

public:
	QGSLauncher(QObject * parent = nullptr);

	QGSLauncher(const QGSLauncher & right) = delete;

	QGSLauncher(QGSLauncher && right) = delete;

	QGSLauncher & operator=(const QGSLauncher & right) = delete;

	QGSLauncher & operator=(QGSLauncher && right) = delete;

	virtual ~QGSLauncher();

	/**

	* @brief 生成启动命令

	* @param version 游戏版本 gameDirectory 游戏目录 launchOptions 启动选项 command 命令输出

	* @return 启动错误

	* @retval QGSLauncherError::ErrorFlags

	* @note

	* @attention

	* @warning

	* @exception

	*/
	virtual QGSLauncherError::ErrorFlags generateLaunchCommand(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QGSLaunchOptions * launchOptions, QString & command);
private:

};

