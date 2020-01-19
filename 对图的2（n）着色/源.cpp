//StudybarCommentBegin
#include <iostream>
using namespace std;

bool color(int* u, int* v, int length);

void main()
{
	char u_char[10000];
	char v_char[10000];
	int input_length;

	cin.getline(u_char, 10000);
	cin.getline(v_char, 10000);
	cin >> input_length;

	int u[1000];
	int v[1000];

	char* tmpStrX = strtok(u_char, " ");
	for (int i = 0; i < input_length; i++)
	{
		u[i] = atoi(tmpStrX);
		tmpStrX = strtok(NULL, " ");
	}

	char* tmpStrY = strtok(v_char, " ");
	for (int j = 0; j < input_length; j++)
	{
		v[j] = atoi(tmpStrY);
		tmpStrY = strtok(NULL, " ");
	}

	cout << color(u, v, input_length);
	system("pause");
}
//StudybarCommentEnd
void MCOLORING(int);
#define MAX 8

bool GRAPH[MAX][MAX];
int X[MAX];
int m, n;
int COUNT = 0;

bool color(int* u, int* v, int length) {
	m = 2;
	int i, j, k, e;

	n = u[0];
	e = v[0];//n=顶点的个数，e=边的个数
			 //初始化图G
	for (i = 0; i <= n; i++)
	{
		X[i] = 0;
		for (j = 0; j <= n; j++)
		{
			GRAPH[i][j] = 0;
		}
	}
	//构建图G
	for (k = 1; k <= e; k++)
	{
		i = u[k];
		j = v[k];
		GRAPH[i][j] = 1;
		GRAPH[j][i] = 1;
	}
	MCOLORING(1);
	if (COUNT == 0)
		return false;
	return true;
}



bool NEXTVALUE(int k)
{
	int j;
	while (true)
	{
		X[k] = (X[k] + 1) % (m + 1);
		if (X[k] == 0)
			return false;
		for (j = 1; j <= n; j++)
		{
			if (GRAPH[k][j] && (X[k] == X[j]))
				break;
		}
		if (j == n + 1)
			return true;
	}
}

void printX()
{
	int i = 0;
	COUNT++;
}
void MCOLORING(int k)
{
	while (true)
	{
		NEXTVALUE(k);
		if (X[k] == 0)
			return;
		if (k == n)
			printX();
		else
			MCOLORING(k + 1);
	}

}