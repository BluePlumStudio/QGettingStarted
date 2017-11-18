#include "QGSNetwork.h"

#include <QEventLoop>
#include <QFileInfo>

class QGSNetwork::Private
{
public:
	Private(QGSNetwork * parent) :mManager(new QNetworkAccessManager(parent))
	{
		
	}

	~Private()
	{
		if (mManager)
		{
			mManager->deleteLater();
		}

		mManager = nullptr;
	}

public:
	QNetworkAccessManager * mManager;
};

/**/

QGSNetwork::QGSNetwork(QObject *parent) :QObject(parent), d(new QGSNetwork::Private(this))
{
	/*
	connect(d->mManager,
		&QNetworkAccessManager::finished,
		this,
		[=](QNetworkReply * reply)
	{
		emit finished(QGSAuthReply(reply));
	});
	*/
}

QGSNetwork * QGSNetwork::getInstance()
{
	static QGSNetwork instance;

	return &instance;
}

QNetworkReply * QGSNetwork::get(const QNetworkRequest & request)
{
	return d->mManager->get(request);
}

QNetworkReply * QGSNetwork::post(const QNetworkRequest & request, const QByteArray & data)
{
	return d->mManager->post(request, data);
}

QGSDownloadManager * QGSNetwork::get(QGSDownloadRequest & request)
{
	QGSDownloadRequest::RequestData requestData = request.getRequestData();//获取下载请求信息
	requestData.mURL = getRedirectURL(requestData.mURL);//获取重定向后的下载链接
	const qint64 fileSize = getFileSize(requestData.mURL);//获取文件总大小
	QFile * file = new QFile;

	if (fileSize <= 0 ||
		requestData.mThreadCount < 1 ||
		!file)
	{
		return nullptr;
	}

	//防止文件过小而请求线程数过多的问题
	if (!(fileSize / requestData.mThreadCount))
	{
		requestData.mThreadCount = 1;
	}
	
	QString fileName = requestData.mPath;
	//若用户未指定文件名
	if (fileName.isEmpty())
	{
		QFileInfo fileInfo(requestData.mURL.path());
		fileName = fileInfo.fileName();
		//若文件名解析失败
		if (fileName.isEmpty())
		{
			//手动分配文件名
			for (uint i = 0; i < UINT_MAX; i++)
			{
				fileName = "QGS_DOWNLOAD_TEMP_" + QString::number(i) + ".tmp";
				file->setFileName(fileName);
				if (!file->exists())
				{
					break;
				}
			}
		}
		else
		{
			file->setFileName(fileName + ".tmp");
		}
	}
	else
	{
		file->setFileName(fileName + ".tmp");
	}

	file->open(QIODevice::WriteOnly | QIODevice::Truncate);
	//若文件打开失败
	if (!file->isOpen())
	{
		file->deleteLater();
		file->close();
		return nullptr;
	}

	QGSDownloadManager * downloadManager = new QGSDownloadManager;
	if (!downloadManager)
	{
		file->deleteLater();
		file->close();
		return downloadManager;
	}
	//设置相关属性
	downloadManager->setThreadCount(requestData.mThreadCount);
	downloadManager->setFile(file);
	downloadManager->setFileSize(fileSize);

	QGSDownloader * downloader = nullptr;

	for (uint i = 0; i < requestData.mThreadCount; i++)
	{
		int start = fileSize * i / requestData.mThreadCount;
		int end = fileSize * (i + 1) / requestData.mThreadCount;

		if (i != 0)
		{
			start--;
		}

		downloader = new QGSDownloader(i);
		if (!downloader)
		{
			throw ExceptionBadAlloc();
			break;
		}

		connect(downloader, &QGSDownloader::downloadFinished, downloader, &QGSDownloader::deleteLater);
		
		downloadManager->addDownloader(downloader);
		
		downloader->startDownload(requestData.mURL, file, start, end);
	}

	return downloadManager;
}

QGSAuthReply * QGSNetwork::post(const QGSAuthRequest & request)
{
	QNetworkReply * reply = d->mManager->post(*request.getNetworkRequest(), request.getRequestMetaData());

	return new QGSAuthReply(reply);
}

qint64 QGSNetwork::getFileSize(QUrl URL)
{
	QEventLoop eventLoop;

	QNetworkReply * reply = d->mManager->head(QNetworkRequest(URL));
	QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit, Qt::DirectConnection);
	eventLoop.exec();

	qint64 size = 0;
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (statusCode == 302 && reply->hasRawHeader("Location"))
	{
		QString location = reply->rawHeader("Location");
		URL.setPath(location);
		size = getFileSize(URL);
	}
	else
	{
		size = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
	}

	reply->deleteLater();

	return size;
}

QUrl QGSNetwork::getRedirectURL(QUrl URL)
{
	QEventLoop eventLoop;

	QNetworkReply * reply = d->mManager->head(QNetworkRequest(URL));//获取重定向后的下载链接
	QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit, Qt::DirectConnection);
	eventLoop.exec();

	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (statusCode == 302 && reply->hasRawHeader("Location"))
	{
		QString location = reply->rawHeader("Location");
		URL.setPath(location);
	}

	return URL;
}

QGSNetwork::~QGSNetwork()
{
	if (d)
	{
		delete d;
	}
	d = nullptr;

}
