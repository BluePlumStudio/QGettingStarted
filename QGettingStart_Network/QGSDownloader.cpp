#include "QGSDownloader.h"
#include "QGSNetwork.h"

class QGSDownloader::Private
{
public:
	Private(int index) :mIndex(index)
	{
		mReply = nullptr;
		mFile = nullptr;
		mHaveDoneBytes = 0;
		mStartPoint = 0;
		mEndPoint = -1;
		mFileSize = 0;
	}

	~Private()
	{
		if (mReply)
		{
			mReply->deleteLater();
		}

		if (mFile)
		{
			mFile->flush();
		}

		mReply = nullptr;
		mFile = nullptr;
	}

public:
	QNetworkReply * mReply;
	QFile * mFile;
	const int mIndex;
	qint64 mHaveDoneBytes;
	qint64 mStartPoint;
	qint64 mEndPoint;
	qint64 mFileSize;
};

QGSDownloader::QGSDownloader(int index, QObject *parent) :QObject(parent), d(new QGSDownloader::Private(index))
{
	if (!d)
	{
		throw ExceptionBadAlloc();
	}
}

bool QGSDownloader::startDownload(const QUrl & URL, QFile *file, qint64 startPoint, qint64 endPoint)
{
	if (!file || URL.isEmpty())
	{
		return false;
	}

	d->mHaveDoneBytes = 0;
	d->mStartPoint = startPoint;
	d->mEndPoint = endPoint;
	d->mFile = file;

	QNetworkRequest request;
	request.setUrl(URL);
	QString range;
	range.sprintf("Bytes=%lld-%lld", d->mStartPoint, d->mEndPoint);
	request.setRawHeader("Range", range.toLatin1());

	d->mReply = QGSNetwork::getInstance()->get(request);

	connect(d->mReply, &QNetworkReply::finished, this, &QGSDownloader::finished);

	connect(d->mReply, 
		static_cast<void(QNetworkReply::*)(qint64, qint64)>(&QNetworkReply::downloadProgress), 
		this, 
		static_cast<void(QGSDownloader::*)(qint64, qint64)>(&QGSDownloader::downloadProgress));

	/*
	connect(d->mReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
		[=](QNetworkReply::NetworkError code)
	{
		emit error(ReplyError(d->mReply->errorString(), d->mReply->error()));
	});
	*/

	return true;
}

void QGSDownloader::finished()
{
	d->mFile->flush();
	d->mReply->deleteLater();
	d->mHaveDoneBytes = 0;
	d->mStartPoint = 0;
	d->mEndPoint = -1;

	d->mReply = nullptr;
	d->mFile = nullptr;

	emit downloadFinished();
}

void QGSDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (!d->mFile)
	{
		return;
	}

	//将读到的信息写入文件    
	QByteArray data = d->mReply->readAll();
	d->mFile->seek(d->mStartPoint + d->mHaveDoneBytes);
	d->mFile->write(data);
	d->mHaveDoneBytes += data.size();

	emit downloadProgress(DownloadProgress(data.size(), bytesTotal, d->mIndex));
}

QGSDownloader::~QGSDownloader()
{
	if (d)
	{
		delete d;
	}

	d = nullptr;
}
