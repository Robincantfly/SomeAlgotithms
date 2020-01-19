//StudybarCommentBegin
#include <iostream>
#include <math.h>
using namespace std;

int* tsp(double* px, double* py, int length);

void main()
{
	char x_char[10000];
	char y_char[10000];
	int length;
	double optimal;

	cin.getline(x_char, 10000);
	cin.getline(y_char, 10000);
	cin >> length;
	cin >> optimal;

	double x[1000];
	double y[1000];

	char* tmpStrX = strtok(x_char, "\t");
	for (int i = 0; i < length; i++)
	{
		x[i] = atof(tmpStrX);
		tmpStrX = strtok(NULL, "\t");
	}

	char* tmpStrY = strtok(y_char, "\t");
	for (int j = 0; j < length; j++)
	{
		y[j] = atof(tmpStrY);
		tmpStrY = strtok(NULL, "\t");
	}

	int* path = tsp(x, y, length);
	double cost = 0;
	for (int k = 0; k < length; k++)
	{
		int a = path[k];
		int b = path[(k + 1) % length];
		cout << "a=" << a << " b=" << b << endl;
		double d = (x[a] - x[b])* (x[a] - x[b]) + (y[a] - y[b])*(y[a] - y[b]);
		if (d == 0)
		{
			cout << 0 << endl;
			return;
		}
		cost += sqrt(d);
	}

	if (cost > 2 * optimal)
	{
		cout << 0 << endl;
		system("pause");
		return;
	}
	cout << 1 << endl;
	system("pause");
}

//StudybarCommentEnd
#include<algorithm>
#include<string.h>
#include<stdio.h>
const int num = 1000;//city number
const int width = 100;
const int height = 100;

typedef struct node {
	int x;
	int y;
}city;
city citys[num];//citys
double dic[num][num];//distance from two citys;
bool visit[num];//visited
int seq[num];//
double answer;
void init(double *x, double *y, int length) {//set N&&x-y设置N和citys[num]
	int i = 0;
	for (i = 0; i < length; i++) {
		citys[i].x = x[i];
		citys[i].y = y[i];
	}
}
void set_dic(int length) {//set distance
	for (int i = 0; i<length; ++i) {
		for (int j = 0; j<length; ++j) {
			dic[i][j] = sqrt(pow(citys[i].x - citys[j].x, 2) + pow(citys[i].y - citys[j].y, 2));
		}
	}
}
double dic_two_point(city a, city b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
double count_energy(int length,int* conf) {
	double temp = 0;
	for (int i = 1; i<length; ++i) {
		temp += dic_two_point(citys[conf[i]], citys[conf[i - 1]]);
	}
	temp += dic_two_point(citys[conf[0]], citys[conf[length - 1]]);
	return temp;
}
void moni(int length) {
	memset(visit, false, sizeof(visit));
	//int temp = rand() % length;
	int temp = 4;
	seq[0] = temp;
	visit[temp] = true;
	int mini = -1;
	int ans = 1e9;
	for (int i = 1; i < length; ++i) {//第i位应该经过的点
		ans = 1e9;
		mini = -1;
		for (int j = 0; j < length; ++j) {
			if (!visit[j] && ans > dic[seq[i - 1]][j]) {
				ans = dic[seq[i - 1]][j];
				mini = j;
			}
		}
		seq[i] = mini;
		visit[mini] = true;
	}
	answer = count_energy(length,seq);
}
int* tsp(double* px, double* py, int length) {
	init(px,py,length);//使用程序内置数据使用init()函数，
	set_dic(length);
	moni(length);
	return seq;
}