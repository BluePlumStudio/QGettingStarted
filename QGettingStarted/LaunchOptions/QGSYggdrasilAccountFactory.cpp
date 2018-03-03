#include "QGSYggdrasilAccountFactory.h"

QGSYggdrasilAccountFactory::QGSYggdrasilAccountFactory()
{

}

QGSYggdrasilAccountFactory::~QGSYggdrasilAccountFactory()
{

}

QGSYggdrasilAccount * QGSYggdrasilAccountFactory::createAccount() const
{
	return new QGSYggdrasilAccount();
}

