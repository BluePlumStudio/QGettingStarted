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
		Argument(const QString & value = "", const Rules & rules = Rules()) :mRules(rules), mValue(value)
		{

		}
		Argument(const QStringList & value = QStringList(), const Rules & rules = Rules()) :mRules(rules), mValue(value)
		{

		}

		Argument(const Argument & right) = default;

		Argument(Argument && right) = default;

		Argument & operator=(const Argument & right) = default;

		Argument & operator=(Argument && right) = default;

		~Argument()
		{

		}

		Argument & setRules(const Rules & rules)
		{
			mRules = rules;
			return *this;
		}

		Argument & setValue(const QString & value)
		{
			mValue = QStringList(value);
			return *this;
		}

		Argument & setValue(const QStringList & value)
		{
			mValue = value;
			return *this;
		}

		Rules getRules()const
		{
			return mRules;
		}

		QStringList getValue()const
		{
			return mValue;
		}

		void clear()
		{
			mRules.clear();
			mValue.clear();
		}
	private:
		Rules mRules;
		QStringList mValue;
	};
public:
	Arguments(QList<Argument> & jvm = QList<Argument>(), QList<Argument> & game = QList<Argument>());

	Arguments(const Arguments & right) = default;

	Arguments(Arguments && right) = default;

	Arguments & operator=(const Arguments & right) = default;

	Arguments & operator=(Arguments && right) = default;

	~Arguments();

	Arguments & setJvm(QList<Argument> jvm);

	Arguments & setGame(QList<Argument> game);

	QList<Argument> getGame()const;

	QList<Argument> getJVM()const;

	void clear();

private:
	QList<Argument> mJvm;
	QList<Argument> mGame;

};

