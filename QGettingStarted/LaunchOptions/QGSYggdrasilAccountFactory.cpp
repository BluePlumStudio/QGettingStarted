#include "QGSYggdrasilAccountFactory.h"

QGSYggdrasilAccountFactory::QGSYggdrasilAccountFactory(QObject * parent) :QGSIAccountFactory(parent)
{

}

QGSYggdrasilAccountFactory::~QGSYggdrasilAccountFactory()
{

}

QGSYggdrasilAccount * QGSYggdrasilAccountFactory::createAccount() const
{
	return new QGSYggdrasilAccount();
}

