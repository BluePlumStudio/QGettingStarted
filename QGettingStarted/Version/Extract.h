#pragma once

#include <QStringList>

class Extract
{
public:
	Extract(const QStringList & exclude = QStringList());

	Extract(const Extract & right) = default;

	Extract(Extract && right) = default;

	Extract & operator=(const Extract & right) = default;

	Extract & operator=(Extract && right) = default;

	~Extract();

	Extract & setExclude(const QStringList & exclude);

	QStringList getExclude()const;
private:
	QStringList mExclude;
};
