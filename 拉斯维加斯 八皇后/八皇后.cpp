#include <time.h>

#define N 8
int x[8] = { 0 };

int Myrand(int a, int b) {
	return (rand() % (b - a + 1) + a);
}

int Place(int x[], int k) {
	int i;
	for (i = 0; i < k; i++)
		if (x[i] == x[k] || abs(i - k) == abs(x[i] - x[k]))
			return 1;

	return 0;
}

void Queen() {
	int i;
	int j;
	int count = 0;
	int flag, tmp;

	srand(time(NULL));

	do {
		flag = 1;
		for (i = 0; i < N;) {
			j = Myrand(1, N);
			x[i] = j;
			count++;
			if (!Place(x, i)) {
				count = 0;
				i++;
			}
			else if (count == N) {
				//                cout << "false...";
				flag = 0;
				break;
			}
		}

	} while (!flag);

	for (tmp = 0; tmp < N; tmp++) {
		chess[tmp][x[tmp] - 1] = 1;
	}

}
