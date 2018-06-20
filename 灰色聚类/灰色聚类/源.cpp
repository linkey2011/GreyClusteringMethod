#include<iostream>
#include<stdio.h> 
#include<string.h>
#include<cmath>//abs(b-a)
#pragma warning(disable:4996)//忽略警告4996
using namespace  std;
double a[20][20];//初始数据矩阵
double difference[20][20];//差异信息矩阵
double relate[20][20];//灰关联系数矩阵
double relation[20][20];//灰聚类矩阵 
double Diff[20][20];//简化版初始数据矩阵

int whether[20];
int Class[20][20];
//输入初始属性
int getShuJu() {
	int i, j;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			cin >> a[i][j];
		}
	}

	return 0;
}
// 输出 int
int myCOUT(int ppp[20][20]) {
	int i, j;
	for (i = 0; i <= 15; i++)
	{

		printf("第%02d行 ", i);
		//cout << "第" << i << "行";
		for (j = 0; j <= 9; j++)
		{
			if (i == 0 && j != 0) cout << "第" << j << "列 ";
			else if (j != 0) {
				//printf("%02d ", a[i][j]);//输出初始属性
				printf("%05d ", ppp[i][j]);
			}
		}
		cout << endl;
	}
	return 0;

}

// 输出 double
int myCOUT(double ppp[20][20], int hang_end, int lie_end) {
	int i, j;
	for (i = 0; i <= hang_end; i++)
	{

		printf("第%02d行 ", i);
		//cout << "第" << i << "行";
		for (j = 0; j <= lie_end; j++)
		{
			if (i == 0 && j != 0) printf("第%02d列    ", j); //cout << "第" << j << "列    ";
			else if (j != 0) {
				//printf("%02d ", a[i][j]);//输出初始属性
				printf("%07.4f   ", ppp[i][j]);
			}
		}
		cout << endl;
	}
	return 0;

}

//填写差异矩阵
int getMyDiff(int hang_start, int hang_end, int target_hang, double p[20][20]) {
	int m, n;
	for (m = hang_start; m <= hang_end; m++) {
		for (n = 1; n <= 9; n++) {
			difference[m][n] = abs(p[m][n] - p[target_hang][n]);
		}
	}

	return 0;
}
//计算二级最大差异信息
double get_M(int hang_start, int hang_end, int lie_end) {
	int p, k;
	double max = difference[hang_end][lie_end];
	for (p = hang_start; p <= hang_end; p++) {
		for (k = 1; k <= lie_end; k++) {
			if (max <= difference[p][k])
				max = difference[p][k];
		}
	}
	return max;
}
//计算二级最小差异信息
double get_m(int hang_start, int hang_end, int lie_end) {
	int p, k;
	double min = difference[hang_end][lie_end];
	for (p = hang_start; p <= hang_end; p++) {
		for (k = 1; k <= lie_end; k++) {
			if (min >= difference[p][k])
				min = difference[p][k];
		}
	}
	return min;
}
//计算关联系数矩阵
int calculateRelate(double m, double M, int hang_start, int hang_end, int lie_end) {
	// 参数选0.5
	int p, k;
	double son;
	double mom;


	for (p = hang_start; p <= hang_end; p++) {
		double sum = 0;
		for (k = 1; k <= lie_end; k++) {
			son = m + 0.5 * M;
			mom = difference[p][k] + 0.5 * M;
			relate[p][k] = son / mom;
			sum = sum + relate[p][k];
		}
	}
	return 0;
}
//计算灰聚类值
int getRelation(int i, int hang_end, int lie_end) {
	int p, k;
	int r = i;
	for (p = i; p <= hang_end; p++) {
		double sum = 0;

		for (k = 1; k <= lie_end; k++) {
			sum = sum + relate[p][k];
		}
		relation[i][r] = sum / 9;
		r++;
	}

	return 0;
}

//计算单个灰关联
double getRelate(int Comparison_target, int Comparison_candidates, int hang_start, int hang_end, int lie_end) {
	//在此之前差异信息矩阵已经计算出来了

	double M = get_M(hang_start, hang_end, lie_end);
	//	cout << "M = " << M;

	double m = get_m(hang_start, hang_end, lie_end);
	//	cout << "   m = " << m << endl;

	calculateRelate(m, M, hang_start, hang_end, lie_end);
	return 0;
}
//消除数据量纲和极性
int clear(int hang_end, int lie_end) {
	/*int i, j;
	double temp;
	for (i = 1; i <= hang_end; i++) {
	temp = a[i][1];
	for (j = 1; j <= lie_end; j++) {
	a[i][j] = a[i][j] / temp ;
	}
	}*/
	int i, j;
	double temp;
	for (i = 1; i <= hang_end; i++) {
		double min = a[i][1];
		double max = a[i][1];
		for (j = 1; j <= lie_end; j++) {
			if (max <= a[i][j]) max = a[i][j];
			if (min >= a[i][j]) min = a[i][j];
		}

		for (j = 1; j <= lie_end; j++) {
			a[i][j] = abs(a[i][j] - min) / (max - min);
		}
	}
	return 0;
}

int visit(int i) {
	cout << i << " ";
	whether[i] = 1;
	int v;
	for (v = 0; v < 15; v++) {
		if (whether[v] == 0 && Class[i][v] == 1)
			visit(v);
	}
	return 0;
}
////灰聚类指出  >=0.8
//int getClass() {
//	int i, j;
//	int p, k;
//	int m = 1, n = 1;
//	cout << "邻接矩阵 " << "----------------------------------------------------" << endl;
//	for (i = 1; i <= 15; i++) {	
//		for (j = 1; j <= 15; j++) {
//			if (relation[i][j] >= 0.8 && i != j)
//			{
//				Class[i][j] = 1;
//				Class[j][i] = 1;
//				
//			}
//			
//			cout << Class[i][j] << " ";			
//		}
//		cout << endl;
//	}
//
//	for (i = 1; i <= 15; i++) {
//		visit(i);
//	}
//	return 0;
//}
//得到新的数据输入
int getDiff(int hang_end, int lie_end) {
	int i, j;
	for (int i = 1; i <= hang_end; i++) {
		for (j = 1; j <= lie_end; j++) {
			if (i == 1) { Diff[i][j] = a[1][j]; }
			if (i == 2) { Diff[i][j] = a[6][j]; }
			if (i == 3) { Diff[i][j] = a[7][j]; }
			if (i == 4) { Diff[i][j] = a[11][j]; }
			if (i == 5) { Diff[i][j] = a[12][j]; }
			if (i == 6) { Diff[i][j] = a[14][j]; }

		}
	}

	return 0;
}
//获取特征变量
int getStand(int hang_end, int lie_end) {
	int i, j;

	for (i = 1; i <= lie_end; i++) {
		double max = 0;
		for (j = 1; j <= hang_end; j++) {
			if (max <= Diff[j][i])
			{
				max = Diff[j][i];
			}

		}
		j = j;
		Diff[j][i] = max;

	}
	return 0;
}
//得到修改后的灰色系数矩阵
int getRelation2(int hang_end, int lie_end) {
	int i, j;
	for (j = 1; j <= lie_end; j++) {
		double sum = 0;
		for (i = 1; i <= hang_end; i++) {
			sum = sum + relate[i][j];
		}
		relate[hang_end + 1][j] = sum / hang_end;
	}

	return 0;
}

void function_A() {
	int i, j;
	for (i = 1; i <= 14; i++) {
		memset(difference, 0, sizeof(difference));// 置空差异信息矩阵
		memset(relate, 0, sizeof(relate));//置空灰关联系数矩阵

		getMyDiff(i, 15, i, a);//填写差异矩阵


							   /*{
							   cout << "第" << i << "行为基准的差异信息矩阵为下(difference[][])" << endl;
							   myCOUT(difference, 15, 9);
							   cout << "--------------------------------" << endl;
							   }*/

		for (j = i; j <= 15; j++) {
			getRelate(i, j, i, 15, 9);//填写灰关联系数矩阵
		}

		getRelation(i, 15, 15);//填写灰聚类矩阵
		if (i == 14)
		{
			cout << "第" << i << "行为基准的灰聚类矩阵为下(relation[][])" << endl;
			myCOUT(relation, 15, 15);
			cout << "--------------------------------" << endl;

		}


	}
}

void function_B() {
	int i, j;
	getDiff(6, 9);
	cout << "输入初始属性数据如下" << endl;   myCOUT(Diff, 6, 9); cout << "--------------------------------" << endl;
	getStand(6, 9);
	cout << "输入初始属性数据如下,其中第7行显示为特征向量" << endl;   myCOUT(Diff, 7, 9); cout << "--------------------------------" << endl;

	memset(difference, 0, sizeof(difference));// 置空差异信息矩阵
	memset(relate, 0, sizeof(relate));//置空灰关联系数矩阵
	getMyDiff(1, 6, 7, Diff);//得到新的差异信息矩阵
	cout << "新的差异信息矩阵为" << endl; myCOUT(difference, 6, 9); cout << "--------------------------------" << endl;

	for (i = 1; i <= 6; i++)
		getRelate(7, i, 1, 6, 9);//填写灰关联系数矩阵  第一个参数为比较目标，第二个为比较候选人
	cout << "新灰关联系数矩阵为下(relate[][])" << endl; myCOUT(relate, 6, 9);   cout << "--------------------------------" << endl;

	cout << "由此可得综合评判结果矩阵 " << endl;
	getRelation2(6, 9);

	for (i = 1; i <= 9; i++)
		cout << relate[7][i] << " ";



}
int main() {
	relation[15][15] = 1.0;
	//freopen("C:\\Users\\linkey\\Desktop\\灰色\\选人in.txt", "r", stdin);//输入重定向输入流至文件
	freopen("C:\\Users\\linkey\\Desktop\\灰色\\选人out.txt", "w", stdout);
	freopen("\\选人in.txt", "r", stdin);
	getShuJu();//读取初始数据

				 //myCOUT(a, 15,9);
	clear(15, 9);//消除极性和量纲
	{//打印输入的数据检验是否正确
		cout << "输入初始属性消除量纲后数据如下" << endl;
		myCOUT(a, 15, 9);
		cout << "--------------------------------" << endl;
	}

	function_A();// 


				 //临界取值>=0.8

	cout << "有以上分析可知 X1，X2, X3，X4，X5，X8，X9，X10，11，X13，X14归为一类" << endl;
	cout << "X6归为一类" << endl;
	cout << "X7归为一类" << endl;
	cout << "X11归为一类" << endl;
	cout << "X12归为一类" << endl;
	cout << "X14归为一类" << endl;
	cout << "一共6个聚类" << endl;
	cout << "每一类最小角标数据为代表，重新设定初始数据，采用灰关联分析" << endl;

	function_B();

	//freopen("CON", "r", stdin);//把输入流和重定向会控制台
	fclose(stdin);//关闭文件 
	fclose(stdout);//关闭文件 
	system("pause");//暂停
	return 0;

}

