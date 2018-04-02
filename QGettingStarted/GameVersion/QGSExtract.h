#pragma once

#include <QStringList>
#include <QMetaType>

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

Q_DECLARE_METATYPE(QGSExtract)