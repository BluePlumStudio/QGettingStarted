#pragma once

#include <QSharedPointer>

#include "QGSILauncherStrategy.h"
#include "QGSGameDirectory.h"

/**

* @brief ������

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

	* @brief ������������

	* @param version ��Ϸ�汾 gameDirectory ��ϷĿ¼ launchOptions ����ѡ�� command �������

	* @return ��������

	* @retval QGSLauncherError::ErrorFlags

	* @note

	* @attention

	* @warning

	* @exception

	*/
	virtual QGSLauncherError::ErrorFlags generateLaunchCommand(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QGSLaunchOptions * launchOptions, QString & command);
private:

};

