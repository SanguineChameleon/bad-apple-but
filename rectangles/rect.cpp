#include <bits/stdc++.h>
using namespace std;

const int FRAME_COUNT = 6572;
int grid[500][500];
bool line_col[500];
bool line_row[500];
int color[500][500];
int height[500];
int lt[500];
int rt[500];
int black_cnt;

void find_rect() {
	int best = 0;
	int lx = -1;
	int rx = -1;
	int ly = -1;
	int ry = -1;
	for (int j = 0; j < 480; j++) {
		height[j] = 0;
	}
	for (int i = 0; i < 360; i++) {
		for (int j = 0; j < 480; j++) {
			if (grid[i][j] == 1) {
				height[j]++;
			}
			else {
				height[j] = 0;
			}
		}
		vector<int> q = {-1};
		for (int j = 0; j < 480; j++) {
			while (q.back() > 0 && height[q.back()] >= height[j]) {
				q.pop_back();
			}
			lt[j] = q.back() + 1;
			q.push_back(j);
		}
		q = {480};
		for (int j = 479; j >= 0; j--) {
			while (q.back() < 480 && height[q.back()] >= height[j]) {
				q.pop_back();
			}
			rt[j] = q.back() - 1;
			q.push_back(j);
		}
		for (int j = 0; j < 480; j++) {
			int cur = height[j] * (rt[j] - lt[j] + 1);
			if (cur > best) {
				best = cur;
				lx = i - height[j] + 1;
				rx = i;
				ly = lt[j];
				ry = rt[j]; 
			}
		}
	}
	int width = (lx + ly) % 3;
	for (int i = lx; i <= min(359, lx + width); i++) {
		line_row[i] = true;
	}
	for (int i = max(0, rx - width); i <= rx; i++) {
		line_row[i] = true;
	}
	for (int i = ly; i <= min(479, ly + width); i++) {
		line_col[i] = true;
	}
	for (int i = max(0, ry - width); i <= ry; i++) {
		line_col[i] = true;
	}
	for (int i = lx; i <= rx; i++) {
		for (int j = ly; j <= ry; j++) {
			color[i][j] = 1;
			grid[i][j] = 0;
			black_cnt--;
		}
	}
}

int main() {
	auto t1 = clock();
	for (int id = 1; id <= FRAME_COUNT; id++) {
		for (int i = 0; i < 360; i++) {
			line_row[i] = false;
		}
		for (int i = 0; i < 480; i++) {
			line_col[i] = false;
		}
		string cmd1 = "python read_img.py frames/frame";
		cmd1 += to_string(id);
		cmd1 += ".png";
		system(cmd1.c_str());
		fstream f1("data.txt", ios::in);
		black_cnt = 0;
		for (int i = 0; i < 360; i++) {
			for (int j = 0; j < 480; j++) {
				f1 >> grid[i][j];
				if (grid[i][j] == 1) {
					black_cnt++;
				}
				color[i][j] = 0;
			}
		}
		bool inv = false;
		if (black_cnt > 86400) {
			black_cnt = 172800 - black_cnt;
			for (int i = 0; i < 360; i++) {
				for (int j = 0; j < 480; j++) {
					grid[i][j] ^= 1;
				}
			}
			inv = true;
		}
		f1.close();
		for (int i = 0; i < 10 && black_cnt > 0; i++) {
			find_rect();
		}
		for (int i = 0; i < 360; i++) {
			if (line_row[i]) {
				for (int j = 0; j < 480; j++) {
					color[i][j] = 1;
				}
			}
		}
		for (int i = 0; i < 480; i++) {
			if (line_col[i]) {
				for (int j = 0; j < 360; j++) {
					color[j][i] = 1;
				}
			}
		}
		fstream f2("rect.txt", ios::out | ios::trunc);
		for (int i = 0; i < 360; i++) {
			for (int j = 0; j < 480; j++) {
				f2 << (color[i][j] ^ inv) << '\n';
			}
		}
		f2.close();
		string cmd2 = "python rect.py ";
		cmd2 += to_string(id);
		system(cmd2.c_str());
	}
	auto t2 = clock();
	cout << t2 - t1;
}