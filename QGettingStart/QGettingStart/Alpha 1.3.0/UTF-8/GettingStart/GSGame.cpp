#include "GSGame.h"

using namespace std;

namespace gs
{
	string readFile(const char * fileName, string & str)
	{
		fstream file;
		string temp = "";

		str = "";

		file.open(fileName, ios::in);
		if (!file.is_open())
		{
#ifdef _DEBUG
			printf("DEBUG：文件：%s 打开失败\n", fileName);
#endif
			//exit(1);
			return "";
		}
		while (getline(file, temp))
		{
			//cout << temp << endl;
			str.append(temp);
			str.append("\n");
		}

		return str;
	}

	/*========================================================*/

	GSLibrary::GSLibrary()
	{
	}

	GSLibrary::~GSLibrary()
	{
	}

	/*========================================================*/

	GSGame::GSGame()
	{
		inited = false;
		father = nullptr;
		jsonFilePath = "";
		version = "";
		path = "";
		javaPath = "";
		nativePath = "";
		playerName = "";
		userType = "";//用户类型
		extraArgument = "";//额外参数
		Xmn = 0;
		Xmx = 0;

#ifdef _DEBUG
		cout << "DEBUG：创建新GSGame" << endl;
#endif
	}

	GSGame::GSGame(const GSGame & right)
	{
		string json = "";

		father = new GSGame;//深拷贝
		if (!father)
		{
			throw FAILED_OPERATION;
		}
		inited = true;//初始化
		if (readFile(right.getJsonFilePath().c_str(), json).empty())
		{
			throw FAILED_OPERATION;
		}
		jsonRoot.Parse(json.c_str());
		if (jsonRoot.HasParseError())
		{
			throw FAILED_OPERATION;
		}
		if (father->init(right.getFatherPtr()->getVersion(), right.getFatherPtr()->getGamePath()))
		{
			throw FAILED_OPERATION;
		}

		jsonFilePath = right.getJsonFilePath();
		path = right.getGamePath();
		javaPath = right.getJavaPath();
		version = right.getVersion();
		nativePath = right.getNativePath();
		playerName = right.getPlayerName();
		userType = right.getUserType();
		extraArgument = right.getExtraArgument();
		Xmn = right.getXmn();
		Xmx = right.getXmx();

#ifdef _DEBUG
		cout << "DEBUG：创建新GSGame（拷贝构造函数）" << endl;
#endif

	}

	Status GSGame::init(string gameVersion, string gamePath)
	{
		if (inited)
		{
			return NO_ERROR;//若初始化过，则返回无错误。
		}
		string json;//json文件字符串内容

		nativePath = "";
		father = nullptr;
		jsonFilePath = "";
		path = gamePath;
		version = gameVersion;
		javaPath = "";
		nativePath = "";
		playerName = "";
		userType = "";
		extraArgument = "";
		Xmn = 0;
		Xmx = 0;

		inited = true;//已初始化

		//剔除像下面那样多余的/符号
		//.minecrat//////
		while (path[path.length() - 1] == '/' || path[path.length() - 1] == '\\')
		{
			path.erase(path.length() - 1);
		}

		//拼合成完整的json文件路径
		jsonFilePath = path + "/versions/" + version + "/" + version + ".json";
#ifdef _DEBUG
		printf("DEBUG：jsonFilePath=%s\n", jsonFilePath.c_str());
#endif

		//读取文件到json字符串，下面要解析
		readFile(jsonFilePath.c_str(), json);
		if (json.empty())
		{
			return FAILED_OPERATION;
		}

		//解析Json文件
		jsonRoot.Parse(json.c_str());
		if (jsonRoot.HasParseError())//检查是否解析错误
		{
#ifdef _DEBUG
			printf("DEBUG：Json文件：%s 解析失败\n", jsonFilePath);
#endif
			return FAILED_OPERATION;//返回失败的操作
		}

		//继承的版本
		/*json文件有个inheritsFrom项，要依赖继承的版本的libraries等项*/
		string inheritsFrom = "";
		inheritsFrom = jsonRoot.HasMember("inheritsFrom") ? jsonRoot["inheritsFrom"].GetString() : "";//是否有继承
		if (!inheritsFrom.empty())
		{
			father = new GSGame;

			return father->init(inheritsFrom, gamePath);//继承版本初始化

			father->path = path;
			father->javaPath = javaPath;
			father->playerName = playerName;
			father->Xmn = Xmn;
			father->Xmx = Xmx;
		}

#ifdef _DEBUG
		cout << "DEBUG：GSGame初始化，" << "版本：" << gameVersion << endl;
#endif
		return NO_ERROR;//返回无错误
	}

	bool GSGame::isInit()const
	{
		return inited;//是否被初始化
	}

	GSGame * GSGame::getFatherPtr()const
	{
		return father;//继承的版本对象的指针
	}

	string GSGame::getJsonFilePath()const
	{
		return jsonFilePath;//当前版本的json文件的路径
	}

	string GSGame::getGamePath()const
	{
		return path;//游戏路径（.minecraft）
	}

	string GSGame::getJavaPath()const
	{
		return javaPath;//Java路径（javaw.exe）
	}

	string GSGame::getVersion()const
	{
		return version;//当前游戏版本
	}

	string GSGame::getNativePath()const
	{
		return nativePath;//native文件夹路径
	}

	string GSGame::getPlayerName()const
	{
		return playerName;
	}

	string GSGame::getUserType()const
	{
		return userType;
	}

	string GSGame::getExtraArgument()const
	{
		return extraArgument;
	}

	int GSGame::getXmn()const
	{
		return Xmn;
	}

	int GSGame::getXmx()const
	{
		return Xmx;
	}

	/*=====================================================================================*/

	void GSGame::setJavaPath(string javaPath)
	{
		int location = string::npos;

		location = javaPath.length() - 1;
		while (location == -1 || javaPath[location] == '/' || javaPath[location] == '\\')
		{
			location--;
		}
		javaPath.erase(location + 1, javaPath.length() - location);

		this->javaPath = javaPath;
	}

	void GSGame::setNativePath(std::string nativePath)
	{
		int location = string::npos;

		location = nativePath.length() - 1;
		while (location == -1 || nativePath[location] == '/' || nativePath[location] == '\\')
		{
			location--;
		}
		nativePath.erase(location + 1, nativePath.length() - location);

		this->nativePath = nativePath;
	}

	void GSGame::setPlayerName(string playerName)
	{
		this->playerName = playerName;
	}

	void GSGame::setUserType(string userType)
	{
		this->userType = userType;
	}

	void GSGame::setExtraArgument(std::string extraArgument)
	{
		this->extraArgument = extraArgument;
	}

	void GSGame::setXmn(int Xmn)
	{
		this->Xmn = Xmn;
	}

	void GSGame::setXmx(int Xmx)
	{
		this->Xmx = Xmx;
	}

	GSGame & GSGame::operator = (GSGame & right)
	{
		if (inited = right.inited)//判断是否初始化，没初始化就这里初始化。
		{
			string json = "";
			father = new GSGame;//深拷贝
			if (!father)
			{
				throw FAILED_OPERATION;
			}
			inited = true;//初始化
			if (readFile(right.getJsonFilePath().c_str(), json).empty())
			{
				throw FAILED_OPERATION;
			}
			jsonRoot.Parse(json.c_str());
			if (jsonRoot.HasParseError())
			{
				throw FAILED_OPERATION;
			}
			if (father->init(right.getFatherPtr()->getVersion(), right.getFatherPtr()->getGamePath()))
			{
				throw FAILED_OPERATION;
			}
			//将继承版本初始化。

			/*
			=
			如果左边的GSGame没有初始化，声明后用=，就要把右边的GSGame深拷贝进来，同时初始化继承的版本。
			*/
		}

		jsonFilePath = right.getJsonFilePath();
		path = right.getGamePath();
		javaPath = right.getJavaPath();
		version = right.getVersion();
		nativePath = right.getNativePath();
		playerName = right.getPlayerName();
		userType = right.getUserType();
		extraArgument = right.getExtraArgument();
		Xmn = right.getXmn();
		Xmx = right.getXmx();
		return *this;
	}

	GSGame::~GSGame()
	{
		//cout << "析构" << endl;
		if (father)
		{
			delete father;
			father = nullptr;
		}

	}
}

