#include "SqliteHelper.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#define DATABASE_NAME Config::DBRemote ? "\\\\172.16.228.4\\share\\Mobile\\Database\\game.zip" : "game.zip"
#else
#define DATABASE_NAME "game.zip"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

static SqliteHelper* s_sqliteHelper = NULL;

SqliteHelper* SqliteHelper::getInstance()
{
    if(s_sqliteHelper == NULL)
    {
       s_sqliteHelper = new SqliteHelper();
       if(s_sqliteHelper->init())
        {
            return s_sqliteHelper;
        }
        
       else
       {
         CC_SAFE_RELEASE_NULL(s_sqliteHelper);
       }

    }
    
    
    return s_sqliteHelper;
}

SqliteHelper::SqliteHelper()
{
    m_pdb = NULL;

}
SqliteHelper::~SqliteHelper()
{
   sqlite3_close(m_pdb);
}


bool SqliteHelper::init()
{
    
    bool bRet = false;
    
	do {
		int result;
		string newPath = DATABASE_NAME;
        
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        
        
		unsigned long fileSize = 0;
		unsigned char* data =FileUtils::getInstance()->getFileData(DATABASE_NAME, "r", &fileSize);
        newPath = FileUtils::getInstance()->getWritablePath() + DATABASE_NAME;
        
		CC_BREAK_IF(!data);
        
		//if(!FileUtils::getInstance()->isFileExist(newPath))//文件不存在,拷贝过去
		{
			FILE* newFile = fopen(newPath.c_str(), "w+");
			CC_BREAK_IF(newFile == NULL);
			fwrite(data, fileSize, 1, newFile);
            
			CC_SAFE_DELETE(data);
			fflush(newFile);
			fclose(newFile);
		}
        
#endif
        result=sqlite3_open(newPath.c_str(),&m_pdb);
        log("sqlite open %s",newPath.c_str());
        CC_BREAK_IF(result != SQLITE_OK);
        
        
/*        char * pErrMsg = 0;
        int ret = 0;
        
        //添加、使用密码
        string key = "xueyu1234";
        ret = sqlite3_key(m_pdb, key.c_str(), key.length() );
        
        
        char sSQL[] = "create table class(name varchar(20), student);";
        sqlite3_exec( m_pdb, sSQL, NULL, 0, &pErrMsg );
        
        //插入数据
        char sSQL1[] = "insert into class values('mem_52911', 'zhaoyun');";
        ret = sqlite3_exec( m_pdb, sSQL1, NULL, 0, &pErrMsg );
        if(ret != SQLITE_OK)
        {
            log("sqlite error");
        }
        //修改密码
        
       // i = sqlite3_rekey(m_pdb, "dcg", 0 );*/
        
        bRet = true;
    } while (0);
    
    
    
    return bRet;
}


bool SqliteHelper::checkDB()
{
  if(m_pdb == NULL)
      return false;
    
    return true;
}


sqlite3_stmt* SqliteHelper::compile(const char *szSQL)
{
    if(!checkDB())
        return NULL;
    
    const char *szTail = 0;
    sqlite3_stmt *pStmt;
    
    int nRet = sqlite3_prepare(m_pdb, szSQL, -1, &pStmt, &szTail);
    
    if (nRet != SQLITE_OK)
    {
        const char *szError = sqlite3_errmsg(m_pdb);
        log("sqlite Error:%s",szError);
        return NULL;
    }
    
    return pStmt;
}


int SqliteHelper::execDML(const char *szSQL)
{
    if(!checkDB())
        return -1;
    
    char* szError=0;
    
    int nRet = sqlite3_exec(m_pdb, szSQL, 0, 0, &szError);
    
    if (nRet == SQLITE_OK)
    {
        return sqlite3_changes(m_pdb);  //返回这个执行影响的行数
    }
   
    return -1;
}


SqliteQuery* SqliteHelper::execQuery(const char *szSQL)
{
    if(!checkDB())
        return NULL;
    
    
    //编译一条指针对象，用临时变量存储，传递给SQLiteQuery后，
    //这个临时sqlite3_stmt*对象会自动消失，最后只有一份保留在CppSQLite3Query中
    sqlite3_stmt *pStmt = compile(szSQL);
    
    int nRet = sqlite3_step(pStmt);
    
    if (nRet == SQLITE_DONE) //表明这个查询没有返回结果
    {
        return SqliteQuery::create(m_pdb, pStmt, true); //所以将第三个字段设置为true，表明到达查询结果末尾处
    }
    else if (nRet == SQLITE_ROW) //这个查询中至少有一行记录
    {
        return SqliteQuery::create(m_pdb, pStmt, false); //false表明没有到达查询结果末尾
    }
    else
    {
        nRet = sqlite3_finalize(pStmt);
        const char *szError = sqlite3_errmsg(m_pdb);
        log("sqlite Error:%s",szError);
    }

    
    return NULL;

}



SqliteTable* SqliteHelper::getTable(const char *szSQL)
{
    if(!checkDB())
        return NULL;
    
    char* szError=0;
    char** paszResults=0;
    int nRet;
    int nRows(0);
    int nCols(0);
    
    nRet = sqlite3_get_table(m_pdb, szSQL, &paszResults, &nRows, &nCols, &szError);
    
    if (nRet == SQLITE_OK)
    {
        if(nCols <= 0 || nCols <= 0)
            return NULL;//没有记录

        return SqliteTable::create(paszResults, nRows, nCols);
    }
    else
    {
        log("sqlite Error:%s",szError);
    }
    
    return NULL;
}


void SqliteHelper::test()
{    
  /* SqliteTable* table = getTable("select * from Animations ;");
    int id;
    char* nickName;
    char* animation;
    char* path;
    int num;
    
    for (int row = 0; row < table->numOfRows(); row++)
    {
        table->setRow(row);  //每次获取数据前要显式的指定行值
        table->getIntField("ID", id);
        table->getStringField("NickName", nickName); 
        table->getStringField("AnimationName", animation);
        table->getStringField("DirPath", path);
        table->getIntField("PngFileNum", num);
        log("%d %s %s %s %d",id, nickName, animation,path, num);
    }*/
    
    
/*    SqliteQuery* query = execQuery("select * from Animations ;");
    while (!query->eof())
    {
        query->getIntValue("ID", id);
        query->getStringValue("NickName", nickName);
        query->getStringValue("AnimationName", animation);
        query->getStringValue("DirPath", path);
        query->getIntValue("PngFileNum", num);
        log("%d %s %s %s %d",id, nickName, animation,path, num);
        
        query->nextRow();
    }*/ 
}
















