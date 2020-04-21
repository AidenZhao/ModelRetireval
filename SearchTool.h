#pragma once
#include "SQLOperator.h"
#include <vector>
#include <string>
using namespace std;

struct labelItem
{
	char id[50];
	char* labelCategory;
};
struct modelItem
{
	char name[50];
	int id_tex, id_sty, id_cat, id_fin;
	float weight_tex, weight_sty, weight_cat, weight_fin;
};

class SearchTool
{
public:
	SearchTool();
	~SearchTool();
	labelItem labelFind(string labelName);
	vector<labelItem> labelSet(vector<string> labelName);
	SQLHSTMT chmod();
	modelItem labelWeight(vector<labelItem> labelSet);
	void ToolInit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password);
	int getFlag();
private:
	SQLOperator op;
	SQLCHAR id_tex[50], id_sty[50], id_cat[50], id_fin[50];
	SQLCHAR weight_tex[50], weight_sty[50], weight_cat[50], weight_fin[50];
	SQLCHAR modelName[50];
	int Flag = 0;
};

