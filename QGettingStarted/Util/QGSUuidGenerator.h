#pragma once

#include <QString>
#include <QUuid>
#include <QObject>

class QGSUuidGenerator :public QObject
{
	Q_OBJECT

public:
	QGSUuidGenerator(QObject * parent = nullptr);

	QGSUuidGenerator(const QGSUuidGenerator & right) = delete;

	QGSUuidGenerator(QGSUuidGenerator && right) = delete;

	QGSUuidGenerator & operator=(const QGSUuidGenerator & right) = delete;

	QGSUuidGenerator & operator=(QGSUuidGenerator && right) = delete;

	virtual ~QGSUuidGenerator();

	static QGSUuidGenerator & getInstance();

	static QString generateUuid(const QString & seed);

	static QString generateUuid();
private:

};

