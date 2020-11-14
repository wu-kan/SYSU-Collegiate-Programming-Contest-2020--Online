#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000;
int n;
int L[maxn], R[maxn];
int size;
int heap[16385];  // 堆里面按R从小到大牌。 heap只存index。

int heap_remove_root(){
	int ret = heap[1];
	int x = heap[size];
	int i = 1;
	int ch = 2;
	size --;
	while (ch <= size){
		if (ch + 1 <= size && R[heap[ch + 1]] < R[heap[ch]]) ch++;
		if (R[x] <= R[heap[ch]]) break;
		heap[i] = heap[ch];
		i = ch; ch = i + i;
	}
	heap[i] = x;
	return ret;
}

void heap_insert(int x){
	size ++;
	int i = size;
	int f = i / 2;
	while (f > 0){
		if (R[heap[f]] <= R[x]) break;
		heap[i] = heap[f];
		i = f; f = i / 2;
	}
	heap[i] = x;
}

bool test(double delta){
	int i = 0; size = 0;
	double A = 0;
	while (A < 9999.9){
		while (i < n && L[i] <= delta + A + 0.1){
			heap_insert(i); i++;
		}
		bool updated = false;
		while (size > 0){
			int x = heap_remove_root();
			if (R[x] + delta >= A - 0.1){
				updated = true;
				if (A <= delta + L[x]) A = A + R[x] - L[x];
				else A = R[x] + delta;
				break;
			}
		}
		if (!updated) return false;
	}
	return true;
}



void sort(int l, int r){  // 按L的值从小到大排列
	if (l >= r) return;
	int x = L[(l + r) / 2];
	int i = l, j = r;
	while (i <= j){
		while (L[i] < x) i++;
		while (L[j] > x) j--;
		if (i <= j){
			int temp;
			temp = L[i]; L[i] = L[j]; L[j] = temp;
			temp = R[i]; R[i] = R[j]; R[j] = temp;
			i++; j--;
		}
	}
	sort(i, r); sort(l, j);
}

int main(){
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> L[i] >> R[i];

	sort(0, n - 1);

	int l = 0;
	int r = 20000;
	while (r > l){
		int now = (l + r) / 2;
		if (test(now / 2.0)) r = now;
		else l = now + 1;
	}

	cout << l / 2.0;
}
