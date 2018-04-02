#pragma once

#include <QList>
#include <QString>
#include <QMap>
#include <QMetaType>

#include "../Util/QGSOperatingSystem.h"

namespace Action
{
	const QString ALLOW("allow");
	const QString DISALLOW("disallow");
}

class QGSRules 
{
public:
	class QGSRule
	{
	public:
		QGSRule(const QString & action = Action::ALLOW, const QMap<QString, bool> & features = QMap<QString, bool>(), const QString & os = OS::UNKNOWN, const QString & osVersion = "");

		QGSRule(const QGSRule & right) = default;

		QGSRule(QGSRule && right) = default;

		QGSRule & operator=(const QGSRule & right) = default;

		QGSRule & operator=(QGSRule && right) = default;

		~QGSRule();

		QGSRule & setAction(const QString & action);

		QGSRule & setFeatures(const QMap<QString, bool> & features);

		QGSRule & setOs(const QString & os);

		QGSRule & setOsVersion(const QString & osVersion);

		QString getAction()const;

		QMap<QString, bool> getFeatures()const;

		QString getOs()const;

		QString getOsVersion()const;

		void clear();
	private:
		QString mAction;
		QMap<QString, bool> mFeatures;
		QString mOs;
		QString mOsVersion;
		QGSOperatingSystem * mOperatingSystemPtr;
	};

public:
	QGSRules();

	QGSRules(const QList<QGSRule> & rules);

	QGSRules(const QGSRules & right) = default;

	QGSRules(QGSRules && right) = default;

	QGSRules & operator=(const QGSRules & right) = default;

	QGSRules & operator=(QGSRules && right) = default;

	~QGSRules();

	QGSRules & setRules(const QList<QGSRule> & rules);

	QList<QGSRule> getRules()const;

	QGSRules & addRule(const QGSRule & rule);

	void clear();
private: 
	QList<QGSRule> mRules;
};

Q_DECLARE_METATYPE(QGSRules::QGSRule)
Q_DECLARE_METATYPE(QGSRules)
