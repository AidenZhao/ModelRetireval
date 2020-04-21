#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<iostream>
using namespace std;
class SQLOperator
{
public:
	SQLOperator();
	~SQLOperator();
	SQLRETURN SQLinit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password);
	SQLHSTMT SQLsearch(SQLCHAR* sql);
	SQLHSTMT SQLNext();
	SQLHSTMT getHSTMT();
	int getFLAG();

private:
	SQLRETURN ret;
	SQLHENV henv;//SQLHANDLE henv
	SQLHDBC hdbc;//SQLHANDLE hdbc
	SQLHSTMT hstmt;//SQLHANDLE hstmt
	int FLAG=0;
};

