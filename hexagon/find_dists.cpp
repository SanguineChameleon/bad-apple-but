#include <bits/stdc++.h>
using namespace std;

const int frame_count = 6572;
const int N = 23;
const int M = 35;
const int start_color[3] = {140, 201, 250};
const int end_color[3] = {29, 66, 155};
const int red_color[3] = {238, 128, 131};
const string alpha = "0123456789abcdef";
int a[N][M];
int dist[N][M];
int color[N][M][3];

bool valid(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M && a[x][y] == 1 && dist[x][y] == -1);
}

pair<int, int> nxt(int x, int y, int d) {
	if (d == 4) {
		x--;
		return {x, y};
	}
	if (d == 5) {
		x++;
		return {x, y};
	}
	if (y % 2 == 0 && d < 2) {
		x--;
	}
	if (y % 2 == 1 && d >= 2) {
		x++;
	}
	if (d % 2 == 0) {
		y--;
	}
	else {
		y++;
	}
	return {x, y};
}

void solve(int frame_id) {
	string name_in = "grids/grid" + to_string(frame_id) + ".txt";
	string name_out = "dists/dist" + to_string(frame_id) + ".txt";
	fstream file_in(name_in, fstream::in);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			file_in >> a[i][j];
		}
	}
	file_in.close();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dist[i][j] = -1;
			color[i][j][0] = -1;
			color[i][j][1] = -1;
			color[i][j][2] = -1;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (a[i][j] == 0) {
				color[i][j][0] = 255;
				color[i][j][1] = 255;
				color[i][j][2] = 255;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (valid(i, j)) {
				vector<pair<int, int>> q;
				q.emplace_back(i, j);
				dist[i][j] = 0;
				int max_dist = 0;
				int pt = 0;
				while (pt < (int)q.size()) {
					int cx = q[pt].first;
					int cy = q[pt].second;
					pt++;
					max_dist = max(max_dist, dist[cx][cy]);
					for (int k = 0; k < 6; k++) {
						auto p = nxt(cx, cy, k);
						int nx = p.first;
						int ny = p.second;
						if (valid(nx, ny)) {
							dist[nx][ny] = dist[cx][cy] + 1;
							q.emplace_back(nx, ny);
						}
					}
				}
				for (auto p: q) {
					int x = p.first;
					int y = p.second;
					if (dist[x][y] == 0) {
						color[x][y][0] = red_color[0];
						color[x][y][1] = red_color[1];
						color[x][y][2] = red_color[2];
						continue;
					}
					if (max_dist == 1) {
						color[x][y][0] = start_color[0];
						color[x][y][1] = start_color[1];
						color[x][y][2] = start_color[2];
						continue;
					}
					for (int k = 0; k < 3; k++) {
						color[x][y][k] = round(1.0L * start_color[k] - 1.0L * (start_color[k] - end_color[k]) * (dist[x][y] - 1) / (max_dist - 1));
					}
				}
			}
		}
	}
	fstream file_out(name_out, fstream::trunc | fstream::out);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			string hex = "#";
			for (int k = 0; k < 3; k++) {
				hex += alpha[color[i][j][k] / 16];
				hex += alpha[color[i][j][k] % 16];
			}
			file_out << hex << " ";
		}
		file_out << '\n';
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			file_out << dist[i][j] << " ";
		}
		file_out << '\n';
	}
	file_out.close();
	return;
}

int main() {
	for (int frame_id = 1; frame_id <= frame_count; frame_id++) {
		solve(frame_id);
	}
	return 0;
}