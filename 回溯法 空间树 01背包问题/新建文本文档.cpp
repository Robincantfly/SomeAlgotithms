int cp = 0;//current price
int cw = 0;//current weight
int put[1000];//1��ʾװ�룬0��ʾ��װ��
int perp[1000];//�Լ۱�
int order[1000];
int bestp;//��ǰ���ż�ֵ
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
		perp[i] = v[i] / w[i]; //���㵥λ��ֵ����λ��������Ʒ��ֵ��
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
			if (perp[i]<perp[j])//ð������perp[],order[],sortv[],sortw[]
			{
				temp = perp[i];  //ð�ݶ�perp[]����
				perp[i] = perp[i];
				perp[j] = temp;

				temporder = order[i];//ð�ݶ�order[]����
				order[i] = order[j];
				order[j] = temporder;

				temp = v[i];//ð�ݶ�v[]����
				v[i] = v[j];
				v[j] = temp;

				temp = w[i];//ð�ݶ�w[]����
				w[i] = w[j];
				w[j] = temp;
			}
	}
}



//���ݺ���
void backtrack(int i, int n, int w[], int v[], int c)
{   //i����ָʾ����Ĳ������ڼ�������0��ʼ����ͬʱҲָʾ��ǰѡ���˼�����Ʒ
	double bound(int i, int c, int n, int w[], int v[]);
	if (i == n) //�ݹ�������ж�����
	{
		bestp = cp;
		return;
	}
	//�������ӽڵ���У���ֱ������������;
	//�������������ȼ����Ͻ纯�������ж��Ƿ����ȥ
	if (cw + w[i] <= c)//����Ʒi���뱳��,����������
	{
		cw += w[i];//ͬ�����µ�ǰ����������
		cp += v[i];//ͬ�����µ�ǰ�������ܼ�ֵ
		put[i] = 1;
		backtrack(i + 1, n, w, v, c);//�������������һ��
		cw -= w[i];//���ݸ�ԭ
		cp -= v[i];//���ݸ�ԭ
	}
	if (bound(i + 1, c, n, w, v)>bestp)//������������������������
		backtrack(i + 1, n, w, v, c);
}

//�����Ͻ纯��������Ϊ��֦
double bound(int i, int c, int n, int w[], int v[])
{   //�жϵ�ǰ�������ܼ�ֵcp��ʣ�����������ɵ�����ֵ<=��ǰ���ż�ֵ
	double leftw = c - cw;//ʣ�౳������
	double b = cp;//��¼��ǰ�������ܼ�ֵcp,������Ͻ�
				  //����Ʒ��λ������ֵ�ݼ�����װ����Ʒ
	while (i < n && w[i] <= leftw)
	{
		leftw -= w[i];
		b += v[i];
		i++;
	}
	//װ������
	if (i < n)
		b += v[i] / w[i] * leftw;
	return b;//���ؼ�������Ͻ�

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