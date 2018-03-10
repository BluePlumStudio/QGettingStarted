#pragma once

#include <QString>
#include <QUuid>

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

	static QString generateUuid(const QString & seed);

	static QString generateUuid();
private:

};

