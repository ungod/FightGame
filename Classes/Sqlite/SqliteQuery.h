#pragma once
#include "cocos2d.h"
#include "sqlite3.h"


USING_NS_CC;
using namespace std;

//#define SQLITE_INTEGER  1
//#define SQLITE_FLOAT    2
//#define SQLITE_BLOB     4
//#define SQLITE_NULL     5
//#ifdef SQLITE_TEXT
//# undef SQLITE_TEXT
//#else
//# define SQLITE_TEXT     3
//#endif
//#define SQLITE3_TEXT     3


class SqliteQuery : public Object
{

public:
	SqliteQuery();
	static SqliteQuery* create(sqlite3 *pdb, sqlite3_stmt *pStmt, bool bEof);
	static SqliteQuery* create(const SqliteQuery &rQuery);
	SqliteQuery& operator= (const SqliteQuery &rQuery);
	~SqliteQuery();
    
	int fieldNums();
    
	int fieldIndex(const char* szField);
	const char* fieldName(int nField);
    
	int fieldDataType(int nField);
	const char* fieldDeclType(int nField);
    
	const char* fieldValue(int nField);
	const char* fieldValue(const char *szField);
    
	bool fieldIsNull(int nField);
	bool fieldIsNull(const char *szField);
    
	bool getIntValue(int nField, int &rDest);
	bool getIntValue(const char *szField, int &rDest);
    
	bool getFloatValue(int nField, double &rDest);
	bool getFloatValue(const char *szField, double &rDest);
    
	bool getStringValue(int nField, char *&rDest);
	bool getStringValue(const char *szField, char *&rDest);
    
	bool eof();
    
	void nextRow();
    
	void finalize();
    
    
private:
	sqlite3 *m_pDB;
	sqlite3_stmt *m_pStmt;
	bool m_bEof;
	int m_nCols;
    
	bool checkStmt();
};