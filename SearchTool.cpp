#include "SearchTool.h"

SearchTool::SearchTool()
{
	
}
SearchTool::~SearchTool()
{

}
void SearchTool::ToolInit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password)
{
	op.SQLinit(database, name, password);
	//cout << "Search Tool OK" << endl;
}
labelItem SearchTool::labelFind(string labelName)
{
	labelItem reitem ;
	SQLHSTMT tempHSTMT;
	string sqlTem;
	SQLCHAR idc[50];
	SQLCHAR idf[50];
	SQLCHAR ids[50];
	SQLCHAR idt[50];
	sqlTem = "SELECT * FROM testModel.dbo.Category WHERE category =  '" +labelName +"'";
	SQLCHAR* sqlCat = (SQLCHAR*)sqlTem.c_str();
	//cout << sqlCat << endl;
	tempHSTMT = op.SQLsearch(sqlCat);
	SQLBindCol(tempHSTMT, 1, SQL_C_CHAR, idc, 50, 0);
	op.SQLNext();
	//cout << op.getFLAG() << endl;
	if (op.getFLAG() != SQL_NO_DATA)
	{
		//cout << "enter cat" << endl;
		strcpy(reitem.id, (const char*)idc);
		reitem.labelCategory = "Category";
		//cout << reitem.id << " " << reitem.labelCategory << endl;
		return reitem;
	}

	sqlTem = "SELECT * FROM dbo.FineGrainedCategory WHERE FineGrainedCategory=  '"+labelName+"'";
	SQLCHAR* sqlFin = (SQLCHAR*)sqlTem.c_str();
	//cout << sqlFin << endl;
	tempHSTMT = op.SQLsearch(sqlFin);
	SQLBindCol(tempHSTMT, 1, SQL_C_CHAR, idf, 50, 0);
	op.SQLNext();
	//cout << op.getFLAG() << endl;
	if (op.getFLAG() != SQL_NO_DATA)
	{
		//cout << "enter fin" << endl;
		strcpy(reitem.id, (const char*)idf);
		reitem.labelCategory = "FineGrainedCategory";
		//cout << reitem.id << " " << reitem.labelCategory << endl;
		return reitem;
	}

	sqlTem = "SELECT * FROM dbo.Style WHERE style =  '" + labelName+"'";
	SQLCHAR* sqlSty = (SQLCHAR*)sqlTem.c_str();
	//cout << sqlSty << endl;
	tempHSTMT = op.SQLsearch(sqlSty);
	SQLBindCol(tempHSTMT, 1, SQL_C_CHAR, ids, 50, 0);
	op.SQLNext();
	//cout << op.getFLAG() << endl;
	if (op.getFLAG() != SQL_NO_DATA)
	{
		//cout << "enter sty" << endl;
		strcpy(reitem.id, (const char*)ids);
		reitem.labelCategory = "Style";
		//cout << reitem.id << " " << reitem.labelCategory << endl;
		return reitem;
	}

	sqlTem = "SELECT * FROM dbo.Texture WHERE texture ='" + labelName+"'";
	SQLCHAR* sqlTex = (SQLCHAR*)sqlTem.c_str();
	//cout << sqlTex << endl;
	tempHSTMT = op.SQLsearch(sqlTex);
	SQLBindCol(tempHSTMT, 1, SQL_C_CHAR, idt, 50, 0);
	op.SQLNext();
	//cout << tempHSTMT << endl;;
	//cout << op.getFLAG() << endl;
	if (op.getFLAG() != SQL_NO_DATA)
	{
		//cout << "enter tex" << endl;
		//cout << idt << endl;
		//strcpy(reitem.id, (const char*)idt);
		//strcpy(reitem.labelCategory, "Texture");
		strcpy(reitem.id , (const char*)idt);
		reitem.labelCategory = "Texture";
		//cout << reitem.id <<reitem.labelCategory << endl;
		return reitem;
	}

	reitem.labelCategory = "0";
	return reitem;
}

vector<labelItem> SearchTool::labelSet(vector<string> labelName)
{
	//cout << "enter labelset ch" << endl;
	vector<labelItem> labelSet;
	for (int i = 0; i < labelName.size(); i++)
	{
		labelItem temp = labelFind(labelName[i]);
		//cout<< temp.id<< "test temp"<<temp.labelCategory<<endl;
		labelSet.push_back(temp);
	}
	return labelSet;
}

modelItem SearchTool::labelWeight(vector<labelItem> labelSet)
{
	modelItem re = {};
	//cout << "label weight" << endl;
	//cout << modelName << endl;
	strcpy(re.name, (const char*)modelName);
	//cout << re.name <<"rename"<< endl;
	re.id_cat = atoi((const char*)id_cat);
	re.id_fin = atoi((const char*)id_fin);
	re.id_sty = atoi((const char*)id_sty);
	re.id_tex = atoi((const char*)id_tex);
	re.weight_cat = atof((const char*)weight_cat);
	re.weight_fin = atof((const char*)weight_fin);
	re.weight_sty = atof((const char*)weight_sty);
	re.weight_tex = atof((const char*)weight_tex);
	op.SQLNext();
	Flag = op.getFLAG();
	return re;
}

SQLHSTMT SearchTool::chmod()
{
	SQLCHAR sql[] = "SELECT * FROM dbo.Model";

	SQLHSTMT temp = op.SQLsearch(sql);
	SQLBindCol(op.getHSTMT(), 1, SQL_C_CHAR, modelName, 50, 0);
	SQLBindCol(op.getHSTMT(), 5, SQL_C_CHAR, id_tex, 50, 0);
	SQLBindCol(op.getHSTMT(), 6, SQL_C_CHAR, id_sty, 50, 0);
	SQLBindCol(op.getHSTMT(), 7, SQL_C_CHAR, id_cat, 50, 0);
	SQLBindCol(op.getHSTMT(), 8, SQL_C_CHAR, id_fin, 50, 0);
	SQLBindCol(op.getHSTMT(), 9, SQL_C_CHAR, weight_tex, 50, 0);
	SQLBindCol(op.getHSTMT(), 10, SQL_C_CHAR, weight_sty, 50, 0);
	SQLBindCol(op.getHSTMT(), 11, SQL_C_CHAR, weight_cat, 50, 0);
	SQLBindCol(op.getHSTMT(), 12, SQL_C_CHAR, weight_fin, 50, 0);
	op.SQLNext();
	return temp;
}

int SearchTool::getFlag()
{
	return Flag;
}