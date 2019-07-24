#include "QGSArguments.h"

QGSArguments::QGSArgument::QGSArgument(const QStringList & value, const QGSRules & rules)
	:mRules(rules), mValue(value)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSArguments::QGSArgument")))
	{
		qRegisterMetaType<QGSArguments::QGSArgument>("QGSArguments::QGSArgument");
	}
}

QGSArguments::QGSArgument::~QGSArgument()
{

}

QGSArguments::QGSArgument & QGSArguments::QGSArgument::setRules(const QGSRules & rules)
{
	mRules = rules;
	return *this;
}

QGSArguments::QGSArgument & QGSArguments::QGSArgument::setValue(const QString & value)
{
	mValue = QStringList(value);
	return *this;
}

QGSArguments::QGSArgument & QGSArguments::QGSArgument::setValue(const QStringList & value)
{
	mValue = value;
	return *this;
}

QGSArguments::QGSArgument & QGSArguments::QGSArgument::addValue(const QString & value)
{
	mValue.push_back(value);
	return *this;
}

QGSRules QGSArguments::QGSArgument::getRules()const
{
	return mRules;
}

QStringList QGSArguments::QGSArgument::getValue()const
{
	return mValue;
}

void QGSArguments::QGSArgument::clear()
{
	mRules.clear();
	mValue.clear();
}

/**/

QGSArguments::QGSArguments(const QList<QGSArgument> & jvm, const QList<QGSArgument> & game)
	:mJvm(jvm), mGame(game)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSArguments")))
	{
		qRegisterMetaType<QGSArguments>("QGSArguments");
	}
}

QGSArguments::~QGSArguments()
{
}

QGSArguments & QGSArguments::setJvm(QList<QGSArgument> jvm)
{
	mJvm = jvm;
	return *this;
}

QGSArguments & QGSArguments::setGame(QList<QGSArgument> game)
{
	mGame = game;
	return *this;
}

QList<QGSArguments::QGSArgument> QGSArguments::getGame()const
{
	return mGame;
}

QList<QGSArguments::QGSArgument> QGSArguments::getJVM()const
{
	return mJvm;
}

void QGSArguments::clear()
{
	mGame.clear();
	mJvm.clear();
}