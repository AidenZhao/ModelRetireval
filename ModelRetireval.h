#pragma once
#include "SearchTool.h"
#include <algorithm>
struct score
{
	char modelName[50];
	float score;
};
class ModelRetireval
{
public:
	ModelRetireval();
	~ModelRetireval();
	vector<score> modelSearch(vector<string> labelName,int TopNum);
	//static bool GreaterSort(score A, score B);
	score scoreCal(vector<labelItem>);
	void RetirevalInit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password);
private:
	SearchTool Tool;
};

