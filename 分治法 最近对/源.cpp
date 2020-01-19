#include <math.h>
//定义结构体表示集合S中的 点的坐标

struct point {

	int x, y, temp;

};
int *Closest(point S[], int low, int high);       //实现求最近对距离

double Distance(point a, point b);                                  //求两点之间距离

int Partition(point r[], int first, int end);             //划分

void QuickSort(point r[], int first, int end);         //快速排序


double point_distance(double xi, double yi, double xj, double yj) {
	return (xi - xj)*(xi - xj) + (yi - yj)*(yi - yj);
}

int * BruteForce(double x[], double y[], int length) {
	double distance = 0;
	int point[3];

	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (!distance) {
				distance = point_distance(x[i], y[i], x[j], y[j]);
				point[0] = i;
				point[1] = j;
			}
			else {
				if (point_distance(x[i], y[i], x[j], y[j]) < distance) {
					distance = point_distance(x[i], y[i], x[j], y[j]);
					point[0] = i;
					point[1] = j;
					point[2] = sqrt(distance);
				}
			}

		}
	}

	return point;
}



int* DivideConquer(double x[], double y[], int length) {
	struct point S[1000];
	int i;
	for (i = 0; i<length; i++) {
		S[i].x = x[i];
		S[i].y = y[i];
	}
	int a[3] = { 0 };
	int b[3] = { 0 };
	int*p = Closest(S, 0, length - 1);
	for (i = 0; i<3; i++) {
		a[i] = p[i];
	}
	int*safe = BruteForce(x, y, length);
	for (i = 0; i<3; i++) {
		b[i] = safe[i];
	}
	for (i = 0; i<3; i++) {
		if (a[i] != b[i])
			return b;
	}
	return a;
}

//实现求最近对距离
int* Closest(point S[], int low, int high) {
	int a[3] = { 0 };
	int right = 0, left = 0;

	double d1, d2, d3, d;

	int mid, i, j, index;

	point P[1000];                   //存放点集合 P1和P2


									 //如果只有两个点，返回这两个点间的距离

	if (high - low == 1) {

		a[2] = Distance(S[low], S[high]);
		a[0] = low;
		a[1] = high;
		return a;

	}


	//如果有三个点，求最近点对距离

	if (high - low == 2) {

		d1 = Distance(S[low], S[low + 1]);

		d2 = Distance(S[low + 1], S[high]);

		d3 = Distance(S[low], S[high]);

		if ((d1 < d2) && (d1 < d3)) {

			a[2] = d1;
			a[0] = low;
			a[1] = low + 1;
			return a;

		}
		else if (d2 < d3) {

			a[2] = d2;
			a[0] = low + 1;
			a[1] = high;
			return a;

		}

		else {
			a[2] = d3;
			a[0] = low;
			a[1] = high;
			return a;

		}

	}


	mid = (low + high) / 2;                      //计算中间点
	int p1[3], p2[3], *tempp;
	tempp = Closest(S, low, mid); //递归求解子问题①
	for (i = 0; i < 3; i++) {
		p1[i] = tempp[i];
	}
	d1 = p1[2];

	tempp = Closest(S, mid + 1, high);          //递归求解子问题②
	for (i = 0; i < 3; i++) {
		p2[i] = tempp[i];
	}
	d2 = p2[2];

	if (d1 <= d2) {
		d = d1;
		a[2] = d1;
		a[0] = p1[0];
		a[1] = p1[1];
	}                         //已下为求解子问题③

	else {
		d = d2;
		a[2] = d2;
		a[0] = p2[0];
		a[1] = p2[1];
	}

	index = 0;

	for (i = mid; i >= low; i--) {                //建立点集合P1
		{
			P[index] = S[i];
			P[index].temp = i;
			index++;
		}
	}

	for (i = mid + 1; i <= high; i++) {           //建立点集合P2             
		{
			P[index] = S[i];
			P[index].temp = i;
			index++;
		}
	}

	//对集合P1、P2按y坐标升序排列

	QuickSort(P, 0, index - 1);


	//依次处理集合P1和P2中的点

	for (i = 0; i < index; i++) {

		for (j = i + 1; j < index; j++) {

			if (P[j].y - P[i].y >= d)           //超出y坐标的范围，点P[i]处理完毕

				break;

			else {

				d3 = Distance(P[i], P[j]);

				if (d3 < d)
				{
					d = d3;
					a[2] = d;
					a[0] = P[i].temp;
					a[1] = P[j].temp;
				}

			}

		}

	}

	return a;

}


//求两点之间距离

double Distance(point a, point b) {

	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

}


int Partition(point r[], int first, int end) {                           //划分

	int i = first, j = end;                                                              //初始化待划分区间

	while (i < j) {

		while (i < j && r[i].y <= r[j].y) j--;                            //右侧扫描

		if (i < j) {

			point temp = r[i]; r[i] = r[j]; r[j] = temp;     //将较小记录交换到前面

			i++;

		}

		while (i < j && r[i].y <= r[j].y) i++;                          //左侧扫描

		if (i < j) {

			point temp = r[i]; r[i] = r[j]; r[j] = temp;    //将较大记录交换到后面

			j--;

		}

	}

	return i;                                                                               // 返回轴值记录的位置

}


void QuickSort(point r[], int first, int end) {  //快速排序

	int pivot;

	if (first < end) {

		pivot = Partition(r, first, end);             //划分，pivot是轴值在序列中的位置

		QuickSort(r, first, pivot - 1);               //求解子问题1，对左侧子序列进行快速排序

		QuickSort(r, pivot + 1, end);              //求解子问题2，对右侧子序列进行快速排序

	}

}
