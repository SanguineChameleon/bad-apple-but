#include<bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define pb push_back

typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;

const int N = 3e6 + 5;
const int mod = 1e9 + 7, oo = 1e18 + 7;

int n;

string s;

/*
answer = (n^2 + n)/2 - sum(x^2 + x)/2
2 * answer = n^2 + n - sum(x^2) - sum(x)
           = n^2 - sum(x^2)
*/

// ranges: consecutive types
#define ranges __ranges__
vector<ii> ranges;

int dp[N][2];

void process(){
    cin >> s; n = s.length();
    int streak = 0;
    for(int i = 0; i <= s.length(); i++){
        if(i && (i == s.length() || (s[i] != s[i - 1]))){
            //cout << s[i - 1] << "\n";
            ranges.pb({s[i - 1], streak});
            streak = 1;
        }
        else streak++;
    }
    if(ranges.size() == 1){
        cout << 0 << "\n";
        return;
    }
    for(int i = 0; i < ranges.size(); i++){
        if(ranges[i].fi != '?') continue;
        if(!i){
            ranges[i].fi = ranges[i + 1].fi;
            continue;
        }
        else if(i == ranges.size() - 1){
            ranges[i].fi = ranges[i - 1].fi;
            continue;
        }
        else if(ranges[i - 1].fi == ranges[i + 1].fi){
            ranges[i].fi = ranges[i - 1].fi;
        }
    }
    //for(auto it : ranges) cout << char(it.fi) << " " << it.se << "\n";
    //cout << "\n";
    vector<ii> ranges2;
    ranges2.pb(ranges[0]);
    for(int i = 1; i < ranges.size(); i++){
        if(ranges[i].fi == ranges2.back().fi) ranges2[ranges2.size() - 1].se += ranges[i].se;
        else ranges2.pb(ranges[i]);
    }
    ranges = ranges2;
    ranges2.clear();
    //for(auto it : ranges) cout << char(it.fi) << " " << it.se << "\n";
    //cout << "\n";
    for(int i = 0; i < ranges.size(); i++){
        //ranges2.pb(ranges[i]);
        if(i && ranges[i].fi != '?' && ranges2.back().fi != '?') ranges2.pb({'?', 0});
        ranges2.pb(ranges[i]); 
    }
    ranges = ranges2;
    if(ranges.size() == 1){
        cout << 0 << "\n";
        return;
    }
    //for(auto it : ranges) cout << char(it.fi) << " " << it.se << "\n";
    for(int i = 0; i < ranges.size(); i += 2) assert(ranges[i].fi != '?');
    for(int i = 1; i < ranges.size(); i += 2) assert(ranges[i].fi == '?');
    dp[1][0] = (ranges[0].se + ranges[1].se) * (ranges[0].se + ranges[1].se);
    dp[1][1] = (ranges[0].se * ranges[0].se);
    int lst = 1;
    for(int i = 3; i < ranges.size(); i += 2){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                int total = ranges[i - 1].se;
                if(k) total += ranges[i - 2].se;
                if(!j) total += ranges[i].se;
                dp[i][j] = max(dp[i][j], dp[i - 2][k] + total * total);
            }
        }
        lst = i;
    }
    dp[lst][0] += (ranges[lst + 1].se * ranges[lst + 1].se);
    dp[lst][1] += (ranges[lst + 1].se + ranges[lst].se) * (ranges[lst + 1].se + ranges[lst].se);
    cout << (n * n - max(dp[lst][0], dp[lst][1])) / 2 << "\n";
}

signed main(){
    freopen("adn.inp", "r", stdin);
    freopen("adn.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    process();
}