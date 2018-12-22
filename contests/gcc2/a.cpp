#include <bits/stdc++.h>

using namespace std;

int main () {
	int n; scanf("%d", &n);
	int mat[n][n];

	for (int i = 0; i < n; i++) {
		mat[i][0] = 1;
		mat[0][i] = 1;
	}

	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			mat[i][j] = mat[i-1][j] + mat[i][j-1];

	printf("%d\n", mat[n-1][n-1]);

	return 0;
}