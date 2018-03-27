#pragma once

#include <QString>
#include <QStringList>

#include "QGSRules.h"

class QGSArguments
{
public:
	class QGSArgument
	{
	public:
		QGSArgument(const QString & value = "", const QGSRules & rules = QGSRules()) :mRules(rules), mValue(value)
		{

		}
		QGSArgument(const QStringList & value = QStringList(), const QGSRules & rules = QGSRules()) :mRules(rules), mValue(value)
		{

		}

		QGSArgument(const QGSArgument & right) = default;

		QGSArgument(QGSArgument && right) = default;

		QGSArgument & operator=(const QGSArgument & right) = default;

		QGSArgument & operator=(QGSArgument && right) = default;

		~QGSArgument()
		{

		}

		QGSArgument & setRules(const QGSRules & rules)
		{
			mRules = rules;
			return *this;
		}

		QGSArgument & setValue(const QString & value)
		{
			mValue = QStringList(value);
			return *this;
		}

		QGSArgument & setValue(const QStringList & value)
		{
			mValue = value;
			return *this;
		}

		QGSRules getRules()const
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
		QGSRules mRules;
		QStringList mValue;
	};
public:
	QGSArguments(const QList<QGSArgument> & jvm = QList<QGSArgument>(), const QList<QGSArgument> & game = QList<QGSArgument>());

	QGSArguments(const QGSArguments & right) = default;

	QGSArguments(QGSArguments && right) = default;

	QGSArguments & operator=(const QGSArguments & right) = default;

	QGSArguments & operator=(QGSArguments && right) = default;

	~QGSArguments();

	QGSArguments & setJvm(QList<QGSArgument> jvm);

	QGSArguments & setGame(QList<QGSArgument> game);

	QList<QGSArgument> getGame()const;

	QList<QGSArgument> getJVM()const;

	void clear();

private:
	QList<QGSArgument> mJvm;
	QList<QGSArgument> mGame;

};

