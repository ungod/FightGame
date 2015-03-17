#include "SqliteQuery.h"


SqliteQuery::SqliteQuery()
{
	m_pDB = 0;
	m_pStmt = 0;
	m_nCols = 0;
	m_bEof = true;
}

SqliteQuery* SqliteQuery::create(sqlite3 *pdb, sqlite3_stmt *pStmt, bool bEof)
{
    SqliteQuery* pRet = new SqliteQuery();
    
	pRet->m_pDB = pdb;
	pRet->m_pStmt = pStmt;
	pRet->m_bEof = bEof;
	pRet->m_nCols = sqlite3_column_count(pStmt);
    pRet->autorelease();
    
    return pRet;
}

SqliteQuery*SqliteQuery::create(const SqliteQuery &rQuery)
{
    SqliteQuery* pRet = new SqliteQuery();
    
	pRet->m_pStmt = rQuery.m_pStmt;
	const_cast<SqliteQuery &>(rQuery).m_pStmt = 0;
	pRet->m_nCols = rQuery.m_nCols;
	pRet->m_bEof = rQuery.m_bEof;
    pRet->autorelease();
    
    return pRet;
}



SqliteQuery& SqliteQuery::operator =(const SqliteQuery &rQuery)
{
	m_pStmt = rQuery.m_pStmt;
	const_cast<SqliteQuery &>(rQuery).m_pStmt = 0;
	m_nCols = rQuery.m_nCols;
	m_bEof = rQuery.m_bEof;
    
	return *this;
}

SqliteQuery::~SqliteQuery()
{
	finalize();
}

bool SqliteQuery::checkStmt()
{
	if (m_pStmt == 0)
	{
		return false;
	}
    
    return true;
}

int SqliteQuery::fieldNums()
{
	if(!checkStmt())
        return -1;
    
	return m_nCols;
}

//根据字段名返回列索引
int SqliteQuery::fieldIndex(const char* szField)
{
	if(!checkStmt())
        return -1;
    
	if (szField)
	{
		for (int nField = 0; nField < m_nCols; nField++)
		{
			//后面还有很多类似的函数，参数差不多，需要一个sqlite3_stmt*和列索引值，这应该是内部查询了之后返回的结果，而不是事先保存的
			const char *szTemp = sqlite3_column_name(m_pStmt, nField);
			if (strcmp(szTemp, szField) == 0)
			{
				return nField;
			}
		}
	}
    
	return -1;
}
const char* SqliteQuery::fieldName(int nField)
{
	if(!checkStmt())
        return NULL;
    
	if (nField < 0 || nField > m_nCols-1)
	{
		return NULL;
	}
    
	return sqlite3_column_name(m_pStmt, nField);
}

int SqliteQuery::fieldDataType(int nField)
{
	if(!checkStmt())
        return -1;
    
	if (nField < 0 || nField > m_nCols-1)
	{
		return -1;
	}
    
	return sqlite3_column_type(m_pStmt, nField);
}
const char* SqliteQuery::fieldDeclType(int nField)
{
	if(!checkStmt())
        return NULL;
    
	if (nField < 0 || nField > m_nCols-1)
	{
		return NULL;
	}
    
	return sqlite3_column_decltype(m_pStmt, nField);
}

const char* SqliteQuery::fieldValue(int nField)
{
	if(!checkStmt())
        return NULL;
    
	if (nField < 0 || nField > m_nCols-1)
	{
		return NULL;
	}
    
	return (const char*)sqlite3_column_text(m_pStmt, nField);
    
}

const char* SqliteQuery::fieldValue(const char *szField)
{
	int nField = fieldIndex(szField);
	return fieldValue(nField);
}

bool SqliteQuery::fieldIsNull(int nField)
{
	return (fieldDataType(nField) == SQLITE_NULL);
}

bool SqliteQuery::fieldIsNull(const char *szField)
{
	int nField = fieldIndex(szField);
	return (fieldDataType(nField) == SQLITE_NULL);
}

bool SqliteQuery::getIntValue(int nField, int &rDest)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = sqlite3_column_int(m_pStmt, nField);
		return true;
	}
}

bool SqliteQuery::getIntValue(const char *szField, int &rDest)
{
	int nField = fieldIndex(szField);
	return getIntValue(nField, rDest);
}

bool SqliteQuery::getFloatValue(int nField, double &rDest)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = sqlite3_column_double(m_pStmt, nField);
		return true;
	}
}
bool SqliteQuery::getFloatValue(const char *szField, double &rDest)
{
	int nField = fieldIndex(szField);
	return getFloatValue(nField, rDest);
}

bool SqliteQuery::getStringValue(int nField, char *&rDest)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = const_cast<char *>((const char*)sqlite3_column_text(m_pStmt, nField));
		return true;
	}
}
bool SqliteQuery::getStringValue(const char *szField, char *&rDest)
{
	int nField = fieldIndex(szField);
	return getStringValue(nField, rDest);
}

bool SqliteQuery::eof()
{
	checkStmt();
    
	return m_bEof;
}

void SqliteQuery::nextRow()
{
	checkStmt();
    
	int nRet = sqlite3_step(m_pStmt);
    
	if (nRet == SQLITE_DONE)
	{
		// no rows
		m_bEof = true;
	}
	else if (nRet == SQLITE_ROW)
	{
		// more rows, nothing to do
	}
	else
	{
		nRet = sqlite3_finalize(m_pStmt);
		m_pStmt = 0;
		const char* szError = sqlite3_errmsg(m_pDB);
        log("sqlite Error:%s",szError);
	}
}

void SqliteQuery::finalize()
{
	if (m_pStmt)
	{
		int nRet = sqlite3_finalize(m_pStmt);
		m_pStmt = 0;
		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(m_pDB);
            log("sqlite Error:%s",szError);

        }
	}
}

 








