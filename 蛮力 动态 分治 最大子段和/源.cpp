int BruteForce(int x[], int length) {
	int tempSum, maxSum;
	maxSum = 0;
	for (int i = 0; i < length; i++)       // 子序列起始位置
	{
		for (int j = i; j < length; j++)   // 子序列终止位置
		{
			tempSum = 0;
			for (int k = i; k < j; k++)   // 子序列遍历求和
				tempSum += x[k];
			if (tempSum > maxSum)       // 更新最大和值
				maxSum = tempSum;
		}
	}
	return maxSum;
}
//算法复杂度为O(n2)

int max3(int a, int b, int c)           // 求三个数的最大值
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
	if (left == right)          // 设置基准，即递归终止条件
		return array[left];

	int middle = (left + right) / 2;

	int leftMaxSubsequenceSum = MaxSubsequenceSum(array, left, middle);     // 求左半部分最大子序列和
	int rightMaxSubsquenceSum = MaxSubsequenceSum(array, middle + 1, right);    // 求右半部分最大子序列和

																				// 处理左右边界问题：最大子序列跨越中间，包含左半部分最右一个数，同时包含右半部分最左一个数
	int maxLeftBorderSum = 0;
	int maxRightBorderSum = 0;
	int tempSum = 0;        // 临时求和变量
	for (i = middle; i >= left; i--)
	{
		tempSum += array[i];
		if (tempSum > maxLeftBorderSum)
			maxLeftBorderSum = tempSum;     // 左边包含边界最大序列和
	}
	tempSum = 0;
	for (i = middle + 1; i < right; i++)
	{
		tempSum += array[i];
		if (tempSum > maxRightBorderSum)
			maxRightBorderSum = tempSum;    // 右边包含边界最大序列和
	}

	int maxBorderSum = maxRightBorderSum + maxLeftBorderSum;        // 最大边界子序列和等于两部分边界之和
	return max3(leftMaxSubsequenceSum, maxBorderSum, rightMaxSubsquenceSum);         // 返回三个部分的最大子序列和
}
//算法复杂度为O(nlogn)

int DivideConquer(int x[], int length) {
	return MaxSubsequenceSum(x, 0, length - 1);
}

int DynamicProgramming(int x[], int length) {
	int tempSum = 0;
	int maxSum = 0;
	for (int j = 0; j < length; j++)   // 子问题后边界
	{
		tempSum = (tempSum + x[j]) > x[j] ? (tempSum + x[j]) : x[j];
		if (tempSum > maxSum)   // 更新最大和
			maxSum = tempSum;

	}
	return maxSum;
}