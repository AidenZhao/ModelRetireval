#include "ModelRetireval.h"
ModelRetireval::ModelRetireval()
{
	
}
ModelRetireval::~ModelRetireval()
{

}
void ModelRetireval::RetirevalInit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password)
{
	Tool.ToolInit(database, name, password);
	//cout<< "ModelRe OK"<<endl;
}
vector<score> ModelRetireval::modelSearch(vector<string> labelName,int TopNum)
{
	//cout << "ModelRe enter" << endl;
	vector<labelItem> labelSet;
	vector<score> scoreSet;
	score temp;
	labelSet = Tool.labelSet(labelName);

	SQLHSTMT hstmt;
	//cout << labelSet[0].id << "try labelset result"<<endl;
	hstmt = Tool.chmod();
	//cout << Tool.getFlag() << endl;
	while (Tool.getFlag() != SQL_NO_DATA)
	{
		//cout << "try retireval" << endl;
		temp = scoreCal(labelSet);
		scoreSet.push_back(temp);
	}
	//sort(scoreSet.begin(),scoreSet.end(),GreaterSort);
	return scoreSet;
}
score ModelRetireval::scoreCal(vector<labelItem> labelSet)
{
	//cout << "enter modere" << endl;
	score currentScore = {};
	modelItem currentModel;
	currentModel = Tool.labelWeight(labelSet);
	//cout << currentModel.id_cat << "if ok cMo"<<endl;
	strcpy(currentScore.modelName,(const char*)currentModel.name);
	currentScore.score = 0;
	for (int i = 0; i < labelSet.size(); i++)
	{
		if (strcmp(labelSet[i].labelCategory, "Category")==0 && atoi(labelSet[i].id) == currentModel.id_cat)
		{
			//cout << labelSet[i].labelCategory << "cat"<<endl;
			currentScore.score += currentModel.weight_cat;
			currentScore.score += 100000;
		}
		else if (strcmp(labelSet[i].labelCategory, "FineGrainedCategory")==0 && atoi(labelSet[i].id) == currentModel.id_fin)
		{
			currentScore.score += currentModel.weight_fin;
		}
		else if (strcmp(labelSet[i].labelCategory, "Style")==0 && atoi(labelSet[i].id) == currentModel.id_sty)
		{
			currentScore.score += currentModel.weight_sty;
		}
		else if (strcmp(labelSet[i].labelCategory, "Texture")==0 && atoi(labelSet[i].id) == currentModel.id_tex)
		{
			currentScore.score += currentModel.weight_tex;
		}
	}

	return currentScore;
}
/*
bool ModelRetireval::GreaterSort(score A, score B)
{
	return (A.score < B.score);
}*/