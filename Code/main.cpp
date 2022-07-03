// count numbers of pair (a[i], a[j]) satisfy |a[i] - a[j]| < D
// with D is integer
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define pb push_back
typedef long long ll;
typedef pair <int, int> pii;

int m, n, D;
vector <ll> a;

ll solve1() {
    ll ans = 0;
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = i + 1; j < (int)a.size(); ++j)
            if (a[j] - a[i] <= D)
                ++ans;
    return ans;
}

ll solve2() {
    ll ans = 0, left = 0, right = 0;
    vector <pii> b;
    // determine all intervals
    // using two pointers technique
    while ((left <= right) && (right < (int)a.size())) {
        while (a[right] - a[left] <= D && (right < (int)a.size()))
            ++right;
        b.pb({left + 1, right});
        ++left;
    }
    // 2C|left->right|
    ans += (b[0].S - b[0].F + 1) * (b[0].S - b[0].F) / 2;
    for (int i = 1; i < (int)b.size(); ++i) {
        ans += (b[i].S - b[i].F + 1) * (b[i].S - b[i].F) / 2;
        // eliminate the common interval between b[i - 1].F and b[i].S
        if (b[i - 1].S >= b[i].F)
            ans -= (b[i].F - b[i - 1].S + 1) * (b[i].F - b[i - 1].S) / 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n >> D;

    // input array and sum
    ll x, s = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> x;
            s += x;
        }
        a.pb(s);
        s = 0;
    }

    // sort increasing
    sort(a.begin(), a.end());

    // cmp solve1 and solve2
    cout << solve1() << " " << solve2();

    return 0;
}

// solution and coding by n_AuTahn
// time complexity of solve1 is O(n^2) because we are using naive algorithm
// the time of solve2 is O(nlogn), let see sorting part
