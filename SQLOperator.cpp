#include "SQLOperator.h"

SQLOperator::SQLOperator()
{

}

SQLOperator::~SQLOperator()
{
	SQLDisconnect(hdbc);//�Ͽ������ݿ������
}

SQLRETURN SQLOperator::SQLinit(SQLCHAR* database, SQLCHAR* name , SQLCHAR* password)
{
	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//���뻷�����
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//���û�������
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//�������ݿ����Ӿ��
	ret = SQLConnect(hdbc, database, SQL_NTS, name, SQL_NTS, password, SQL_NTS);//�������ݿ�
	//ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) printf("�������ݿ�ɹ�!\n");
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