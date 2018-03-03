#include "QGSNetwork.h"

QGSNetwork::QGSNetwork(QObject * parent) :QObject(parent), mManager(new QNetworkAccessManager)
{
}

QNetworkAccessManager * QGSNetwork::getManager()
{
	return mManager;
}

QGSNetwork::~QGSNetwork()
{
}

QGSNetwork & QGSNetwork::getInstance()
{
	static QGSNetwork instance;
	return instance;
}
