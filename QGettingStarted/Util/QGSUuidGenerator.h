#pragma once

#include <QString>

class QGSUuidGenerator
{
public:
	QGSUuidGenerator();

	QGSUuidGenerator(const QGSUuidGenerator & right) = delete;

	QGSUuidGenerator(QGSUuidGenerator && right) = delete;

	QGSUuidGenerator & operator=(const QGSUuidGenerator & right) = delete;

	QGSUuidGenerator & operator=(QGSUuidGenerator && right) = delete;

	~QGSUuidGenerator();

	static QGSUuidGenerator & getInstance();

	QString generateUuid(const QString & seed);

private:

};

