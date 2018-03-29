#pragma once

#include <QUrl>
#include <QString>

class QGSLiteLoaderVersionReposity
{
public:
	QGSLiteLoaderVersionReposity(const QString & stream = "", const QString & type = "", const QUrl & url = QUrl(), const QString & classifier = "");

	QGSLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & right) = default;

	QGSLiteLoaderVersionReposity(QGSLiteLoaderVersionReposity && right) = default;

	QGSLiteLoaderVersionReposity & operator=(const QGSLiteLoaderVersionReposity & right) = default;

	QGSLiteLoaderVersionReposity & operator=(QGSLiteLoaderVersionReposity && right) = default;

	~QGSLiteLoaderVersionReposity();

	QString getStream()const;
	QString getType()const;
	QUrl getUrl()const;
	QString getClassifier()const;

	QGSLiteLoaderVersionReposity & setStream(const QString & stream);
	QGSLiteLoaderVersionReposity & setType(const QString & type);
	QGSLiteLoaderVersionReposity & setUrl(const QUrl & url);
	QGSLiteLoaderVersionReposity & setClassifier(const QString & classifier);
private:
	QString mStream;
	QString mType;
	QUrl mUrl;
	QString mClassifier;
};
