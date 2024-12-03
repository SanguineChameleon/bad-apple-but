#include <bits/stdc++.h>
using namespace std;

const string names[3] = {"gray", "yellow", "green"};

ostream& operator<<(ostream &out, vector<pair<int, int>> row) {
	for (auto p: row) {
		out << (char)('a' + p.first) << "_" << names[p.second] << '\n';
	}
	return out;
}

int cnt[26] = {};
int digs[243][5];

vector<pair<int, int>> color(string ans, string guess) {
	vector<pair<int, int>> res(5);
	for (int i = 0; i < 26; i++) {
		cnt[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		res[i].first = guess[i] - 'a';
		cnt[ans[i] - 'a']++;
	}
	for (int i = 0; i < 5; i++) {
		if (guess[i] == ans[i]) {
			cnt[guess[i] - 'a']--;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (guess[i] == ans[i]) {
			res[i].second = 2;
		}
		else if (cnt[guess[i] - 'a'] > 0) {
			res[i].second = 1;
			cnt[guess[i] - 'a']--;
		}
		else {
			res[i].second = 0;
		}
	}
	return res;
}

mt19937 gen(69420);

string ans[2500];
string guess[13000];
vector<pair<int, int>> pat[2500][243];
int ans_cnt;
int guess_cnt;

int main() {
	for (int i = 0; i < 243; i++) {
		int x = i;
		for (int j = 4; j >= 0; j--) {
			digs[i][j] = x % 3;
			x /= 3;
		}
	}
	fstream f_ans("answers.txt");
	string s;
	while (f_ans >> s) {
		ans[ans_cnt++] = s;
	}
	f_ans.close();
	fstream f_guess("guesses.txt");
	while (f_guess >> s) {
		guess[guess_cnt++] = s;
	}
	for (int i = 0; i < ans_cnt; i++) {
		shuffle(guess, guess + guess_cnt, gen);
		for (int j = 0; j < guess_cnt; j++) {
			auto p = color(ans[i], guess[j]);
			int num = 0;
			for (int k = 0; k < 5; k++) {
				num = num * 3 + p[k].second;
			}
			if (pat[i][num].empty()) {
				pat[i][num] = p;
			}
		}
		pat[i][242] = color(ans[i], ans[i]);
	}
	freopen("patterns.txt", "w", stdout);
	for (int i = 0; i < ans_cnt; i++) {
		for (int num = 0; num < 243; num++) {
			if (!pat[i][num].empty()) {
				cout << i << " " << num << '\n';
				for (int k = 0; k < 5; k++) {
					cout << pat[i][num][k].first << " " << pat[i][num][k].second << '\n';
				}
			}
		}
	}
}