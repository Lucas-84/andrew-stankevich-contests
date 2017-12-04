#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int (i) = 0; (i) < n; ++(i))
#define repu(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define repd(i, a, b) for (int (i) = (b) - 1; (i) >= (a); --(i))
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
using lli = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vlli = vector<lli>;

vector<char> sops;
vi svals;

int sgn(int a) { return a > 0 ? 1 : -1; }

int powrec(int a, int b) {
    if (b == 0) return 1;
    int t = powrec(a, b / 2);
    if (b % 2 == 0) return t * t;
    return t * t * a;
}

map<char, pair<int, function<int(int, int)>>> ops = {
    {'+', {0, [&](int a, int b) { return a + b; }}},
    {'-', {0, [&](int a, int b) { return a - b; }}},
    {'/', {1, [&](int a, int b) { return a / b; }}},
    {'%', {1, [&](int a, int b) { return sgn(a) * sgn(b) * (abs(a) % abs(b)); }}},
    {'*', {1, [&](int a, int b) { return a * b; }}},
    {'^', {2, [&](int a, int b) { return powrec(a, b); }}},
    {'_', {3, nullptr}},
    {'#', {3, nullptr}},
    {'(', {-1, nullptr}},
    {')', {-1, nullptr}}
};

map<string, string> cc;

int convert(string s) {
    if (!isdigit(s[0])) {
        assert(isalpha(s[0]));
        return 0;
    }
    int ans = 0;
    for (char c: s) ans = ans * 10 + c - '0';
    return ans;
}

string getvars(string s) {
    if (!cc.count(s)) return s;
    return cc[s] = getvars(cc[s]);
}

int getvar(string s) {
    return convert(getvars(s));
}

void define(string s, string t) {
    if (s != t && !cc.count(s) && getvars(t) != s) cc[s] = t;
}

void process(auto cond) {
    while (!sops.empty() && cond()) {
        if (sops.back() != '(') {
            int a = svals.back(); svals.pop_back();
            if (sops.back() == '_') {
                svals.pb(-a);
            } else if (sops.back() == '#') {
                svals.pb(a);
            } else {
                assert(!svals.empty());
                int b = svals.back(); svals.pop_back();
                svals.pb(ops[sops.back()].snd(b, a));
            } 
        }
        sops.pop_back();
    }
}

int evaluate(string s) {
    int i = 0;
    bool unary = true;
    auto skip = [&]() { while (i < sz(s) && isspace(s[i])) i++; return i < sz(s); };
    while (skip()) {
        function<bool()> cond = [&]() { return false; };
        if (isalnum(s[i])) {
            string var;
            while (skip() && !ops.count(s[i]))
                var += s[i++];
            svals.pb(getvar(var));
            unary = false;
        } else {
            if (s[i] == ')') {
                cond = [&]() { return sops.back() != '('; };
                unary = false;
            } else if (s[i] == '(') {

            } else if (s[i] == '^') {
                cond = [&]() { return ops[s[i]].fst < ops[sops.back()].fst; };
            } else if (ops.count(s[i])) {
                if (unary) {
                    if (s[i] == '-') s[i] = '_';
                    else {
                        assert(s[i] == '+');
                        s[i] = '#';
                    }
                }
                if (!unary)
                    cond = [&]() { return ops[s[i]].fst <= ops[sops.back()].fst; };
            } else {
                assert(0);
            }
            process(cond);
            if (ops.count(s[i]) && s[i] != ')') {
                sops.pb(s[i]);
                unary = true;
            }
            if (s[i] == ')')
                sops.pop_back();
            i++;
        }
    } 
    process([&]() { return true; });
    return svals.back();
}

string lowered(const char *s) {
    string ans;
    rep(i, (int)strlen(s)) ans += tolower(s[i]);
    return ans;
}

int main() {
    freopen("plcool.in", "r", stdin);
    freopen("plcool.out", "w", stdout);
    char cmd[64];
    while (scanf(" %s", cmd) == 1) {
        if (strcmp(cmd, "print") == 0) {
            char line[256];
            scanf(" %[^\n]", line);
            int ans = evaluate(lowered(line));
            printf("%d\n", ans);
        } else {
            char v1[16], v2[16];
            scanf(" %s %s", v1, v2);
            define(lowered(v1), lowered(v2));
        }
    }
}
