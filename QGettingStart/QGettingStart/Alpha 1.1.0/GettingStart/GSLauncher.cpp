#include "GSLauncher.h"

using namespace std;

string genUUID(string seed)
{
	string UUID = "";
	char * code = "x@&asd%j2813";
	char UUIDChars[] = "bad260ecde3bfe752a";
	int i = 0;
	
	if (seed.empty())
	{
		return "";
	}

	while (UUID.length() < 32)
	{
		char c1 = 0;
		char c2 = 0;
		char c = 0;
		
		srand(seed[(i + code[i % strlen(code)]) % seed.length()] + i);
		c1 = 'a' + rand() % 6;
		c2 = '0' + rand() % 10;
		c = rand() % 32;
		if (c>16)
		{
			if (rand() % 2)
			{
				UUID.push_back(c1);
			}
			else
			{
				UUID.push_back(c2);
			}
		}
		else
		{
			UUID.push_back(UUIDChars[c]);
		}


		i = (i + 1) % 65536;
	}
#ifdef _DEBUG
	printf("DEBUG：UUID：%s\n", UUID.c_str());
#endif
	return UUID;
}

namespace gs
{
	GSLauncher::GSLauncher()
	{
	}

	Status GSLauncher::getLaunchString(GSGame & launchGame, string & launchCommand)
	{
		string minecraftArguments = "";
		string mainClass = "";			//json中的mainClass一项
		string librariesString = "";
		string finalJarFileName = "";	//启动主jar文件名
		vector<string> librariesStringVector;
		GSGame * gamePtr = &launchGame;	//开头的一些参数
		char arguments[2048] = "";
		launchCommand = "";				

		if ((launchGame.getGamePath().empty()) | (launchGame.getJavaPath().empty()) | (launchGame.getNativePath().empty()) | (launchGame.getPlayerName().empty()) | (launchGame.getUserType().empty()) | (launchGame.getVersion().empty()) | (launchGame.getXmx() < launchGame.getXmn()))
		{
#ifdef _DEBUG
			printf("DEBUG：启动参数不全\n");
#endif
			return INVALID_VALUE;
		}

		librariesStringVector = getStyledLibrariesStringVector(launchGame, false);//获取libraries列表，先不需要分号;，因为下面要检查是否存在;
		launchCommand = launchCommand + "\"" + launchGame.getJavaPath() + "\"" + " ";//拼接上Java路径，因为文件名可能有空格，需要另外加""号
		strcat(arguments, launchGame.getExtraArgument().c_str());//拼接上额外参数
		if (launchGame.getXmn() > 0)//检查是否有填有效最小内存
		{
			char temp[64] = "";
			sprintf(temp, " -Xmn%dm", launchGame.getXmn());
			strcat(arguments, temp);//拼接
		}
		if (launchGame.getXmx() > 0)//检查是否有填有效最大内存
		{
			char temp[64] = "";
			sprintf(temp, " -Xmx%dm", launchGame.getXmx());
			strcat(arguments, temp);//拼接
		}
		launchCommand = launchCommand + arguments;//arguments的任务完成，拼接
		launchCommand = launchCommand + " \"-Djava.library.path=" + launchGame.getNativePath() + "\" -Dfml.ignoreInvalidMinecraftCertificates=true -Dfml.ignorePatchDiscrepancies=true -cp \"";//拼接必要参数
		for (unsigned i = 0; i < librariesStringVector.size(); i++)
		{
			string tempLibrariesString = librariesStringVector[i];
			if (isFileExist(tempLibrariesString.c_str()))//检查是否存在
			{
				librariesString = librariesString + librariesStringVector[i] + ";";//加入分号并拼接在一起
			}
		}
		launchCommand = launchCommand + librariesString;//拼接
		minecraftArguments = getStyledMinecraftArgumentsString(launchGame);//拼接minecraftArguments
		mainClass = launchGame.jsonRoot["mainClass"].GetString();//获取json的mainClass项，启动的主类

		while (gamePtr)
		{
			finalJarFileName = gamePtr->getVersion();//获取需要的.jar文件的最后一项，因为有的继承版本不一定都有.jar文件，就要一层一层查，直到查到最近的一层
			if (isFileExist((launchGame.getGamePath() + "/versions/" + finalJarFileName + "/" + finalJarFileName + ".jar").c_str()))
			{
				break;
			}
			gamePtr = gamePtr->getFatherPtr();
		}

		if (finalJarFileName.empty())//是否有
		{
			return FAILED_OPERATION;//最后的.jar文件缺失，返回失败的操作
		}

		launchCommand = launchCommand + launchGame.getGamePath() + "/versions/" + finalJarFileName + "/" + finalJarFileName + ".jar\" " + mainClass + " " + minecraftArguments;//拼接上最后的.jar文件，启动主类，和参数

#ifdef _DEBUG
		cout << "DEBUG：" << launchCommand << endl;
#endif
		return NO_ERROR;//成功，无错误
	}
	/*
	string GSLauncher::getStyledLibrariesString(GSGame & launchGame, bool Semicolon)
	{
		string librariesString = "";//全Libraries字符串
		GSGame * gamePtr = &launchGame;
		do
		{
			for (unsigned int i = 0; i < gamePtr->jsonRoot["libraries"].Size(); i++)
			{
				string originalName = gamePtr->jsonRoot["libraries"][i]["name"].GetString();//刚获取到的转为string的name项（name项具体看各版本json文件）
				string libraryPath = gamePtr->getGamePath() + "/libraries/";//组合成完成的libraries文件夹路径
				string libraryRootPath = originalName;//这两个要互相组合使用
				string fileName = "";//转换完的.jar文件名
				int location = 0;
				int End = 0;

				End = libraryRootPath.find(":");
				while ((location = libraryRootPath.find(".", location)) != string::npos)
				{
					if (location >= End)
					{
						break;
					}
					libraryRootPath[location] = '/';
				}

				location = 0;
				while ((location = libraryRootPath.find(":", location)) != string::npos)
				{
					libraryRootPath[location] = '/';
				}

				location = originalName.find(":", 0);
				fileName = originalName.substr(location + 1);
				location = 0;
				while ((location = fileName.find(":", location)) != string::npos)
				{
					fileName[location] = '-';
				}

				libraryPath = libraryPath + libraryRootPath + "/" + fileName + ".jar";

				if (Semicolon)//是否要加;分割
				{
					libraryPath = libraryPath + ";";
				}
				librariesString += libraryPath;
			}

		} while (gamePtr = gamePtr->getFatherPtr());//先执行一次，在检查有没有继承的版本


		return librariesString;
	}
	*/
	vector<string> GSLauncher::getStyledLibrariesStringVector(GSGame & launchGame, bool Semicolon)
	{
		vector<string> librariesStringVector;
		GSGame * gamePtr = &launchGame;

		librariesStringVector.clear();
		do
		{
			for (unsigned int i = 0; i < gamePtr->jsonRoot["libraries"].Size(); i++)
			{
				string originalName = gamePtr->jsonRoot["libraries"][i]["name"].GetString();
				string libraryPath = gamePtr->getGamePath() + "/libraries/";
				string libraryRootPath = originalName;
				string fileName = "";
				int location = 0;
				int End = 0;

				End = libraryRootPath.find(":");
				while ((location = libraryRootPath.find(".", location)) != string::npos)
				{
					if (location >= End)
					{
						break;
					}
					libraryRootPath[location] = '/';
				}

				location = 0;
				while ((location = libraryRootPath.find(":", location)) != string::npos)
				{
					libraryRootPath[location] = '/';
				}

				location = originalName.find(":", 0);
				fileName = originalName.substr(location + 1);
				location = 0;
				while ((location = fileName.find(":", location)) != string::npos)
				{
					fileName[location] = '-';
				}

				libraryPath = libraryPath + libraryRootPath + "/" + fileName + ".jar";

				if (Semicolon)
				{
					libraryPath = libraryPath + ";";
				}
				librariesStringVector.push_back(libraryPath);
			}

		} while (gamePtr = gamePtr->getFatherPtr());


		return librariesStringVector;
	}

	vector<GSLibrary>	GSLauncher::getGSLibraryVector(GSGame & launchGame)
	{
		vector<GSLibrary> librariesVector;

		librariesVector.clear();

		//string librariesString = "";//全Libraries字符串
		GSGame * gamePtr = &launchGame;
		do
		{
			for (unsigned int i = 0; i < gamePtr->jsonRoot["libraries"].Size(); i++)
			{
				GSLibrary library;
				string originalName = gamePtr->jsonRoot["libraries"][i]["name"].GetString();//刚获取到的转为string的name项（name项具体看各版本json文件）
				string libraryPath = gamePtr->getGamePath() + "/libraries/";//组合成完成的libraries文件夹路径
				string libraryRootPath = originalName;//这两个要互相组合使用
				string fileName = "";//转换完的.jar文件名
				int location = 0;
				int End = 0;

				End = libraryRootPath.find(":");
				while ((location = libraryRootPath.find(".", location)) != string::npos)
				{
					if (location >= End)
					{
						break;
					}
					libraryRootPath[location] = '/';
				}

				location = 0;
				while ((location = libraryRootPath.find(":", location)) != string::npos)
				{
					libraryRootPath[location] = '/';
				}

				location = originalName.find(":", 0);
				fileName = originalName.substr(location + 1);
				location = 0;
				while ((location = fileName.find(":", location)) != string::npos)
				{
					fileName[location] = '-';
				}

				libraryPath = libraryPath + libraryRootPath + "/" + fileName + ".jar;";
				library.name = fileName;
				library.path = libraryPath;
				library.url = gamePtr->jsonRoot["libraries"][i].HasMember("url") ? gamePtr->jsonRoot["libraries"][i]["url"].GetString() : "";
				librariesVector.push_back(library);
			}

		} while (gamePtr = gamePtr->getFatherPtr());//先执行一次，在检查有没有继承的版本

		return librariesVector;
	}

	string GSLauncher::getStyledMinecraftArgumentsString(GSGame & launchGame)
	{
		string minecraftArguments = launchGame.jsonRoot["minecraftArguments"].GetString();

		int location = string::npos;//参数变量的位置
		string assetsIndexName = "";//参数中的一条：--assetIndex ${assets_index_name} 需要特殊获取方法
		GSGame * gamePtr = &launchGame;//指针，用于寻找继承版本

		replaceArgument(minecraftArguments, "username", launchGame.getPlayerName());//用户名

		replaceArgument(minecraftArguments, "version", "\"BluePlum Studio.\"");//这里替换内容可以随便写

		replaceArgument(minecraftArguments, "gameDir", "\"" + launchGame.getGamePath() + "\"");//游戏路径（.minecraft）

		replaceArgument(minecraftArguments, "assetsDir", "\"" + (launchGame.getGamePath()) + "/assets\"");//资源文件夹路径

		while (gamePtr->getFatherPtr())//找到最顶层的继承版本
		{
			gamePtr = gamePtr->getFatherPtr();
		}
		assetsIndexName = gamePtr->jsonRoot["assets"].GetString();//从json中读取
		replaceArgument(minecraftArguments, "assets", assetsIndexName);

		replaceArgument(minecraftArguments, "uuid", genUUID(launchGame.getPlayerName()));//UUID，离线的可以随便写满32位，只要基本不重复

		replaceArgument(minecraftArguments, "accessToken", genUUID(launchGame.getPlayerName()));//UUID，和上面一样

		replaceArgument(minecraftArguments, "userType", launchGame.getUserType());//用户类型（离线Legacy）

		replaceArgument(minecraftArguments, "versionType", "\"BluePlum Studio.\"");//有的版本已经写好，比如Forge版本这里就先写了Forge

		while ((location = minecraftArguments.find('$')) != string::npos)//填充以上识别不到的参数，比如--userType ${user_type}识别不到就填充为--userType {}
		{
			minecraftArguments.replace(minecraftArguments.find('$', location), minecraftArguments.find('}', location) - minecraftArguments.find('$', location) + 1, "{}");
			location = string::npos;
		}

		return minecraftArguments;
	}

	bool GSLauncher::isFileExist(const char * fileName)
	{
		fstream file;

		file.open(fileName, ios::in);
		
		if (file.is_open())
		{
			return true;
		}

		return false;
	}

	vector<string> GSLauncher::getMissingLibrariesStringVector(GSGame & launchGame, bool Semicolon)
	{
		vector<string> missingLibrariesVector;
		vector<string> librariesStringVector = getStyledLibrariesStringVector(launchGame, Semicolon);

		missingLibrariesVector.clear();

		for (unsigned i = 0; i < librariesStringVector.size(); i++)
		{
			string tempLibrariesString = librariesStringVector[i];
			if (Semicolon)
			{
				tempLibrariesString.erase(tempLibrariesString.length() - 1, 1);
			}
			if (!isFileExist(tempLibrariesString.c_str()))
			{
#ifdef _DEBUG
				printf("DEBUG：缺失文件 %d：%s\n", i, tempLibrariesString.c_str());
#endif
				missingLibrariesVector.push_back(tempLibrariesString + (Semicolon ? ";" : ""));
			}
		}
		return missingLibrariesVector;
	}

	bool GSLauncher::replaceArgument(string & minecraftArguments, string argumentName, string replacement)
	{
		int location = string::npos;//各个参数变量的位置
		int begin = string::npos;//替换字符的首位置
		int end = string::npos;//尾位置

		if ((location = minecraftArguments.find(argumentName)) != string::npos)//检查是否有该变量
		{
			if ((begin = minecraftArguments.find(' ', location) + 1) != string::npos)//找到间隔的空格
			{
				if (minecraftArguments[begin] == '$')//有的变量已经被填好了，填好的没有$符号
				{
					if ((end = minecraftArguments.find(' ', begin)) == string::npos)
					{
						end = minecraftArguments.length();
					}
					minecraftArguments.replace(begin, end - begin, replacement);//替换，内容为replacement
					return true;//返回真
				}
			}

		}
		return false;//返回假（替换失败）
	}



	GSLauncher::~GSLauncher()
	{
	}

/*==============================================================================================================*/


}
