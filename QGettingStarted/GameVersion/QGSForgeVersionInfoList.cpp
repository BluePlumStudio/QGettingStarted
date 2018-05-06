#include <QJsonArray>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>

#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "QGSForgeVersionInfoList.h"

QGSForgeVersionInfoList::QGSForgeVersionInfoList()
{

}

QGSForgeVersionInfo & QGSForgeVersionInfoList::operator[](const int index)
{
	return mForgeVersionInfoVector[index];
}

QGSForgeVersionInfoList::~QGSForgeVersionInfoList()
{
}

const QGSForgeVersionInfo & QGSForgeVersionInfoList::at(const int index)
{
	return mForgeVersionInfoVector.at(index);
}

QGSForgeVersionInfo QGSForgeVersionInfoList::getVersionInfo(const int build)
{
	auto it(findForgeVersionInfo(build));
	if (it == mForgeVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}
	
	return *it;
}

bool QGSForgeVersionInfoList::addVersionInfo(const QGSForgeVersionInfo & versionInfo)
{
	if (mForgeVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mForgeVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

bool QGSForgeVersionInfoList::removeVersionInfo(const int build)
{
	auto it(findForgeVersionInfo(build));
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	mForgeVersionInfoVector.erase(it);

	return true;
}

bool QGSForgeVersionInfoList::containsVersionInfo(const int build)
{
	auto it(findForgeVersionInfo(build));
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int QGSForgeVersionInfoList::size()
{
	return mForgeVersionInfoVector.size();
}

bool QGSForgeVersionInfoList::merge(const QGSForgeVersionInfoList & right)
{
	std::vector<QGSForgeVersionInfo> newInfoVector;
	std::vector<QGSForgeVersionInfo> && oldInfoVector(mForgeVersionInfoVector.toStdVector());
	std::vector<QGSForgeVersionInfo> && rightInfoVector(right.mForgeVersionInfoVector.toStdVector());
	newInfoVector.resize(oldInfoVector.size() + rightInfoVector.size());
	std::merge(std::begin(oldInfoVector),
		std::end(oldInfoVector),
		std::begin(rightInfoVector),
		std::end(rightInfoVector),
		std::begin(newInfoVector));
	std::unique(std::begin(newInfoVector), std::end(newInfoVector));
	mForgeVersionInfoVector = QVector<QGSForgeVersionInfo>::fromStdVector(newInfoVector);

	return true;
}

void QGSForgeVersionInfoList::sort()
{
	qSort(mForgeVersionInfoVector.begin(), mForgeVersionInfoVector.end(), [](const QGSForgeVersionInfo & left, const QGSForgeVersionInfo & right)
	{
		return left.getBuild() < right.getBuild();
	});
}

QVector<QGSForgeVersionInfo>::iterator QGSForgeVersionInfoList::findForgeVersionInfo(const int build)
{
	auto it(mForgeVersionInfoVector.begin());

	while (it++ != mForgeVersionInfoVector.end())
	{
		if (it->getBuild() == build)
		{
			break;
		}
	}

	return it;
}

QVector<QGSForgeVersionInfo> QGSForgeVersionInfoList::getForgeVersionInfoVector()const
{
	return mForgeVersionInfoVector;
}
