#pragma once

#include <QDir>
#include <QFile>
#include <QVector>

#include "../GameVersion/QGSGameVersion.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

/**

* @brief ��ϷĿ¼

*/
class QGSGameDirectory :public QObject
{
	Q_OBJECT

public:
	/**

	* @brief QGSGameDirectory���캯��

	* @param baseDir ��ϷĿ¼

	* @param parent ������

	* @return

	* @retval

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionIO������ļ���Ŀ¼����ʧ��

	*/
	QGSGameDirectory(const QDir & baseDir, QObject * parent = nullptr);

	/**

	* @brief QGSGameDirectory���캯��

	* @param baseDir ��ϷĿ¼

	* @param parent ������

	* @return

	* @retval

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionIO������ļ���Ŀ¼����ʧ��

	*/
	QGSGameDirectory(QDir && baseDir, QObject * parent = nullptr);

	QGSGameDirectory(const QGSGameDirectory & right) = default;

	QGSGameDirectory(QGSGameDirectory && right) = default;

	QGSGameDirectory & operator=(const QGSGameDirectory & right) = default;

	QGSGameDirectory & operator=(QGSGameDirectory && right) = default;

	virtual ~QGSGameDirectory();

	/**

	* @brief ��ȡ��Ϸ�汾

	* @param version ��Ϸ�汾

	* @return ��Ϸ�汾

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound��versionΪ�� 
				QGSExceptionVersionNotFound���Ҳ����汾 
				QGSExceptionIO��IO�쳣
				QGSExceptionJsonPraseError��json��������

	*/
	const QGSGameVersion & getVersion(const QString & version);

	/**

	* @brief ��ȡ��Ϸ�汾

	* @param gameVersionInfo ��Ϸ�汾��Ϣ

	* @return ��Ϸ�汾

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound��versionΪ�� 
				QGSExceptionVersionNotFound���Ҳ����汾 
				QGSExceptionIO��IO�쳣
				QGSExceptionJsonPraseError��json��������

	*/
	const QGSGameVersion & getVersion(const QGSGameVersionInfo & gameVersionInfo);

	/**

	* @brief ��Ӱ汾

	* @param version ��Ϸ�汾

	* @return ��������

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound��versionΪ�� 
				QGSExceptionVersionNotFound���Ҳ����汾 
				QGSExceptionIO��IO�쳣
				QGSExceptionJsonPraseError��json��������

	*/
	const QGSGameVersion & addGameVersion(const QString version);

	/**

	* @brief ��Ӱ汾

	* @param gameVersionInfo ��Ϸ�汾��Ϣ

	* @return ��������

	* @retval const QGSGameVersion &

	* @note

	* @attention

	* @warning

	* @exception QGSExceptionVersionNotFound��versionΪ��
	QGSExceptionVersionNotFound���Ҳ����汾
	QGSExceptionIO��IO�쳣
	QGSExceptionJsonPraseError��json��������

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