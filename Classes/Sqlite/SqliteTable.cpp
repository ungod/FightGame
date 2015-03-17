#include "SqliteTable.h"


SqliteTable::SqliteTable()
{
	m_nCols = 0;
	m_nRows = 0;
	m_nCurrentRow = 0;
	m_paszResults = 0;
}

SqliteTable* SqliteTable::create(const SqliteTable &rTable)
{
    SqliteTable*  pRet = new SqliteTable();
    
	pRet->m_nCols = rTable.m_nCols;
	pRet->m_nRows = rTable.m_nRows;
	pRet->m_nCurrentRow = rTable.m_nCurrentRow;
	pRet->m_paszResults = rTable.m_paszResults;
	const_cast<SqliteTable&>(rTable).m_paszResults = 0; //当表复制时，销毁原来的表，防止丢失修改
    
    return pRet;
}

SqliteTable* SqliteTable::create(char **paszResults, int nRows, int nCols)
{
    SqliteTable*  pRet = new SqliteTable();
    
	pRet->m_paszResults = paszResults; //给出一个一维指针数组，初始化一个表
	pRet->m_nCols = nCols;
	pRet->m_nRows = nRows;
	pRet->m_nCurrentRow = 0;
    
    return pRet;
}

SqliteTable::~SqliteTable()
{
	finalize();
}

SqliteTable& SqliteTable::operator= (const SqliteTable &rTable)
{
	finalize();
    
	m_paszResults = rTable.m_paszResults;
	const_cast<SqliteTable &>(rTable).m_paszResults = 0;
	m_nCols = rTable.m_nCols;
	m_nRows = rTable.m_nRows;
	m_nCurrentRow = rTable.m_nCurrentRow;
    
	return *this;
}

void SqliteTable::finalize()
{
	if (m_paszResults)
	{
		sqlite3_free_table(m_paszResults);  //利用库函数销毁表存储内容
		m_paszResults = 0;
	}

}

int SqliteTable::numOfFields()
{
	return m_nCols;
}

int SqliteTable::numOfRows()
{
	return m_nRows;
}

const char* SqliteTable::nameOfField(int nField)
{
	if (nField < 0 || nField > m_nCols-1)
	{
		return NULL;
	}
    
	return m_paszResults[nField]; //一位数组的头m_nCols个元素存放的是表的字段名称，存储具体位置是m_paszResults[0,,,m_nCols-1]。
}

const char* SqliteTable::valueOfField(int nField)
{
	if (nField < 0 || nField > m_nCols-1)
	{
		return NULL;
	}
    
	//根据要查询的当前行与列值算出在一位数组中的索引下标，额外加一个m_nCols是第一行存储的是字段名
	int nIndex = m_nCurrentRow*m_nCols + m_nCols + nField;
	return m_paszResults[nIndex];
}

//根据字段名称来访问某一列的数据
const char* SqliteTable::valueOfField(const char *szField)
{
	if (szField)
	{
		for (int nField = 0; nField < m_nCols; nField++)
		{
			if (strcmp(szField, m_paszResults[nField]) == 0)
			{
				int nIndex = m_nCurrentRow*m_nCols + m_nCols + nField;
				return m_paszResults[nIndex];
			}
		}
	}
    
	return NULL;
}

bool SqliteTable::fieldIsNull(int nField)
{
	return (valueOfField(nField) == 0);
}

bool SqliteTable::fieldIsNull(const char* szField)
{
	return (valueOfField(szField) == 0);
}

//这里的获取具体类型数值函数，需要用户对数据库中的表有一定的了解，知道哪些字段存储的是什么内容
//并且使用的是外部传递引用的形式
bool SqliteTable::getIntField(int nField, int &rDest)
{
	if (fieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//atoi()函数是C库函数，讲数值型字符串转换为整型值
		rDest = atoi(valueOfField(nField));
		return true;
	}
}

bool SqliteTable::getIntField(const char *szField, int &rDest)
{
	if (fieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atoi(valueOfField(szField));
		return true;
	}
}

bool SqliteTable::getFloatField(int nField, double &rDest)
{
	if (fieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//C库函数，将数值型字符串转换为浮点数
		rDest = atof(valueOfField(nField));
		return true;
	}
}

bool SqliteTable::getFloatField(const char *szField, double &rDest)
{
	if (fieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atof(valueOfField(szField));
		return true;
	}
}

bool SqliteTable::getStringField(int nField, char *&rDest)
{
	if (fieldIsNull(nField))
	{
		return false;
	}
	else
	{
		rDest = const_cast<char *>(valueOfField(nField));
		return true;
	}
}
bool SqliteTable::getStringField(const char *szField, char *&rDset)
{
	if (fieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDset = const_cast<char *>(valueOfField(szField));
		return true;
	}
}

//在每一次需要获取数据的时候都要设置要访问的行值
void SqliteTable::setRow(int nRow)
{
	if (nRow < 0 || nRow > m_nRows-1)
	{
		return ;
	}
    
	m_nCurrentRow = nRow;
}
















