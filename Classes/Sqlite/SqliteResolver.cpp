#include "SqliteResolver.h"
#include "Skills/Actions/SkillMoveBy.h"


// string toolkit
static inline void split(std::string src, const char* token, Array* array)
{
    int nend=0;
    int nbegin=0;

    if(src == "")
        return;
    
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            array->addObject(String::createWithFormat("%s",src.substr(nbegin, src.length()-nbegin).c_str()));
        else
            array->addObject(String::createWithFormat("%s",src.substr(nbegin, nend-nbegin).c_str()));
        nbegin = nend + strlen(token);
    }
}






SqliteResolver::SqliteResolver()
{
	m_table = NULL;
}

SqliteResolver::~SqliteResolver()
{
	CC_SAFE_RELEASE(m_table);
}


SqliteResolver* SqliteResolver::create(const char* szSQL)
{
    SqliteResolver* pRet = new SqliteResolver();
    if(pRet && pRet->init(szSQL))
    {
        pRet->autorelease();
        return pRet;
    }
    
    
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;

}

SqliteResolver* SqliteResolver::create(const char* tableName, int ID)
{
    SqliteResolver* pRet = new SqliteResolver();
    if(pRet && pRet->init(tableName, ID))
    {
        pRet->autorelease();
        return pRet;
    }
    
    
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;

}


SqliteResolver* SqliteResolver::create(SqliteTable* table)
{
    SqliteResolver* pRet = new SqliteResolver();
    if(pRet && pRet->init(table))
    {
        pRet->autorelease();
        return pRet;
    }
    
    
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;

}


bool SqliteResolver::init(const char* szSQL)
{
    bool bRet = false;

    do {
		String* sql = String::createWithFormat("SELECT * FROM %s;",szSQL);
        m_table = SqliteHelper::getInstance()->getTable(sql->getCString());
        CC_BREAK_IF(!m_table);
        m_table->retain();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

bool SqliteResolver::init(SqliteTable* table)
{
    bool bRet = false;
    
    do {
         setTable(table);
        
        bRet = true;
    } while (0);
    
    return bRet;

}


bool SqliteResolver::init(const char* tableName, int ID)
{
    bool bRet = false;
    
    do {
        String* sql = String::createWithFormat("SELECT * FROM %s WHERE ID=%d ;",tableName, ID);
        m_table = SqliteHelper::getInstance()->getTable(sql->getCString());
        //CC_SAFE_RELEASE_NULL(sql);
        
        CC_BREAK_IF(!m_table);
        m_table->retain();
        
        
        
        bRet = true;
    } while (0);
    
    return bRet;

}



bool SqliteResolver::loadSimpleSprite(const char* path, const char* animationName, int pngNum)
{
    bool bRet = true;
    for( int i = 0; i < pngNum; i++)
    {
        string jsonFile = FileUtils::getInstance()->fullPathForFilename(String::createWithFormat("%s/%s.json",path, animationName)->getCString());
        string pngFile = FileUtils::getInstance()->fullPathForFilename(String::createWithFormat("%s/%s%d.png",path, animationName, i)->getCString());
        string plistFile = FileUtils::getInstance()->fullPathForFilename(String::createWithFormat("%s/%s%d.plist",path, animationName, i)->getCString());
        //log("%s %s %s ",pngFile.c_str(), plistFile.c_str(),jsonFile.c_str());
        
        if(!FileUtils::getInstance()->isFileExist(jsonFile)
           || !FileUtils::getInstance()->isFileExist(pngFile)
           || !FileUtils::getInstance()->isFileExist(plistFile))
        {
            return false;
        }
        
        extension::armature::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
                                                                                                     pngFile.c_str(),
                                                                                                     plistFile.c_str(),
                                                                                                     jsonFile.c_str());
    }
    
    
    return bRet;

}


char* SqliteResolver::loadSimpleSprite()
{
    char* pRet = NULL;
    
    do {
        
        CC_BREAK_IF(!m_table);
        
        int id;
        char* nickName;
        char* animation;
        char* path;
        int num;
        
        m_table->getIntField("ID", id);
        m_table->getStringField("NickName", nickName);
        m_table->getStringField("AnimationName", animation);
        m_table->getStringField("DirPath", path);
        m_table->getIntField("PngFileNum", num);
        
        CC_BREAK_IF(!loadSimpleSprite(path, animation, num));
        
        
        pRet = animation;
        
        
    } while (0);
    
    
    
    return  pRet;


}

SimpleAnimation* SqliteResolver::getSimpleSprite()
{
    SimpleAnimation* pRet = NULL;
   
    do {
        
        char* pAnimation = loadSimpleSprite();
        CC_BREAK_IF(!pAnimation);
    
        pRet =  SimpleAnimation::create(pAnimation);
        
        
    } while (0);
    
        
    
    return  pRet;
}


Array* SqliteResolver::getArray(const char* arrayName)
{
    Array* pRet = NULL;
    
    do {  
         CC_BREAK_IF(!m_table);;
        
        char* pStr = NULL;
        CC_BREAK_IF(!m_table->getStringField(arrayName, pStr));//获取字符串
        
        Array* array = Array::create();
        split(pStr, "\n", array);
        
        CC_BREAK_IF(array->count() <= 0);
        
        pRet = array;
        
        
    } while (0);
    return pRet;
}

Array* SqliteResolver::getIntArray(const char* arrayName)
{
    Array* pRet = NULL;
    
    do {
                
        Array* array = getArray(arrayName);
        CC_BREAK_IF(!array);
        
        Object* obj;
        Array* tmpArray = Array::create();
        CCARRAY_FOREACH(array, obj)
        {
            int value = atoi( ((String*)obj)->getCString() );
            Integer* pInt = Integer::create(value);
            tmpArray->addObject(pInt);
        
        }
        
        CC_BREAK_IF(tmpArray->count() <= 0);
        
        pRet = tmpArray;
        
        
    } while (0);
    return pRet;

}



Sequence* SqliteResolver::getPoint3DSequance(const char* actionName, float xScale)
{
    Sequence *pRet = NULL;
    
    do{
        
        Array* array = getArray(actionName);
        CC_BREAK_IF(array == NULL);
        
        
        Array* point3DActionArray = Array::create();
        Object* pointAction = NULL;
        CCARRAY_FOREACH(array, pointAction)
        {
            String* pointString = (String*)pointAction;
            Point3DTime pointTime = Point3DTimeFromString(pointString->getCString());
            
            Point3D point = Point3D(pointTime.point.x * xScale, pointTime.point.y, pointTime.point.z);
            SkillMoveBy* skillMoveBy = SkillMoveBy::create(pointTime.time, point);
            
            point3DActionArray->addObject(skillMoveBy);
            //log("point: time:%f x:%f y:%f z:%f",pointTime.time, point.x,point.y,point.z);
            
        }
        
        pRet = Sequence::create(point3DActionArray);
        
    }while (0);
    
    return pRet;
}


Sequence* SqliteResolver::SequenceWithCallback(Sequence* sequance, CallFunc* callFunc)
{
    Sequence* ret = sequance;
    if(callFunc != NULL)
    {
        ret = Sequence::create(sequance, callFunc, NULL);
        
    }
    
    return ret;
    
}




Point3D SqliteResolver::getPoint3D(const char* pointName, float xScale)
{
    Point3D ret;
    
    do {
        CC_BREAK_IF(!m_table);;
        
        char* pStr = NULL;
        CC_BREAK_IF(!m_table->getStringField(pointName, pStr));//获取字符串
        
        Point3D tmp = Point3DFromString(pStr);
        ret = Point3D(tmp.x * xScale, tmp.y, tmp.z);
        
    } while (0);
    

        
    //log("Point3DTime:x:%f y:%f z:%f",ret.x,ret.y,ret.z);
    return ret;
}


Point SqliteResolver::getPoint(const char* pointName)
{
    Point ret;
    
    do {
        CC_BREAK_IF(!m_table);;
        
        char* pStr = NULL;
        CC_BREAK_IF(!m_table->getStringField(pointName, pStr));//获取字符串
        
        ret = PointFromString(pStr);
        
        
    } while (0);
    
    // log("Point:x:%f y:%f ",ret.x,ret.y);
    return ret;
}


Size SqliteResolver::getSize(const char* sizeName)
{
    Size ret;
    
    do {
        CC_BREAK_IF(!m_table);;
        
        char* pStr = NULL;
        CC_BREAK_IF(!m_table->getStringField(sizeName, pStr));//获取字符串
        
        ret = SizeFromString(pStr);
        
        
    } while (0);
    
        
    //log("Size:x:%f y:%f ",ret.width,ret.height);
    return ret;
    
}


Rect SqliteResolver::getRect(const char* rectName)
{
    Rect ret;
    do {
        CC_BREAK_IF(!m_table);;
        
        char* pStr = NULL;
        CC_BREAK_IF(!m_table->getStringField(rectName, pStr));//获取字符串
        
        ret = RectFromString(pStr);
        
        
    } while (0);
        
    //log("Rect:x:%f y:%f width:%f height:%f",ret.origin.x, ret.origin.y, ret.size.width,ret.size.height);
    return ret;
}

int SqliteResolver::getInt(const char* intName)
{
    int ret = 0;
    do {
        CC_BREAK_IF(!m_table);;
        
        int value;
        CC_BREAK_IF(!m_table->getIntField(intName, value));
        
        ret = value;
        
        
    } while (0);
   
    //log("int:x:%d ",ret);
    return ret;
    
}

float SqliteResolver::getFloat(const char* floatName)
{
    float ret = 0;
    do {
        CC_BREAK_IF(!m_table);;
        
        double value;
        CC_BREAK_IF(!m_table->getFloatField(floatName, value));
        
        ret = (float)value;
        
        
    } while (0);
    
    //log("float:x:%f ",ret);
    return ret;
}

string SqliteResolver::getString(const char* stringName)
{
    string ret = "";
    do {
        CC_BREAK_IF(!m_table);;
        
        char* pStr;
        CC_BREAK_IF(!m_table->getStringField(stringName, pStr));
        
        ret = pStr;
        
    } while (0);

    // log("string:x:%s ",ret.c_str());
    
    return ret;
}

void SqliteResolver::setRow( int row )
{
	do {
		CC_BREAK_IF(!m_table);;
		m_table->setRow(row);

	} while (0);
}

int SqliteResolver::getRow()
{
	int ret = -1;
	do {
		CC_BREAK_IF(!m_table);;
		ret = m_table->numOfRows();

	} while (0);

	return ret;
}








