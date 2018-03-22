#include "QGSThread.h"
#include "QGSThreadPool.h"

QGSThread::QGSThread(QGSThreadPool * threadPool) :mThreadPoolPtr(threadPool)
{
	if (!threadPool)
	{

	}
}

QGSThread::~QGSThread()
{

}

void QGSThread::run()
{
	if (!mThreadPoolPtr)
	{
		//exception
	}

	QEventLoop eventLoop;

	while (true)
	{
		mThreadPoolPtr->mMutex.lock();
		//�������Ƿ�������
		if (!mThreadPoolPtr->mTaskQueue.size() && !mThreadPoolPtr->mReleaseThreads)
		{
			mThreadPoolPtr->mTaskQueueNotEmptyCondition.wait(&mThreadPoolPtr->mMutex);
		}
		//�̳߳��˳����߳��ͷ�
		if (mThreadPoolPtr->mReleaseThreads || mThreadPoolPtr->mWaitReleasedThreadCount)
		{
			mThreadPoolPtr->mCurrentThreadCount--;
			mThreadPoolPtr->mWaitReleasedThreadCount--;
			mThreadPoolPtr->mMutex.unlock();
			exit(0);
			qDebug() << "Thread:" << this << "released!";
			break;
		}
		//����Ƿ������������е�����
		if (mThreadPoolPtr->mTaskQueueBlock)
		{
			mThreadPoolPtr->mMutex.unlock();
			continue;
		}
		//��ȡ����
		auto * task{ mThreadPoolPtr->mTaskQueue.front() };
		//qDebug() << "Current task queue size:" << mThreadPoolPtr->mTaskQueue.size();
		mThreadPoolPtr->mTaskQueue.pop_front();
		mThreadPoolPtr->mTaskQueueBlock = task->isTaskQueueBlock();
		//����������δ��
		/*
		signals:
		void started(QGSTask * task);
		void finished(QGSTask * task);
		void stoped(QGSTask * task);
		void canceled(QGSTask * task);
		void error(QGSTask * task);
		*/
		QObject::connect(task, &QGSTask::finished, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::canceled, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::error, &eventLoop, &QEventLoop::quit);
		QObject::connect(this, &QGSThread::taskStart, task, &QGSTask::start);
		mThreadPoolPtr->mMutex.unlock();
		//����
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount++;
		mThreadPoolPtr->mAttribMutex.unlock();
		//����ʼ
		emit taskStart(task);
		eventLoop.exec();
		QObject::disconnect(this, &QGSThread::taskStart, task, &QGSTask::start);
		//�����ǰ����Ϊ�������е�����
		if (task->isTaskQueueBlock())
		{
			mThreadPoolPtr->mMutex.lock();
			//������ɣ��������
			mThreadPoolPtr->mTaskQueueBlock = false;
			mThreadPoolPtr->mMutex.unlock();
		}
		//qDebug() << "Current task finished:" << task;
		//����
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount--;
		mThreadPoolPtr->mAttribMutex.unlock();
	}
}
