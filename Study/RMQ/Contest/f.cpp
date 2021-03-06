#include <bits/stdc++.h>
#define maxn 1001

using namespace std;

int X, Y, p;
int st[4*maxn][4*maxn];

void build() {
	for (int i = 0; i <= 4*X; i++) {
		for (int j = 0; j <= 4*Y; j++) {
			st[i][j] = 0;
		}
	}
}

void updateY(int nox, int lx, int rx, int noy, int ly, int ry, int x, int y, int val) {
	if (ly == ry) {
		if (lx == rx) {
			st[nox][noy] += val;
		} else {
			st[nox][noy] = st[2*nox][noy] + st[2*nox+1][noy];
		}
	} else {
		int mid = (ly+ry)/2;
		if (y <= mid) {
			updateY(nox, lx, rx, 2*noy, ly, mid, x, y, val);
		} else {
			updateY(nox, lx, rx, 2*noy+1, mid+1, ry, x, y, val);
		}
		st[nox][noy] = st[nox][2*noy] + st[nox][2*noy+1];
	}
}

void updateX(int no, int lx, int rx, int x, int y, int val) {
	if (lx != rx) {
		int mid = (lx+rx)/2;
		if (x <= mid) updateX(2*no, lx, mid, x, y, val);
		else updateX(2*no+1, mid+1, rx, x, y, val);
	}
	updateY(no, lx, rx, 1, 1, Y, x, y, val);
}



int queryY(int nox, int noy, int ly, int ry, int lyq, int ryq) {
	if (ly > ryq || ry < lyq) return 0;
	if (ly >= lyq && ry <= ryq) {
		return st[nox][noy];
	}
	int mid = (ly+ry)/2;
	return queryY(nox, 2*noy, ly, mid, lyq, ryq) +
					queryY(nox, 2*noy+1, mid+1, ry, lyq, ryq);
}



int queryX(int no, int lx, int rx, int lxq, int rxq, int lyq, int ryq) {
	if (lx > rxq || rx < lxq) return 0;
	if (lx >= lxq && rx <= rxq) {
		return queryY(no, 1, 1, Y, lyq, ryq);
	}
	int mid = (lx+rx)/2;
	return queryX(2*no, lx, mid, lxq, rxq, lyq, ryq) +
					queryX(2*no+1, mid+1, rx, lxq, rxq, lyq, ryq);
}

int main () {

	while (scanf("%d %d %d", &X, &Y, &p) && X) {
		int q; scanf("%d", &q);

		for (int i = 0; i < q; i++) {
			char c; scanf(" %c", &c);
			if (c == 'A') {
				int n, a, b; scanf("%d %d %d", &n, &a, &b);
			  a++; b++; 
				updateX(1, 1, X, a, b, n);
			} else {
				int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				x1++; y1++; x2++; y2++;
				if (x1 > x2) swap(x1, x2);
				if (y1 > y2) swap(y1, y2);
				printf("%d\n", queryX(1, 1, X, x1, x2, y1, y2)*p);
			}
 		}
		puts("");
		build();
	}

	

	return 0;
}
