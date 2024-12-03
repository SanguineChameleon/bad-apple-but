#include <bits/stdc++.h>
using namespace std;

const int FRAME_COUNT = 6572;
int piece[7000][50][50];
int grid[500][500];

int main() {
	fstream f("scaled.txt", ios::in);
	for (int id = 1; id <= FRAME_COUNT; id++) {
		for (int i = 0; i < 36; i++) {
			for (int j = 0; j < 48; j++) {
				f >> piece[id][i][j];
			}
		}
	}
	for (int id = 1; id <= FRAME_COUNT; id++) {
		string cmd1 = "python read_img.py frames/frame";
		cmd1 += to_string(id);
		cmd1 += ".png";
		system(cmd1.c_str());
		fstream f1("data.txt", ios::in);
		for (int i = 0; i < 360; i++) {
			for (int j = 0; j < 480; j++) {
				f1 >> grid[i][j];
			}
		}
		f1.close();
		fstream f2("grid.txt", ios::out | ios::trunc);
		for (int i = 0; i < 360; i += 36) {
			for (int j = 0; j < 480; j += 48) {
				int best = -1;
				int mi = 1e9;
				for (int pid = 1; pid <= FRAME_COUNT; pid++) {
					int sum = 0;
					for (int x = 0; x < 36; x++) {
						for (int y = 0; y < 48; y++) {
							sum += abs(grid[i + x][j + y] - piece[pid][x][y]);
						}
					}
					if (sum < mi) {
						best = pid;
						mi = sum;
					}
				}
				f2 << best << '\n';
			}
		}
		f2.close();
		string cmd2 = "python match.py ";
		cmd2 += to_string(id);
		system(cmd2.c_str());
	}
}