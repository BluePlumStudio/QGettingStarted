#ifndef GOJOBZIP_H
#define GOJOBZIP_H

#include <QFile>
#include <QFile>
#include <QtCore> 
#include <QCoreApplication>
#include <QObject>

//#include "inc_ato.h"
#include "quazip.h"
#include "quazipfile.h"

#include <QList>
#include <QString>

static  QList<QString> zipList;


#include <iostream>
#include <stdio.h>

using namespace std;

#ifdef STDC
#  include <string.h>
#  include <stdlib.h>
#endif

#ifdef USE_MMAP
#  include <sys/types.h>
#  include <sys/mman.h>
#  include <sys/stat.h>
#endif

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#ifdef VMS
#  define unlink delete
#  define GZ_SUFFIX "-gz"
#endif
#ifdef RISCOS
#  define unlink remove
#  define GZ_SUFFIX "-gz"
#  define fileno(file) file->__file
#endif
#if defined(__MWERKS__) && __dest_os != __be_os && __dest_os != __win32_os
#  include <unix.h> /* for fileno */
#endif


#ifndef GZ_SUFFIX
#  define GZ_SUFFIX ".gz"
#endif
#define SUFFIX_LEN (sizeof(GZ_SUFFIX)-1)

#define BUFLEN      16384
#define MAX_NAME_LEN 1024

#ifdef MAXSEG_64K
#  define local static
   /* Needed for systems with limitation on stack size. */
#else
#  define local
#endif




//QList<QString> getList()
//{
//    QList<QString> zipList;
//}

extern inline QString  BiteorMega( int peso  )
{
    QString humanread;
    double canno = peso / 1024;
    int sale = canno;
    if (peso > 0) {
        if (canno < 1) {
           sale = 1; 
        }
    }
    
   if (sale < 1025) {
   humanread = QString("Kb.%1").arg(sale);
   return humanread;
   }
   
   float megad = sale / 1024;
   
   if (megad < 1025) {
   humanread = QString("MB.%1").arg(megad);
   return humanread;
   } else {
   humanread = QString("GB.1+"); 
   }
   
return humanread;
}

extern inline bool is_file(QString fullFileName)
{
    if (!fullFileName.size() > 0) {
      return false;  
    }
    QDir diro(fullFileName);
       if (diro.exists()) {
         return false;   
       }
    QFile f( fullFileName );
	if ( f.exists(fullFileName) ) {
    return true;  
	} else {
	return false;
    }
}

extern inline void gz_compress( FILE   *in , gzFile out ) 
{
    local char buf[BUFLEN];
    int len;
    ///////int err;
    
    for (;;) {
        len = (int)fread(buf, 1, sizeof(buf), in);
        if (ferror(in)) {
            perror("fread");
            exit(1);
        }
        if (len == 0) break;

        if (gzwrite(out, buf, (unsigned)len) != len) {
         return;   
        }
    }
    fclose(in);
    if (gzclose(out) != Z_OK) {
     return;
    }
}


extern inline bool  MakeGzipOneFile( QString filelocation )
{
    local char outfile[MAX_NAME_LEN];
    FILE  *in;
    gzFile out;
    QByteArray cgofile = filelocation.toLatin1();
    char* file = cgofile.data();
    QString const busgo = filelocation.append(GZ_SUFFIX);
    strcpy(outfile, file);
    strcat(outfile, GZ_SUFFIX);   /* attach suffix */
    in = fopen(file, "rb");
    
    if (in == NULL) {
     return false;
    }
    out = gzopen(outfile,"wb6");
    if (out == NULL) {
      fclose( in );
      return false;
    }
    gz_compress(in, out);
    
    QFile f( busgo );
    return f.exists(busgo);
}




static inline bool  UnzipTo( const QString zipfile, const QString outputdir )
{
    zipList.clear();
    ///////////// const QString cartella = QDir::currentPath();
     /////////qDebug() << "### from unzzip function path " <<  QDir::currentPath();
   /////////// qDebug() << "### outputdir " <<  outputdir;
    //////////qDebug() << "### zipfile " <<  zipfile;
    char* suk;
    QuaZip zip(zipfile);
    bool extractsuccess = false;
    zip.open(QuaZip::mdUnzip);
    QuaZipFile file(&zip);
    for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) 
	{
        file.open(QIODevice::ReadOnly);
        QString name = zip.getCurrentFileName();
        name.prepend(outputdir);   /* extract to path ....... */
        QFile meminfo(name);
        QFileInfo infofile(meminfo);
        QDir dira(infofile.absolutePath());
        if ( dira.mkpath(infofile.absolutePath()) ) 
		{ 
			/* dir is exist*/
        /////////qDebug() << "### name  " << name;     
        /////qDebug() << "### namedir yes  " << infofile.absolutePath();
                              
			QString fileqinfo = zip.getCurrentFileName();
			zipList.append(fileqinfo);

			QByteArray fe = fileqinfo.toLatin1();
			suk = fe.data();

			cout <<  "Processing..... " << suk << "\n";   
               
            if ( meminfo.open(QIODevice::WriteOnly | QIODevice::Truncate) ) 
			{
				meminfo.write(file.readAll());   /* write */
				meminfo.close();
				extractsuccess = true;
				//////////RegisterImage(name);
            }
        } 
		else 
		{
			file.close();
			return false;               
        }
        file.close(); // do not forget to close!
    }
    zip.close();
    
	return extractsuccess;
}


class PackZip : public QObject
{
    Q_OBJECT
    
public:
PackZip()
{
startnow = QDir::currentPath();
} 
~PackZip()
{
QDir::setCurrent(startnow);
}
void SetJob( const QString packfolder , const QString zipoutfolder )
{
    
  startdir = packfolder;   /* grab all this file */
  zipdir = zipoutfolder;   /* save zip to this dir */
  startnow = QDir::currentPath();
  Init();
}

private:
void Init()
{
    canmake = false;
    if (!zipdir.contains("/")) {
        ResetDir();
        return;
    }
    if (!zipdir.endsWith("/")) {
        ResetDir();
       return; 
    }
    if (!startdir.contains("/")) {
        ResetDir();
        return;
    }
    if (!startdir.endsWith("/")) {
       ResetDir();
       return; 
    }
    canmake = true;
    QDir dir(startdir);
    char c;
    char* suk;
    qreal cento;
    qreal percentuale;
    QString dirname = dir.dirName();
    selfname = dirname + ".zip";
    zipfile = zipdir;
    zipfile.append(dirname);
    zipfile.append(".zip");
    
    QFile zcheck(zipfile);
     if (zcheck.exists()) {
      zcheck.remove();
     }
    
    dirandfile.clear();
    IndexDir(startdir);
    if (dirandfile.size() > 0) {
        
      QuaZip zip(zipfile);
      if(!zip.open(QuaZip::mdCreate)) {
      ResetDir();
      return;
      }
      
      QuaZipFile outFile(&zip);
      
      int totalf = dirandfile.size();
      
       ///////qDebug() << "### totalfile " <<  dirandfile.size();
         for (int i = 0; i < dirandfile.size(); ++i) {
             QString filepak = dirandfile.at(i);
             const  QString abse = filepak;
             const  QString goname = filepak.replace(startdir,"");
             
             QFile inFile(abse);
                   inFile.setFileName(abse);
             
             if(!inFile.open(QIODevice::ReadOnly)) {
              ResetDir();
              return;
             }
             
              if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(goname, inFile.fileName()))) {
              ResetDir();
              return;
              }
              
               while(inFile.getChar(&c)&&outFile.putChar(c));
                if(outFile.getZipError()!=UNZ_OK) {
                  ResetDir();
                  return;
                }
                
                outFile.close();
                if(outFile.getZipError()!=UNZ_OK) {
                ResetDir();
                return;
                }
                inFile.close();
                cento = 100;
                percentuale = i*cento/totalf;
                int status = percentuale;
                emit Status(status);
                
                
                QString fileqinfo = goname;
                        fileqinfo.append(" ");
                        fileqinfo.append(BiteorMega(inFile.size()));
                QByteArray fe = fileqinfo.toLatin1();
                suk = fe.data();
                
                             cout <<  "Status. " << percentuale << "% " << suk << "\n";
                             /////fflush ( stdin );
             
             ////////qDebug() << "### status " <<  status;
             //////////qDebug() << "### d " <<  goname;
         }
        
          zip.close();
          if(zip.getZipError()!=0) {
          QDir::setCurrent(startnow);
          }
          
          
          
          
          QFile re(zipfile);
          
           QString fr = re.fileName();
                        fr.append(" ");
                        fr.append(BiteorMega(re.size()));
          
          QByteArray fe = fr.toLatin1();
                suk = fe.data();
          
          cout <<  "End file " << suk << "\n";
          ///////qDebug() << "### status 100";
          emit Status(100);
          emit ZipEnd(zipfile);
          return;
          /////////////qDebug() << "### emitend " <<  zipfile;
    }
emit ZipError();
}
void ResetDir()
{
    emit ZipError();
    QDir::setCurrent(startnow);
}
void IndexDir(const QString d)
{
   QDir dir(d);
   if (dir.exists())
   {
      const QFileInfoList list = dir.entryInfoList();
      QFileInfo fi;
      for (int l = 0; l < list.size(); l++)
      {
         fi = list.at(l);
         if (fi.isDir() && fi.fileName() != "." && fi.fileName() != "..") {
            IndexDir(fi.absoluteFilePath());
         } else if (fi.isFile() && fi.fileName() != selfname ) {
            dirandfile.append(fi.absoluteFilePath());
         } 
        
      }
   }
}
    QString startnow;
    QStringList dirandfile;
    QString startdir;
    QString zipdir;
    QString zipfile;
    QString selfname;
    bool canmake;
signals:
    void ZipEnd( QString fileresult );
    void ZipError();
    void Status(int o );
public slots:

};







//
#endif // GOJOBZIP_H

