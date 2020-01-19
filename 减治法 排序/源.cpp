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
	//��ʼ���п����㷨 
	//���������ȱ���left������Ӧ������  ��ǰ������Ϊ�и�������� 
	double piovt = iArray[left];
	//������ʱ������������2�˵����� 
	int leftIndex = left;
	int rightIndex = right;
	while (leftIndex < rightIndex) { //��������ͨ��ѭ�����ұ߿�ʼ����һ������ֵС������ 
		while (leftIndex < rightIndex) { 
			//����ұߵ������ڵ�ǰ�Ĳ�����ֵ
			if (piovt <= iArray[rightIndex]) { 
				//�Ҷ�����ָʾ������ 
				rightIndex--;
			}
			else { //˵�������Ҷ˳��ֱ���ֵ��С������ 
				   //���ʱ�����ǾͿ��԰������С��������䵽������������Ӧ�ĵط� 
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//������Ҫ����ѭ���˵�ǰ������� 
				break;
			}
		} //����߿�ʼ����һ������ֵ���������д�ϴ����µĿ� 
		while (leftIndex < rightIndex) { //�����ߵ�����С����ֵ ��������ָʾ���������� 
			if (piovt >= iArray[leftIndex]) { leftIndex++; }
			else { //˵������������ҵ��˱���ֵ��������� 
				iArray[rightIndex] = iArray[leftIndex];
				rightIndex--;
				break;
			}
		}
	}
	iArray[leftIndex] = piovt;
	return leftIndex;
}
