#pragma once
#include "cocos2d.h"
#include "sqlite3.h"


USING_NS_CC;
using namespace std;

class SqliteTable : public Object
{

public:
	SqliteTable();
	static SqliteTable* create(const SqliteTable &rTable);
	static SqliteTable* create(char **paszResults, int nRows, int nCols);
	~SqliteTable();
    
	SqliteTable& operator= (const SqliteTable &rTable);
    
	int numOfFields();
	int numOfRows();
    
	const char* nameOfField(int nField);
    
	const char* valueOfField(int nField);
	const char* valueOfField(const char *szField);
    
	bool fieldIsNull(int nField);
	bool fieldIsNull(const char *szField);
    
	bool getIntField(int nField, int &rDest);
	bool getIntField(const char *szField, int &rDest);
    
	bool getFloatField(int nField, double &rDest);
	bool getFloatField(const char *szField, double &rDest);
    
	bool getStringField(int nField, char *&rDest);
	bool getStringField(const char *szField, char *&rDset);
    
	void setRow(int nRow);
    
	void finalize();
    
    
    
private:
	int m_nCurrentRow;
	int m_nRows;
	int m_nCols;
	char **m_paszResults;
    
};
