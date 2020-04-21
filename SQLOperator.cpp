#include "SQLOperator.h"

SQLOperator::SQLOperator()
{

}

SQLOperator::~SQLOperator()
{
	SQLDisconnect(hdbc);//断开与数据库的连接
}

SQLRETURN SQLOperator::SQLinit(SQLCHAR* database, SQLCHAR* name , SQLCHAR* password)
{
	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境句柄
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境属性
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接句柄
	ret = SQLConnect(hdbc, database, SQL_NTS, name, SQL_NTS, password, SQL_NTS);//连接数据库
	//ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) printf("连接数据库成功!\n");
	//cout << "SQLOP OK" << endl;
	return ret;
}

SQLHSTMT SQLOperator::SQLsearch(SQLCHAR* sql)
{
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, sql, SQL_NTS);
	//cout << "ret: " << ret << endl;
	FLAG = ret;
	//cout << hstmt << endl;
	return hstmt;
}

SQLHSTMT SQLOperator::SQLNext()
{
	ret = SQLFetch(hstmt);
	FLAG = ret;
	return hstmt;
}
int SQLOperator::getFLAG()
{
	return FLAG;
}
SQLHSTMT SQLOperator::getHSTMT()
{
	return hstmt;
}