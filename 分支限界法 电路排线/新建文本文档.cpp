//c�ǲ��߾���01��n�Ǿ��󳤿���0��ʼ��a����㣬b���յ�
#include<queue>
int dir[4][2] = { 0 , 1 , 1 , 0 , 0 , -1 , -1 , 0 };
struct Point { //��ʾ����
	int x, y, step;
};
queue<Point> Q; //���Դ����չ�ڵ�Ķ���

int solve(int** c, int n, int a_row, int a_col, int b_row, int b_col) {
	Point u, v;
	int i;
	while (!Q.empty()) {
		u = Q.front(), Q.pop(); //�������е���Ԫ��ȡ��������չ
		if (u.x == b_row && u.y == b_col) return u.step; //�Ѿ����յ���
		for (i = 0; i < 4; i++) { //����4 �����������չ
			int xx = u.x + dir[i][0];
			int yy = u.y + dir[i][1];
			if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
			if (c[xx][yy]) continue;
			v.step = u.step + 1;
			v.x = xx, v.y = yy;
			c[xx][yy] = 1;
			Q.push(v);
		}
	}
	return -1;
}

int distance(int** c, int n, int a_row, int a_col, int b_row, int b_col) {
	Point u;
	u.x = a_row, u.y = a_col, u.step = 0;
	Q.push(u);
	c[a_row][a_col] = 1;
	int ans = solve(c,n,a_row,a_col,b_row,b_col);
	return ans;
}