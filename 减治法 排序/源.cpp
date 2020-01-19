int index(double T[], int low, int high);
int mysearch(double T[], int low, int high, int k);

double search(double T[], int length, int k) {
	int low = 0, high = length - 1;
	int a=mysearch(T, low, high, k);
	return T[a];
}

int mysearch(double T[], int low, int high, int k) {
	int pin = index(T, low, high);
	if (pin == k - 1)
		return pin;
	else if (pin > k - 1) {
		high = pin;
		return mysearch(T, low, high, k);
	}
	else {
		low = pin+1;
		return mysearch(T, low, high,k);
	}
}

int index(double iArray[], int left, int right) {
	//开始进行快排算法 
	//首先我们先保存left索引对应的数据  当前数据作为切割数组的轴 
	double piovt = iArray[left];
	//定义临时变量保存数组2端的索引 
	int leftIndex = left;
	int rightIndex = right;
	while (leftIndex < rightIndex) { //现在我们通过循环从右边开始搜索一个比轴值小的数据 
		while (leftIndex < rightIndex) { 
			//如果右边的数大于当前的参数轴值
			if (piovt <= iArray[rightIndex]) { 
				//右端索引指示器左移 
				rightIndex--;
			}
			else { //说明我们右端出现比轴值更小的数据 
				   //这个时候我们就可以把这个更小的数据填充到索引轴索引对应的地方 
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//我们需要跳出循环了当前工作完毕 
				break;
			}
		} //从左边开始搜索一个比轴值更大的数填写上次留下的坑 
		while (leftIndex < rightIndex) { //如果左边的数据小于轴值 我们索引指示器就往右走 
			if (piovt >= iArray[leftIndex]) { leftIndex++; }
			else { //说明我们在左端找到了比轴值更大的数据 
				iArray[rightIndex] = iArray[leftIndex];
				rightIndex--;
				break;
			}
		}
	}
	iArray[leftIndex] = piovt;
	return leftIndex;
}
