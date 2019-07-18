#pragma once

#include <QDir>
#include <QFile>
#include <QVector>

#include "../GameVersion/QGSGameVersion.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

/**

* @brief 游戏目录

*/
class QGSGameDirectory :public QObject
{
	Q_OBJECT

public:
	/**

	* @brief QGSGameDirectory构造函数

	* @param baseDir 游戏目录

	* @param parent 父对象

	* @return

	* @retval

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionIO：相关文件或目录创建失败

	*/
	QGSGameDirectory(const QDir & baseDir, QObject * parent = nullptr);

	/**

	* @brief QGSGameDirectory构造函数

	* @param baseDir 游戏目录

	* @param parent 父对象

	* @return

	* @retval

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionIO：相关文件或目录创建失败

	*/
	QGSGameDirectory(QDir && baseDir, QObject * parent = nullptr);

	QGSGameDirectory(const QGSGameDirectory & right) = default;

	QGSGameDirectory(QGSGameDirectory && right) = default;

	QGSGameDirectory & operator=(const QGSGameDirectory & right) = default;

	QGSGameDirectory & operator=(QGSGameDirectory && right) = default;

	virtual ~QGSGameDirectory();

	/**

	* @brief 获取游戏版本

	* @param version 游戏版本

	* @return 游戏版本

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound：version为空 
				QGSExceptionVersionNotFound：找不到版本 
				QGSExceptionIO：IO异常
				QGSExceptionJsonPraseError：json解析错误

	*/
	const QGSGameVersion & getVersion(const QString & version);

	/**

	* @brief 获取游戏版本

	* @param gameVersionInfo 游戏版本信息

	* @return 游戏版本

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound：version为空 
				QGSExceptionVersionNotFound：找不到版本 
				QGSExceptionIO：IO异常
				QGSExceptionJsonPraseError：json解析错误

	*/
	const QGSGameVersion & getVersion(const QGSGameVersionInfo & gameVersionInfo);

	/**

	* @brief 添加版本

	* @param version 游戏版本

	* @return 自身引用

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound：version为空 
				QGSExceptionVersionNotFound：找不到版本 
				QGSExceptionIO：IO异常
				QGSExceptionJsonPraseError：json解析错误

	*/
	const QGSGameVersion & addGameVersion(const QString version);

	/**

	* @brief 添加版本

	* @param gameVersionInfo 游戏版本信息

	* @return 自身引用

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound：version为空
	QGSExceptionVersionNotFound：找不到版本
	QGSExceptionIO：IO异常
	QGSExceptionJsonPraseError：json解析错误

	*/
	const QGSGameVersion & addGameVersion(const QGSGameVersionInfo & gameVersionInfo);

	bool containsGameVersion(const QString & version)const;

	bool containsGameVersion(const QGSGameVersionInfo & gameVersionInfo)const;

	QFile * generateGameVersionJarFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJarFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const QGSAssetIndex & assetIndex, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const QString & version, const bool withAbsolutePath = true);

	QFile * generateAssetIndexJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true);

	QFile * generateLibraryFile(const QGSLibrary & library, const bool withAbsolutePath = true)const;

	QVector<QFile *> generateLibraryFiles(const QList<QGSLibrary> & libraryList, const bool withAbsolutePath = true)const;

	QDir generateVersionsDirectory(const bool withAbsolutePath = true)const;

	QDir generateLibrariesDirectory(const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QString & version, const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QDir getBaseDir()const;

	static QString praseLibraryName(const QGSLibrary & library);

	static QString praseName(const QString & name);

	/*need to be updated*/
	bool generateAssetsDirectory(QString version, const QGSAssetIndex & assetIndex, QDir & dir);

	QDir generateAssetsDirectory(const bool withAbsolutePath = true);

	QFile * generateAssetObjectFile(const QGSAssetObject & assetObject, const bool withAbsolutePath = true);
private:
	void init();

private:
	QMap<QString, QGSGameVersion> mVersionMap;
	QDir mBaseDir;
};