#pragma once

#include <QString>
#include <QStringList>
#include <QMetaType>

#include "QGSRules.h"

class QGSArguments
{
public:
	class QGSArgument
	{
	public:
		QGSArgument(const QStringList & value = QStringList(), const QGSRules & rules = QGSRules());

		QGSArgument(const QGSArgument & right) = default;

		QGSArgument(QGSArgument && right) = default;

		QGSArgument & operator=(const QGSArgument & right) = default;

		QGSArgument & operator=(QGSArgument && right) = default;

		~QGSArgument();

		QGSArgument & setRules(const QGSRules & rules);

		QGSArgument & setValue(const QString & value);

		QGSArgument & setValue(const QStringList & value);

		QGSArgument & addValue(const QString & value);

		QGSRules getRules()const;

		QStringList getValue()const;

		void clear();
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

Q_DECLARE_METATYPE(QGSArguments::QGSArgument)
Q_DECLARE_METATYPE(QGSArguments)