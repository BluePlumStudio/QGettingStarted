#include <QChar>

#include "ILauncher.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

ILauncher::ILauncher(const QString & version, QGSGameDirectory & gameDirectory) :mVersion(version), mGameDirectory(gameDirectory)
{

}

ILauncher::~ILauncher()
{

}

bool ILauncher::isRulesAllowing(const Rules & rules)
{
	bool ret = true;
	auto & instance = QGSOperatingSystem::getInstance();
	auto && osName = instance.getProductType();
	const auto && osVersion = instance.getProductVersion();
	const auto && listRules = rules.getRules();

	if (osName.contains(OS::MACOS))
	{
		//解决部分json中"osx"显示为"macos"的问题
		osName = "os";
	}

	for (auto & i : listRules)
	{
		auto && version = praseOsVersion(i.getOsVersion());

		if (i.getAction() == Action::ALLOW)
		{
			if (i.getOs().contains(osName))
			{
				if (version.isEmpty())
				{
					ret = true;
					break;
				}
				else if (version == osVersion)
				{
					ret = true;
					break;
				}
			}
			else if (i.getOs().isEmpty())
			{
				ret = true;
			}
		}
		else if (i.getAction() == Action::DISALLOW)
		{
			if (i.getOs().contains(osName))
			{
				if (version.isEmpty())
				{
					ret = false;
					break;
				}
				else if (version == osVersion)
				{
					ret = false;
					break;
				}
			}
			else if (i.getOs().isEmpty())
			{
				ret = false;
			}
		}
	}

	return ret;
}

inline QString ILauncher::praseOsVersion(QString & osVersion)
{
	if (osVersion.isEmpty())
	{
		return osVersion;
	}

	osVersion.remove("^").remove("\\");

	if (!osVersion.isEmpty() && !(osVersion[osVersion.length() - 1].isNumber()))
	{
		osVersion.remove(osVersion.length() - 1, 1);
	}

	return osVersion;
}
