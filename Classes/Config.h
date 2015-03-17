#pragma once

#include "cocos2d.h"

#define CONFIG_FILE_PATH "config.plist"

USING_NS_CC;

class Config
{
public:
	static void initConfig()
	{
		m_ConfigDict = Dictionary::createWithContentsOfFile(CONFIG_FILE_PATH);

		if (m_ConfigDict)
		{
			DBRemote = m_ConfigDict->valueForKey("DBRemote")->intValue() == 1;
			PhyDebug = m_ConfigDict->valueForKey("PhyDebug")->intValue() == 1;
		}
	}

public:
	static bool DBRemote;//数据库是否远程
	static bool PhyDebug;//是否打开物理调试

private:
	static Dictionary* m_ConfigDict;
};