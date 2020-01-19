/*
StudybarCommentBegin
#include<iostream>
using namespace std;

int BF(char* s, char* t);
int KMP(char* s, char* t);

char s[20000];
char t[1000];
int s_length;
int t_length;
int method_id;

void main()
{
	cin >> s;
	cin >> s_length;
	cin >> t;
	cin >> t_length;
	cin >> method_id;

	switch (method_id)
	{
	case 1:
		cout << BF(s, t) << endl;
		break;
	case 2:
		cout << KMP(s, t) << endl;
		break;
	default:
		cout << -1 << endl;
		break;
	}
}
StudybarCommentEnd
*/

int BF(char* s, char* t) {
	for (int i = 0; i < s_length-t_length+1; i++) {
		if (s[i] == t[0]) {
			int temp = i + 1;
			int failure_mark = 0;
			//ʧ���־
			for (int j = 1; j < t_length; j++) {
				if (s[temp] != t[j])
				{
					failure_mark = 1; break;
				}
				temp++;
			}
			if (failure_mark == 0)
			{
				return i;
		}
			failure_mark = 0;
		}
	}
	return NULL;
}
void GetNext(char* t, int next[]) {
	int i, j,len;
	next[0] = -1;
	for (j = 1; t[j] != '\0'; j++) //������next[j]
	{
		for (len = j - 1; len >= 1; len--) {
			//��ͬ�Ӵ���󳤶�Ϊj-1
			for (i = 0; i < len; i++) {
				//�϶��ǲ��ܵ��ڵģ���Ȼ����û����
				if (t[i] != t[j - len + i])
					break;
				//ͦ�����ģ�ֻҪ�����ڣ��ͽ�������
			}
			if (i == len) {
				//i=len˵�������Ǹ�ѭ��������ִ�ж�û�б�break
				next[j] = len; break;
			}
	}
		if (len < 1) next[j] = 0;
	}
}
int KMP(char* s, char* t){
	int i = 0, j = 0,temp=0;
	for (temp = 0; t[temp] != '\0'; temp++);
	//int *next;
	//next = new int[temp];
	int next[80];
	GetNext(t, next);
	while (i<s_length - t_length + 2) {
		if (s[i] == t[j]) {
			i++; j++;
		}
		else {
			j = next[j];
			if (j == -1) { i++; j++; }
		}
	}
	if (t[j] == '\0')
		return (i - temp);
	else
		return 0;
	//delete[] next;
}