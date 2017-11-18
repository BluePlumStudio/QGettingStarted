#include <QtCore/QCoreApplication>
#include <QDebug>
#include <iostream>
#include <string>

#include "QGSNetwork.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QGSNetwork * instance = QGSNetwork::getInstance();
	int type = 0;
	qDebug() << QString::fromLocal8Bit("QGSNetworkģ�鹦�ܲ��ԣ�0.�����¼���� 1.���ز��ԣ���");
	std::cin >> type;
	if (!type)
	{
		QGSAuthRequest::RequestData requestData;
		std::string userName;
		std::string password;
		qDebug() << QString::fromLocal8Bit("UserName��");
		std::cin >> userName;
		qDebug() << QString::fromLocal8Bit("Password��");
		std::cin >> password;
		requestData.mUserName = QString::fromLocal8Bit(userName.c_str());
		requestData.mPassword = QString::fromLocal8Bit(password.c_str());

		QGSAuthRequest request;
		request.setRequestData(requestData);

		QGSAuthReply * _reply = instance->post(request);
		//_reply->deleteLater();
		QObject::connect(_reply, &QGSAuthReply::finished,
			[=]()
		{
			QGSAuthReply::ReplyData replyData;
			QGSAuthReply::ReplyData::ReplyError replyError = _reply->getReplyData(replyData);

			qDebug() << QString::fromLocal8Bit("Json���ģ�");
			qDebug() << replyData.mData;
			qDebug() << QString::fromLocal8Bit("====================��");
			qDebug() << QString::fromLocal8Bit("������");
			qDebug() << QString::fromLocal8Bit("========����========��");
			qDebug() << replyError.mError;
			qDebug() << replyError.mErrorMessage;
			qDebug() << replyError.mCause;
			qDebug() << replyError.mErrorCode;
			qDebug() << QString::fromLocal8Bit("========��֤========��");
			qDebug() << replyData.mAccessToken;
			qDebug() << replyData.mClientToken;
			qDebug() << QString::fromLocal8Bit("=availableProfiles==��");
			for (auto it : replyData.mAvailableProfiles)
			{
				qDebug() << it.mID;
				qDebug() << it.mName;
				qDebug() << it.mLegacy;
			}
			qDebug() << QString::fromLocal8Bit("==selectedProfile===��");
			qDebug() << replyData.mSelectedProfile.mID;
			qDebug() << replyData.mSelectedProfile.mName;
			qDebug() << replyData.mSelectedProfile.mLegacy;

		});
	}
	else if (type == 1)
	{
		QGSDownloadRequest::RequestData requestData;
		//requestData.mPath = "./test.tmp";
		uint threadCount = 1;
		qDebug() << QString::fromLocal8Bit("������");
		std::string URL;
		std::cin >> URL;
		requestData.mURL = QString::fromLocal8Bit(URL.c_str());
		qDebug() << QString::fromLocal8Bit("�߳�����");
		std::cin >> threadCount;
		requestData.mThreadCount = threadCount;

		QGSDownloadRequest request(&requestData);
		QGSDownloadManager * manager = instance->get(request);
		if (!manager)
		{
			qDebug() << QString::fromLocal8Bit("��Ч�������ӣ�");
			return 1;
		}
		QObject::connect(manager, &QGSDownloadManager::finished,
			[=]()
		{
			qDebug() << QString::fromLocal8Bit("==========request��������ɣ�==========");
		});

		QObject::connect(manager, static_cast<void(QGSDownloadManager::*)(QGSDownloadManager::DownloadProgress downloadProgress)> (&QGSDownloadManager::downloadProgress),
			[=](QGSDownloadManager::DownloadProgress downloadProgress)
		{
			qDebug() << QString::fromLocal8Bit("==========downloadProgress��==========");
			qDebug() << QString::fromLocal8Bit("���գ��ֽڣ���") << downloadProgress.mBytesReceived;
			qDebug() << QString::fromLocal8Bit("�ļ���С���ֽڣ���") << downloadProgress.mFileSize;
			qDebug() << QString::fromLocal8Bit("�߳�������") << downloadProgress.mIndex;
			qDebug() << QString::fromLocal8Bit("����߳�����") << downloadProgress.mFinishedCount;
			qDebug() << QString::fromLocal8Bit("�߳�����") << downloadProgress.mThreadCount;
			qDebug() << QString::fromLocal8Bit("======================================");
		});
	}
	return a.exec();
}
