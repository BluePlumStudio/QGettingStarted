#include "QGSOptifineVersionInfoList.h"

QGSOptifineVersionInfoList::QGSOptifineVersionInfoList()
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSOptifineVersionInfoList")))
	{
		qRegisterMetaType<QGSOptifineVersionInfoList>("QGSOptifineVersionInfoList");
	}
}

QGSOptifineVersionInfo & QGSOptifineVersionInfoList::operator[](const int index)
{
	return mOptifineVersionInfoVector[index];
}

QGSOptifineVersionInfoList::~QGSOptifineVersionInfoList()
{

}

QGSOptifineVersionInfo QGSOptifineVersionInfoList::getOptifineVersionInfo(const int index)
{
	return mOptifineVersionInfoVector[index];
}

const QGSOptifineVersionInfo & QGSOptifineVersionInfoList::at(const int index)
{
	return mOptifineVersionInfoVector.at(index);
}

QList<QGSOptifineVersionInfo> QGSOptifineVersionInfoList::getVersionInfoList(const QString & mcversion)
{
	QList<QGSOptifineVersionInfo> ret;
	for (auto & versionInfo : mOptifineVersionInfoVector)
	{
		if (versionInfo.getMcversion() == mcversion)
		{
			ret.push_back(versionInfo);
		}
	}

	return ret;
}

bool QGSOptifineVersionInfoList::addVersionInfo(const QGSOptifineVersionInfo & versionInfo)
{
	if (mOptifineVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mOptifineVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

int QGSOptifineVersionInfoList::size()
{
	return mOptifineVersionInfoVector.size();
}

void QGSOptifineVersionInfoList::sort()
{
	qSort(mOptifineVersionInfoVector.begin(), mOptifineVersionInfoVector.end());
}
