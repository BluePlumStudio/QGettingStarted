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

	const QGSForgeVersionInfo & getVersionInfo(const QString & build);

	bool addVersionInfo(const QGSForgeVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & build);

	bool containsVersionInfo(const QString & build);

	int size();

	bool merge(const QGSForgeVersionInfoList & right);

	QVector<QGSForgeVersionInfo> getForgeVersionInfoVector()const;
private:
	void sort();
	QVector<QGSForgeVersionInfo>::iterator findForgeVersionInfo(const QString & build);
private:
	QVector<QGSForgeVersionInfo> mForgeVersionInfoVector;
};
