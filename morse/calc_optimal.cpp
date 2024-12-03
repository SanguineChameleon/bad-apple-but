#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 20;
const int FRAME_COUNT = 6572;
const int N = 22;
const int M = 63;
const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 #";
const string chars = ".- /";
/*const vector<string> encoded = {
	".-", // normal
	"-...", // normal
	"-.-.", // normal
	"-..", // normal
	".", // normal
	"..-.", // normal
	"--.", // weird
	"....", // normal
	"..", // normal
	".---", // weird
	"-.-", // normal
	".-..", // normal
	"--", // weird
	"-.", // normal
	"---", // weird
	".--.", // weird
	"--.-", // weird
	".-.", // normal
	"...", // normal
	"-", // normal
	"..-", // normal
	"...-", // normal
	".--", // weird
	"-..-", // normal
	"-.--", // weird
	"--..", // weird
	"-----", // weird
	".----", // weird
	"..---", // weird
	"...--", // weird
	"....-", // normal
	".....", // normal
	"-....", // normal
	"--...", // weird
	"---..", // weird
	"----.", // weird
	"/",
	" ",
};*/

const vector<vector<string>> encoded = {
	{".-"},
	{"-..."},
	{"-.-."},
	{"-.."},
	{"."},
	{"..-."},
	{"-", "-."},
	{"...."},
	{".."},
	{".-", "-", "-"},
	{"-.-"},
	{".-.."},
	{"-", "-"},
	{"-."},
	{"-", "-", "-"},
	{".-", "-."},
	{"-", "-.-"},
	{".-."},
	{"..."},
	{"-"},
	{"..-"},
	{"...-"},
	{".-", "-"},
	{"-..-"},
	{"-.-", "-"},
	{"-", "-.."},
	{"-", "-", "-", "-", "-"},
	{".-", "-", "-", "-"},
	{"..-", "-", "-"},
	{"...-", "-"},
	{"....-"},
	{"....."},
	{"-...."},
	{"-", "-..."},
	{"-", "-", "-.."},
	{"-", "-", "-", "-."},
	{"/"},
	{" "},
};
int costs[N * M + 1][4];
pair<int, pair<int, int>> dp[N * M * 3 + 6];

// dot -> 0
// dash -> 1
// space -> 2
// slash -> 3

// pos * 3 + type
// type == 0 -> normal
// type == 1 -> last character was a space
// type == 2 -> string has ended

tuple<int, int, string> nxt_edge(int cur_state, int char_id) {
	char c = alpha[char_id];
	int pos = cur_state / 3;
	int type = cur_state % 3;
	if (type == 2 && c != '#') {
		return {-1, -1, ""};
	}
	if (type == 1 && (c == ' ' || c == '#')) {
		return {-1, -1, ""};
	}
	if (c == '#') {
		if (pos + 6 <= N * M) {
			return {-1, -1, ""};
		}
		return {(pos + 1) * 3 + 2, costs[pos + 1][2], " "};
	}
	string tot = "";
	int sum = 0;
	for (int i = 0; i < (int)encoded[char_id].size(); i++) {
		string add = encoded[char_id][i];
		int row1 = (pos + M - 1) / M;
		int row2 = (pos + ((int)add.size() + (i == 0)) + M - 1) / M;
		if (row1 == row2) {
			if (i == 0) {
				add = " " + add;
			}
		}
		else {
			add = string(row1 * M - pos, ' ') + add;
		}
		for (auto x: add) {
			pos++;
			if (pos > N * M) {
				return {-1, -1, ""};
			}
			sum += costs[pos][chars.find(x)];
			tot += x;
		}
	}
	return {pos * 3 + (c == ' '), sum, tot};
}


void solve(int id) {
	string name_in = "costs/costs" + to_string(id) + ".txt";
	string name_out = "strings/string" + to_string(id) + ".txt";
	fstream file_in(name_in, ios::in);
	fstream file_out(name_out, ios::out | ios::trunc);
	for (int i = 1; i <= N * M; i++) {
		for (int j = 0; j < 4; j++) {
			file_in >> costs[i][j];
		}
	}
	for (int pos = 0; pos <= N * M + 1; pos++) {
		for (int type = 0; type < 3; type++) {
			int cur_state = pos * 3 + type;
			dp[cur_state] = {INF, {-1, '?'}};
		}
	}
	dp[1] = {0, {-1, '?'}};
	for (int pos = 0; pos <= N * M; pos++) {
		for (int type = 0; type < 3; type++) {
			int cur_state = pos * 3 + type;
			if (dp[cur_state].first == INF) {
				continue;
			}
			for (int char_id = 0; char_id < (int)alpha.size(); char_id++) {
				auto [nxt_state, cost, add] = nxt_edge(cur_state, char_id);
				if (nxt_state != -1) {
					dp[nxt_state] = min(dp[nxt_state], {dp[cur_state].first + cost, {cur_state, char_id}});
				}
			}
		}
	}
	int cur_state = N * M * 3 + 5;
	string res = "";
	while (cur_state != 1) {
		res += alpha[dp[cur_state].second.second];
		cur_state = dp[cur_state].second.first;
	}
	reverse(res.begin(), res.end());
	while (res.back() == '#') {
		res.pop_back();
	}
	file_out << res;
/*	string grid = "";
	cur_state = 1;
	for (auto c: res) {
		int char_id = alpha.find(c);
		auto [nxt_state, cost, add] = nxt_edge(cur_state, char_id);
		grid += add;
		cur_state = nxt_state;
	}
	grid.resize(N * M, ' ');
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << grid[i * M + j];
		}
		cout << '\n';
	}*/
	file_in.close();
	file_out.close();
}

int main() {
	for (int id = 1; id <= FRAME_COUNT; id++) {
		solve(id);
	}
}