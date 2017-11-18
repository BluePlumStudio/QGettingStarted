#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

enum Status//各种运行结果
{
    NO_ERROR,//没啥错误
    INVALID_VALUE,//无效值
    INVALID_OPERATION,//无效操作
    FAILED_OPERATION//操作失败

};

std::string readFile(const char * fileName, std::string & str);//读取文件内容到str

namespace gs
{
	class GSLibrary
	{
	public:
		GSLibrary();
		~GSLibrary();

	public:
		std::string name;
		std::string path;
		std::string url;

	};



	struct GSGame
	{
	public:
		GSGame();
		GSGame(const GSGame & right);

		Status init(std::string gameVersion/*完整版本号，如：1.11.2*/,
			std::string gamePath = ".minecraft"/*.minecraft的路径，推荐写带盘符完整路径*/);//初始化

		bool            isInit()const;			//是否被初始化，保证只初始化一次

		GSGame *			getFatherPtr()const;	//获取父版本（GSGame）的指针

		std::string		getJsonFilePath()const;	//获取Json文件路径

		std::string		getGamePath()const;		//获取游戏路径
		std::string		getJavaPath()const;		//获取Java路径
		std::string		getVersion()const;		//获取版本号
		std::string		getNativePath()const;	//获取Native文件夹路径
		std::string		getPlayerName()const;	//获取用户名
		std::string		getUserType()const;		//获取用户类型（正版/离线）
		std::string		getExtraArgument()const;//获取额外参数
		int				getXmn()const;			//获取最小内存（MB）
		int				getXmx()const;			//获取最大内存（MB）

		void			setJavaPath(std::string javaPath);
		void			setNativePath(std::string nativePath);
		void			setPlayerName(std::string playerName);
		void			setUserType(std::string userType);
		void			setExtraArgument(std::string extraArgument);
		void			setXmn(int Xmn);
		void			setXmx(int Xmx);
		GSGame &			operator=(GSGame & right);//=操作符重载

		
		~GSGame();
	public:
		rapidjson::Document jsonRoot;	//Json
    private:
        bool				inited;		//是否被初始化

		GSGame *				father;			//继承游戏版本

		std::string			jsonFilePath;	//json文件路径

		std::string			version;		//游戏版本
		std::string			path;			//游戏路径
		std::string			javaPath;		//Java路径
		std::string			nativePath;		//native文件夹路径
		std::string			playerName;		//用户名
		std::string			userType;		//用户类型
		std::string			extraArgument;	//额外参数
		int					Xmn;			//最小内存
		int					Xmx;			//最大内存
	};
}
