#include "QGSDownloadManager.h"

class QGSDownloadManager::Private
{
public:
	Private()
	{
		mFile = nullptr;
	}

	~Private()
	{
		if (mFile)
		{
			mFile->flush();
			mFile->close();
			mFile->deleteLater();
		}

		mFile = nullptr;
	}

public:
	DownloadProgress mDownloadProgress;
	QFile * mFile;
};

QGSDownloadManager::QGSDownloadManager(QObject *parent) :QObject(parent), d(new QGSDownloadManager::Private)
{
	if (!d)
	{
		throw ExceptionBadAlloc();
	}

}

void QGSDownloadManager::addDownloader(QGSDownloader * downloader)
{
	connect(downloader, 
		static_cast<void(QGSDownloader::*)(QGSDownloader::DownloadProgress)>(&QGSDownloader::downloadProgress),
		this, 
		static_cast<void(QGSDownloadManager::*)(QGSDownloader::DownloadProgress)>(&QGSDownloadManager::downloadProgress));

	connect(downloader,
		static_cast<void(QGSDownloader::*)()>(&QGSDownloader::downloadFinished),
		this,
		static_cast<void(QGSDownloadManager::*)()>(&QGSDownloadManager::subPartFinished));

	downloader->setParent(this);
}

void QGSDownloadManager::setFile(QFile * file)
{
	d->mFile = file;
}

void QGSDownloadManager::setFileSize(qint64 fileSize)
{
	d->mDownloadProgress.mFileSize = fileSize;
}

void QGSDownloadManager::setThreadCount(int threadCount)
{
	d->mDownloadProgress.mThreadCount = threadCount;
}

void QGSDownloadManager::subPartFinished()
{
	d->mDownloadProgress.mFinishedCount++;

	if (d->mDownloadProgress.mFinishedCount == d->mDownloadProgress.mThreadCount)
	{
		d->mFile->close();

		QString path = d->mFile->fileName();
		const int length = path.length();
		if (length >= 4)
		{
			path.remove(length - 4, 4);
		}
		QFile::rename(d->mFile->fileName(), path);

		emit downloadProgress(DownloadProgress(d->mDownloadProgress.mBytesReceived,
			d->mDownloadProgress.mFileSize,
			d->mDownloadProgress.mFinishedCount,
			d->mDownloadProgress.mFinishedCount,
			d->mDownloadProgress.mThreadCount));

		emit finished();
	}
}

void QGSDownloadManager::downloadProgress(QGSDownloader::DownloadProgress progress)
{
	d->mDownloadProgress.mBytesReceived += progress.mBytesReceived;

	emit downloadProgress(DownloadProgress(d->mDownloadProgress.mBytesReceived,
		d->mDownloadProgress.mFileSize,
		d->mDownloadProgress.mFinishedCount,
		progress.mIndex,
		d->mDownloadProgress.mThreadCount));
}

QGSDownloadManager::~QGSDownloadManager()
{
	if (d)
	{
		delete d;
	}
	
	d = nullptr;
}
