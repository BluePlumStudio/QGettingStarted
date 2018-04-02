#include "QGSOfflineAccountFactory.h"

QGSOfflineAccountFactory::QGSOfflineAccountFactory(QObject * parent) :QGSIAccountFactory(parent)
{

}

QGSOfflineAccountFactory::~QGSOfflineAccountFactory()
{

}

QGSOfflineAccount * QGSOfflineAccountFactory::createAccount() const
{
	return new QGSOfflineAccount();
}

