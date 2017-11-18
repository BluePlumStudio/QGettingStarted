/*
	Minecraft启动器Json解析库 Beta

		BluePlum Studio. 
*/
	//——lzycc234
	//——%.6f
	//——/*HCl*/

/*
	注意：
		1.可能会有致命BUG。
		2.有些函数、变量之类的命名不太好，日后会改善。
		。。。。。。
*/
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "GSGame.h"

std::string genUUID(std::string seed);//UUID生成


namespace gs
{


	class GSLauncher
	{
	public:
		GSLauncher();
		Status						getLaunchString(GSGame & launchGame, std::string & launchCommand);//获取完整启动命令
		~GSLauncher();
	public:							//Semicolon为是否要加入分号;来分割
		//std::string					getStyledLibrariesString(GSGame & launchGame, bool Semicolon = false);//获取格式化好的库文件字符串
		std::vector<std::string>	getStyledLibrariesStringVector(GSGame & launchGame, bool Semicolon = false);//获取格式化好的库文件字符串容器
		std::vector<GSLibrary>		getGSLibraryVector(GSGame & launchGame);
		std::string					getStyledMinecraftArgumentsString(GSGame & launchGame);//获取格式化好的MinecraftArguments
		bool						isFileExist(const char * fileName);//检查名为fileName的文件是否存在
		std::vector<std::string>	getMissingLibrariesStringVector(GSGame & launchGame, bool Semicolon = false);//获取丢失库文件路径
	private:
		bool replaceArgument(std::string & minecraftArguments, std::string argumentName, std::string replacement);//用于替换minecraftArguments的参数
	};

}




