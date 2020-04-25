# ModelRetireval
模型检索模块。
cpp + ODBC +SQLServer

#### 简介
* SQLOperator
使用ODBC。封装了数据库底层的基本操作，包括数据库连接、SQL语句的执行等。

* SearchTool
封装了检索本模型库需要的操作。
包括权重的查询，标签到索引的转换等。

* ModelRetireval
检索的交互模块。
包括权重的计算，按照权重将检索结果排序等。


#### API
* ModelRetireval
    -  ```void RetirevalInit(SQLCHAR* database, SQLCHAR* name, SQLCHAR* password);```
    初始化方法。
    database：数据库名。
    name：用户名。
    password：密码。
    - ```vector<score> modelSearch(vector<string> labelName,int TopNum);```
    检索方法。
    labelName：检索特征集合。
    TopNum：保留结果数目。


#### 使用方法 & 示例程序
只需要调用 **ModelRetireval.h**。
```cpp
#include<iostream>
#include "ModelRetireval.h"
#include <vector>
using std::vector;
using namespace std;
bool GreaterSort(score a, score b)
{
	return (a.score > b.score);
}
int main()
{
	ModelRetireval re;
	vector<score> res;
	re.RetirevalInit((SQLCHAR*)"***", (SQLCHAR*)"**", (SQLCHAR*)"****");
	vector<string> label= { "cloth","Japanese","Bed"};
	res = re.modelSearch(label, 5);

	std::sort(res.begin(), res.end(), GreaterSort);
	cout << res[0].modelName << "   " <<  endl;
	cout << res[1].modelName << "   " <<  endl;
	cout << res[2].modelName << "   " <<  endl;
	cout << res[3].modelName << "   " <<  endl;
	cout << res[4].modelName << "   " <<  endl;

}
```

#### ODBC配置
可以参考以下博文：
https://blog.csdn.net/huyuyang6688/article/details/9036745
