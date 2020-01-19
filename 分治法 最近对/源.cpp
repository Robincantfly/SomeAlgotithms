#include <math.h>
//����ṹ���ʾ����S�е� �������

struct point {

	int x, y, temp;

};
int *Closest(point S[], int low, int high);       //ʵ��������Ծ���

double Distance(point a, point b);                                  //������֮�����

int Partition(point r[], int first, int end);             //����

void QuickSort(point r[], int first, int end);         //��������


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

//ʵ��������Ծ���
int* Closest(point S[], int low, int high) {
	int a[3] = { 0 };
	int right = 0, left = 0;

	double d1, d2, d3, d;

	int mid, i, j, index;

	point P[1000];                   //��ŵ㼯�� P1��P2


									 //���ֻ�������㣬�������������ľ���

	if (high - low == 1) {

		a[2] = Distance(S[low], S[high]);
		a[0] = low;
		a[1] = high;
		return a;

	}


	//����������㣬�������Ծ���

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


	mid = (low + high) / 2;                      //�����м��
	int p1[3], p2[3], *tempp;
	tempp = Closest(S, low, mid); //�ݹ�����������
	for (i = 0; i < 3; i++) {
		p1[i] = tempp[i];
	}
	d1 = p1[2];

	tempp = Closest(S, mid + 1, high);          //�ݹ�����������
	for (i = 0; i < 3; i++) {
		p2[i] = tempp[i];
	}
	d2 = p2[2];

	if (d1 <= d2) {
		d = d1;
		a[2] = d1;
		a[0] = p1[0];
		a[1] = p1[1];
	}                         //����Ϊ����������

	else {
		d = d2;
		a[2] = d2;
		a[0] = p2[0];
		a[1] = p2[1];
	}

	index = 0;

	for (i = mid; i >= low; i--) {                //�����㼯��P1
		{
			P[index] = S[i];
			P[index].temp = i;
			index++;
		}
	}

	for (i = mid + 1; i <= high; i++) {           //�����㼯��P2             
		{
			P[index] = S[i];
			P[index].temp = i;
			index++;
		}
	}

	//�Լ���P1��P2��y������������

	QuickSort(P, 0, index - 1);


	//���δ�����P1��P2�еĵ�

	for (i = 0; i < index; i++) {

		for (j = i + 1; j < index; j++) {

			if (P[j].y - P[i].y >= d)           //����y����ķ�Χ����P[i]�������

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


//������֮�����

double Distance(point a, point b) {

	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

}


int Partition(point r[], int first, int end) {                           //����

	int i = first, j = end;                                                              //��ʼ������������

	while (i < j) {

		while (i < j && r[i].y <= r[j].y) j--;                            //�Ҳ�ɨ��

		if (i < j) {

			point temp = r[i]; r[i] = r[j]; r[j] = temp;     //����С��¼������ǰ��

			i++;

		}

		while (i < j && r[i].y <= r[j].y) i++;                          //���ɨ��

		if (i < j) {

			point temp = r[i]; r[i] = r[j]; r[j] = temp;    //���ϴ��¼����������

			j--;

		}

	}

	return i;                                                                               // ������ֵ��¼��λ��

}


void QuickSort(point r[], int first, int end) {  //��������

	int pivot;

	if (first < end) {

		pivot = Partition(r, first, end);             //���֣�pivot����ֵ�������е�λ��

		QuickSort(r, first, pivot - 1);               //���������1������������н��п�������

		QuickSort(r, pivot + 1, end);              //���������2�����Ҳ������н��п�������

	}

}
