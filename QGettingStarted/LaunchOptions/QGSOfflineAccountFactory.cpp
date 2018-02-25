#include "QGSOfflineAccountFactory.h"

QGSOfflineAccountFactory::QGSOfflineAccountFactory()
{

}

QGSOfflineAccountFactory::~QGSOfflineAccountFactory()
{

}

QGSOfflineAccount * QGSOfflineAccountFactory::createAccount() const
{
	return new QGSOfflineAccount();
}

