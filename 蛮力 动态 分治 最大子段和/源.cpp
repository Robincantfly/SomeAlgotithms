int BruteForce(int x[], int length) {
	int tempSum, maxSum;
	maxSum = 0;
	for (int i = 0; i < length; i++)       // ��������ʼλ��
	{
		for (int j = i; j < length; j++)   // ��������ֹλ��
		{
			tempSum = 0;
			for (int k = i; k < j; k++)   // �����б������
				tempSum += x[k];
			if (tempSum > maxSum)       // ��������ֵ
				maxSum = tempSum;
		}
	}
	return maxSum;
}
//�㷨���Ӷ�ΪO(n2)

int max3(int a, int b, int c)           // �������������ֵ
{
	int max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return max;
}

int MaxSubsequenceSum(int array[], int left, int right)
{
	int i;
	if (left == right)          // ���û�׼�����ݹ���ֹ����
		return array[left];

	int middle = (left + right) / 2;

	int leftMaxSubsequenceSum = MaxSubsequenceSum(array, left, middle);     // ����벿����������к�
	int rightMaxSubsquenceSum = MaxSubsequenceSum(array, middle + 1, right);    // ���Ұ벿����������к�

																				// �������ұ߽����⣺��������п�Խ�м䣬������벿������һ������ͬʱ�����Ұ벿������һ����
	int maxLeftBorderSum = 0;
	int maxRightBorderSum = 0;
	int tempSum = 0;        // ��ʱ��ͱ���
	for (i = middle; i >= left; i--)
	{
		tempSum += array[i];
		if (tempSum > maxLeftBorderSum)
			maxLeftBorderSum = tempSum;     // ��߰����߽�������к�
	}
	tempSum = 0;
	for (i = middle + 1; i < right; i++)
	{
		tempSum += array[i];
		if (tempSum > maxRightBorderSum)
			maxRightBorderSum = tempSum;    // �ұ߰����߽�������к�
	}

	int maxBorderSum = maxRightBorderSum + maxLeftBorderSum;        // ���߽������к͵��������ֱ߽�֮��
	return max3(leftMaxSubsequenceSum, maxBorderSum, rightMaxSubsquenceSum);         // �����������ֵ���������к�
}
//�㷨���Ӷ�ΪO(nlogn)

int DivideConquer(int x[], int length) {
	return MaxSubsequenceSum(x, 0, length - 1);
}

int DynamicProgramming(int x[], int length) {
	int tempSum = 0;
	int maxSum = 0;
	for (int j = 0; j < length; j++)   // �������߽�
	{
		tempSum = (tempSum + x[j]) > x[j] ? (tempSum + x[j]) : x[j];
		if (tempSum > maxSum)   // ��������
			maxSum = tempSum;

	}
	return maxSum;
}