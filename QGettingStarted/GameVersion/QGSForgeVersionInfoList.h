#pragma once

#include <QVector>

#include "QGSForgeVersionInfo.h"

class QGSForgeVersionInfoList
{
public:
	QGSForgeVersionInfoList();

	QGSForgeVersionInfoList(const QGSForgeVersionInfoList & right) = default;

	QGSForgeVersionInfoList(QGSForgeVersionInfoList && right) = default;

	QGSForgeVersionInfoList & operator=(const QGSForgeVersionInfoList & right) = default;

	QGSForgeVersionInfoList & operator=(QGSForgeVersionInfoList && right) = default;

	QGSForgeVersionInfo & operator[](const int index);

	~QGSForgeVersionInfoList();

	const QGSForgeVersionInfo & at(const int index);

	QGSForgeVersionInfo & getVersionInfo(const int build);

	bool addVersionInfo(const QGSForgeVersionInfo & versionInfo);

	bool removeVersionInfo(const int build);

	bool containsVersionInfo(const int build);

	int size();

	bool merge(const QGSForgeVersionInfoList & right);

	QVector<QGSForgeVersionInfo> getForgeVersionInfoVector()const;
private:
	void sort();
	QVector<QGSForgeVersionInfo>::iterator findForgeVersionInfo(const int build);
private:
	QVector<QGSForgeVersionInfo> mForgeVersionInfoVector;
};

Q_DECLARE_METATYPE(QGSForgeVersionInfoList)