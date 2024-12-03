#include <bits/stdc++.h>
using namespace std;

mt19937 gen(69420);

int main() {
	while (true) {
		int N = 144;
		vector<int> A(N);
		for (int i = 0; i < N; i++) {
			A[i] = i;
		}
		shuffle(A.begin(), A.end(), gen);
		vector<int> orig = A;
		vector<int> gaps;
		for (int i = N - 1; i >= 1; i--) {
			int x = i;
			while (x % 2 == 0) {
				x /= 2;
			}
			while (x % 3 == 0) {
				x /= 3;
			}
			if (x == 1) {
				gaps.push_back(i);
			}
		}
		vector<pair<int, int>> swaps;
		for (auto gap: gaps) {
			for (int i = gap; i < N; i++) {
				for (int j = i; j >= gap && A[j] < A[j - gap]; j -= gap) {
					swap(A[j], A[j - gap]);
					swaps.push_back({j - gap, j});
				}
			}
		}
		for (int i = 0; i < N; i++) {
			assert(A[i] == i);
		}
		cout << swaps.size() << '\n';
/*		if ((int)swaps.size() == 6571) {
			fstream f("swaps.txt", ios::out);
			for (int i = 0; i < N; i++) {
				f << orig[i] << " ";
			}
			f << '\n';
			for (auto p: swaps) {
				f << p.first << " " << p.second << '\n';
			}
			f.close();
			return 0;
		}*/
	}
}