#pragma once

#include <QString>
#include <QStringList>

#include "Rules.h"

class Arguments
{
public:
	class Argument
	{
	public:
		Argument(const Rules & rules, const QString & value) :mRules(rules), mValue(value)
		{

		}
		~Argument()
		{

		}

		inline Argument & setRules(const Rules & rules)
		{
			mRules = rules;
			return *this;
		}

		inline Argument & setValue(const QString & value)
		{
			mValue = value;
			return *this;
		}

		inline Rules getRules()const
		{
			return mRules;
		}

		inline QString getValue()const
		{
			return mValue;
		}
	private:
		Rules mRules;
		QString mValue;
	};
public:
	Arguments();

	~Arguments();

	inline Arguments & setJvm(QList<Argument> jvm);

	inline Arguments & setGame(QList<Argument> game);

	inline QList<Argument> getGame()const;

	inline QList<Argument> getJVM()const;

private:
	QList<Argument> mJvm;
	QList<Argument> mGame;

};

