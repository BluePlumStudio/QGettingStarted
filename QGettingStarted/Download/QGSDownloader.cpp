#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QTimer>

#include "QGSDownloader.h"
#include "QGSUuidGenerator.h"
#include "QGSOperatingSystem.h"

static const QString SEPARATOR{ QGSOperatingSystem::getInstance().getSeparator() };
static const QString DOWNLOADDIRNAME{ "QGSDownload" };

QGSDownloader::QGSDownloader(const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject *parent)
	: QObject(parent), mDownloadInfo(downloadInfo), mFile(nullptr), mReply(nullptr), mProxy(proxy), mState(State::Stop), mDelete(false), mBytesReceived(0)
{

}

QGSDownloader::~QGSDownloader()
{
}

bool QGSDownloader::start()
{
	if (mState == State::Start)
	{
		return false;
	}
	auto request{ QGSNetwork::generateNetworkRequestWithSSL() };
	//���Url�Ƿ�Ϊ���Լ���Ч
	auto && url{ mDownloadInfo.getUrl() };
	if(!url.isValid()
		|| url.isEmpty()
		|| url.isLocalFile())
	{
		return false;
	}

	request.setUrl(url);
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	mDownloadInfo.setUrl(url);

	//�������·��
	QDir downloadDirectory{ QCoreApplication::applicationDirPath() + SEPARATOR + DOWNLOADDIRNAME };
	if(mDownloadInfo.getPath().isEmpty())
	{
		QFileInfo fileInfo{ url.toString() };

		if (!downloadDirectory.exists())
		{
			if (!downloadDirectory.mkpath(QCoreApplication::applicationDirPath() + SEPARATOR + DOWNLOADDIRNAME))
			{
				return false;
			}
		}

		mDownloadInfo.setPath(downloadDirectory.absolutePath() + SEPARATOR + fileInfo.fileName());
		
	}

	//���ļ�
	if (!mFile.isOpen())
	{
		mFile.setFileName(downloadDirectory.absolutePath() + SEPARATOR + generateRandomFileName());
		if (!mFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			return false;
		}
	}

	//��ʼ����
	if (mBytesReceived)
	{
		QString strRange = QString("bytes=%1-").arg(mBytesReceived);
		request.setRawHeader("Range", strRange.toLatin1());
	}
	mReply = QGSNetwork::getInstance().getManager()->get(request);

	connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
	connect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
	connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
	connect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
	connect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
	connect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
	mTimer.start(12000);

	mState = State::Start;
	return true;
}

bool QGSDownloader::stop()
{
	mState = State::Stop;

	mFile.flush();
	mBytesReceived = mFile.size();
	disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
	disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
	disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
	disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
	disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
	disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
	mReply->deleteLater();
	mReply = nullptr;

	return true;
}

bool QGSDownloader::cancel()
{
	mState = State::Stop;

	mFile.flush();
	mFile.close();
	mBytesReceived = 0;
	mDelete = false;
	mFile.remove();
	disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
	disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
	disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
	disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
	disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
	disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
	mReply->deleteLater();
	mReply = nullptr;

	return true;
}

QFile * QGSDownloader::generateFile() const
{
	return new QFile{ mFile.fileName() };
}

QFile & QGSDownloader::getFile()
{
	return mFile;
}

QGSDownloader::State QGSDownloader::getState() const
{
	return mState;
}

void QGSDownloader::slotFinished()
{
	mFile.flush();
	mFile.close();
	QFile::remove(mDownloadInfo.getPath());
	mFile.rename(mDownloadInfo.getPath());
	if (!mDownloadInfo.getSHA1().isEmpty())
	{
		//�ļ�SHA1���
	}
	if (mDelete)
	{
		mFile.remove();
	}
	mReply->deleteLater();
	mReply = nullptr;

	emit finished();
}

void QGSDownloader::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	mTimer.start(12000);

	auto receivedData{ mReply->readAll() };
	mFile.write(receivedData);
	mFile.flush();

	emit downloadProgress(mBytesReceived + bytesReceived, bytesTotal);
}

void QGSDownloader::slotError(QNetworkReply::NetworkError code)
{
	emit error(Error{ code,mReply->errorString() });
}

void QGSDownloader::slotSslErrors(const QList<QSslError>& errors)
{
	emit sslErrors(errors);
}

void QGSDownloader::slotTimeout()
{
	stop();
	emit timeout();
}

void QGSDownloader::slotRedirected(const QUrl & url)
{
	QFileInfo fileInfo{ url.toString() };
	QDir downloadDirectory{ QCoreApplication::applicationDirPath() + SEPARATOR + DOWNLOADDIRNAME };
	mDownloadInfo.setPath(downloadDirectory.absolutePath()
		+ SEPARATOR + fileInfo.fileName());
}

QString QGSDownloader::generateRandomFileName()
{
	return QString{ QGSUuidGenerator::generateUuid() + ".tmp" };
}
