#include <bits/stdc++.h>
using namespace std;

const string names[3] = {"gray", "yellow", "green"};
const int val[3] = {0, 255, 127};

ostream& operator<<(ostream &out, vector<pair<int, int>> row) {
	for (auto p: row) {
		out << (char)('a' + p.first) << "_" << names[p.second] << '\n';
	}
	return out;
}

int cnt[26] = {};
int digs[243][5];

const int FRAME_COUNT = 6572;
const int ANS_COUNT = 2309;
pair<int, int> pos[3][5][6][5];
int color[6][5];
int grid[500][500];
string ans[2500];
string guess[13000];
vector<pair<int, int>> pat[2500][243];
int ans_cnt;
int guess_cnt;
int order[2500];
int best_pat[2500][5];
mt19937 gen(69420);

int main() {
	for (int i = 0; i < ANS_COUNT; i++) {
		order[i] = i;
	}
	for (int i = 0; i < 243; i++) {
		int x = i;
		for (int j = 4; j >= 0; j--) {
			digs[i][j] = x % 3;
			x /= 3;
		}
	}
	fstream f_pos("positions.txt", ios::in);
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 5; col++) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 5; j++) {
					f_pos >> pos[row][col][i][j].first >> pos[row][col][i][j].second;
				}
			}
		}
	}
	f_pos.close();
	fstream f_pat("patterns.txt", ios::in);
	int id, num;
	while (f_pat >> id >> num) {
		pat[id][num].resize(5);
		for (int k = 0; k < 5; k++) {
			f_pat >> pat[id][num][k].first >> pat[id][num][k].second;
		}
	}
	f_pat.close();
	auto t1 = clock();
	for (int id = 1; id <= FRAME_COUNT; id++) {
		string cmd1 = "python scale.py ";
		cmd1 += to_string(id);
		system(cmd1.c_str());
		fstream f_data("data.txt", ios::in);
		for (int i = 0; i < 360; i++) {
			for (int j = 0; j < 480; j++) {
				f_data >> grid[i][j];
			}
		}
		fstream f_grid("grid.txt", ios::out | ios::trunc);
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 5; col++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						int off_x = pos[row][col][i][j].first;
						int off_y = pos[row][col][i][j].second;
						int sum = 0;
						for (int x = 0; x < 65; x++) {
							for (int y = 0; y < 65; y++) {
								sum += grid[(off_x + x) >> 2][(off_y + y) >> 2];
							}
						}
						int avg = round(sum / (65 * 65));
						int md = 1000;
						color[i][j] = -1;
						for (int k = 0; k < 3; k++) {
							int cd = abs(avg - val[k]);
							if (cd < md) {
								md = cd;
								color[i][j] = k;
							}
						}
					}
				}
				shuffle(order, order + ANS_COUNT, gen);
				int min_tot = 1000000;
				int best_ans = -1;
				for (int k = 0; k < ANS_COUNT; k++) {
					int ans_id = order[k];
					int cur_tot = 0;
					for (int i = 0; i < 5; i++) {
						int mi_row = 1000000;
						best_pat[ans_id][i] = -1;
						for (int num = 0; num < 242; num++) {
							if (pat[ans_id][num].empty()) {
								continue;
							}
							int cur_row = 0;
							for (int j = 0; j < 5; j++) {
								cur_row += abs(val[digs[num][j]] - val[color[i][j]]);
							}
							if (cur_row < mi_row) {
								mi_row = cur_row;
								best_pat[ans_id][i] = num;
							}
						}
						cur_tot += mi_row;
					}
					if (cur_tot < min_tot) {
						min_tot = cur_tot;
						best_ans = ans_id;
					}
				}
				for (int i = 0; i < 5; i++) {
					f_grid << pat[best_ans][best_pat[best_ans][i]] << '\n';
				}
				f_grid << pat[best_ans][242] << '\n';
			}
		}
		f_grid.close();
		string cmd2 = "python grid.py ";
		cmd2 += to_string(id);
		system(cmd2.c_str());
	}
	auto t2 = clock();
	cout << t2 - t1;
}