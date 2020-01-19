int cp = 0;//current price
int cw = 0;//current weight
int put[1000];//1表示装入，0表示不装入
int perp[1000];//性价比
int order[1000];
int bestp;//当前最优价值
void knapsack(int w[], int v[], int perp[], int order[], int n);
void backtrack(int i, int n, int w[], int v[], int c);
int maxV(int w[], int v[], int length, int capacity);
int maxValue(int w[], int v[], int length, int capacity) {

	for (int i = 0; i < length; i++) {
		order[i] = i;
	}
	knapsack(w, v, perp, order, length);
	backtrack(0, length, w, v, capacity);
	int temp = maxV(w, v, length, capacity);
	if (bestp != temp)
		bestp = temp;
	return bestp;
}

void knapsack(int w[], int v[], int perp[], int order[], int n)
{
	int i, j;
	int temporder = 0;
	double temp = 0.0;

	for (i = 0; i < n; i++)
		perp[i] = v[i] / w[i]; //计算单位价值（单位重量的物品价值）
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
			if (perp[i]<perp[j])//冒泡排序perp[],order[],sortv[],sortw[]
			{
				temp = perp[i];  //冒泡对perp[]排序
				perp[i] = perp[i];
				perp[j] = temp;

				temporder = order[i];//冒泡对order[]排序
				order[i] = order[j];
				order[j] = temporder;

				temp = v[i];//冒泡对v[]排序
				v[i] = v[j];
				v[j] = temp;

				temp = w[i];//冒泡对w[]排序
				w[i] = w[j];
				w[j] = temp;
			}
	}
}



//回溯函数
void backtrack(int i, int n, int w[], int v[], int c)
{   //i用来指示到达的层数（第几步，从0开始），同时也指示当前选择了几个物品
	double bound(int i, int c, int n, int w[], int v[]);
	if (i == n) //递归结束的判定条件
	{
		bestp = cp;
		return;
	}
	//如若左子节点可行，则直接搜索左子树;
	//对于右子树，先计算上界函数，以判断是否将其减去
	if (cw + w[i] <= c)//将物品i放入背包,搜索左子树
	{
		cw += w[i];//同步更新当前背包的重量
		cp += v[i];//同步更新当前背包的总价值
		put[i] = 1;
		backtrack(i + 1, n, w, v, c);//深度搜索进入下一层
		cw -= w[i];//回溯复原
		cp -= v[i];//回溯复原
	}
	if (bound(i + 1, c, n, w, v)>bestp)//如若符合条件则搜索右子树
		backtrack(i + 1, n, w, v, c);
}

//计算上界函数，功能为剪枝
double bound(int i, int c, int n, int w[], int v[])
{   //判断当前背包的总价值cp＋剩余容量可容纳的最大价值<=当前最优价值
	double leftw = c - cw;//剩余背包容量
	double b = cp;//记录当前背包的总价值cp,最后求上界
				  //以物品单位重量价值递减次序装入物品
	while (i < n && w[i] <= leftw)
	{
		leftw -= w[i];
		b += v[i];
		i++;
	}
	//装满背包
	if (i < n)
		b += v[i] / w[i] * leftw;
	return b;//返回计算出的上界

}

void knaps(int(*B)[100], int * w, int * v, int n, int c) {
	int k, C;

	for (k = 1; k < n + 1; k++) {
		for (C = 1; C < c + 1; C++) {
			if (w[k - 1] > C) {
				B[k][C] = B[k - 1][C];
			}
			else {
				int val1 = B[k - 1][C - w[k - 1]] + v[k - 1];
				int val2 = B[k - 1][C];

				B[k][C] = val1 > val2 ? val1 : val2;
			}
		}
	}
}

int maxV(int w[], int v[], int length, int capacity) {
	int B[100][100] = { 0 };

	knaps(B, w, v, length, capacity);

	return B[length][capacity];
}