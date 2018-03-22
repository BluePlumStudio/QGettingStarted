#pragma once

#include <QStringList>

class QGSExtract
{
public:
	QGSExtract(const QStringList & exclude = QStringList());

	QGSExtract(const QGSExtract & right) = default;

	QGSExtract(QGSExtract && right) = default;

	QGSExtract & operator=(const QGSExtract & right) = default;

	QGSExtract & operator=(QGSExtract && right) = default;

	~QGSExtract();

	QGSExtract & setExclude(const QStringList & exclude);

	QStringList getExclude()const;
private:
	QStringList mExclude;
};
