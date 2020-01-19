int findlastpoint(int x[], int length) {
	int i = 0;
	for (i = 0; i < length; i++) {
		if (x[i] == 0)
			return -1;
		if ((x[i] + i) >= (length - 1))
			return i;
	}
	return -1;
}

int Greedy(int x[], int length) {
	int lastp = findlastpoint(x, length);
	if (lastp == -1)
		return -1;
	else if (lastp == 0)
		return 1;
	int step = 2;
	while (lastp > 0) {
		lastp = findlastpoint(x, lastp);
		step++;
	}
	if (lastp == -1)
		return -1;
	return --step;
}

