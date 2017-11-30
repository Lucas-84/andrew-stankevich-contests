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

const int maxn = 20, maxm = 20;
bool seen[maxn][maxm];
int n, m;

const int basesz = 32;
const uint64_t base = 1ull << basesz;
struct BigInt {
    vector<uint32_t> digs;
    BigInt(uint64_t x=0) { while (x) { digs.push_back(x%base), x /= base; } }
    BigInt(const BigInt& other) : digs(other.digs) {}
    void operator=(const BigInt& other) { digs = other.digs; }

    void normalize() {
	while (digs.size() && !digs.back()) digs.pop_back();
    }

    bool zero() { return digs.empty(); }

    uint64_t value() {
	uint64_t res = 0;
	for (auto it = digs.rbegin(); it != digs.rend(); ++it)
	    res = res * base + *it;
	return res;
    }

    void add(int i, uint64_t x) {
	if (!x) return;
	if (i >= (int)digs.size())
	    digs.resize(i + 1);
	uint64_t y = uint64_t{digs[i]} + x;
	if (y < base) { digs[i] = y; return; }
	digs[i] = y % base;
	add(i + 1, y / base);
    }

    BigInt operator++() {
	BigInt old(*this);
	add(0,1);
	return old;
    }

    BigInt operator+(const BigInt& other)  const {
	BigInt res(other);
	for (size_t i = 0; i < digs.size(); ++i)
	    res.add(i, digs[i]);
	res.normalize();
	return res;
    }

    BigInt operator*(const BigInt& other) const {
	BigInt res;
	for (size_t i = 0; i < digs.size(); ++i)
	    for (size_t j = 0; j < other.digs.size(); ++j) {
		res.add(i + j, 1ll * digs[i] * other.digs[j]);
	    }
	res.normalize();
	return res;
    }

    BigInt operator>>(int shift) const {
	BigInt res;
	res.digs.resize(digs.size());
	for (size_t i = 0; i < digs.size(); ++i) {
	    uint32_t& cur = res.digs[i];
	    cur = digs[i]>>shift;
	    if (i + 1 < digs.size())
		cur |= (uint64_t{digs[i+1]} << (basesz - shift)) & (base - 1);
	}
	res.normalize();
	return res;
    }

    bool operator<(const BigInt& other) const {
	if (digs.size() != other.digs.size())
	    return digs.size() < other.digs.size();
	return lexicographical_compare(digs.rbegin(), digs.rend(),
		other.digs.rbegin(), other.digs.rend());
    }

    bool operator==(const BigInt& other) const {
	return !(*this < other) && !(other < *this);
    }

    pair<BigInt, BigInt> divmod(const BigInt& other) const {
	BigInt lo(0), hi(*this + 1); // here, hi is exclusive
	while (lo + 1 < hi) {
	    BigInt mid = (lo + hi)>>1;
	    //cout << " lo=" << lo << " hi=" << hi << " mid=" << mid << endl;
	    //cout << "    " << (*this) << " < " << (mid*other) << " = " << (*this<mid*other) << endl;
	    if (*this < mid * other) hi = mid;
	    else lo = mid;
	}
	BigInt div = lo;
	BigInt tmp = div * other;
	lo = 0; hi = other;
	while (lo < hi) {
	    BigInt mid = (lo + hi)>>1;
	    if (tmp + mid < *this) lo = mid + 1;
	    else hi = mid;
	}
	return {div, lo};
    }

    BigInt operator/(const BigInt& other) const { return divmod(other).first; }
    BigInt operator%(const BigInt& other) const { return divmod(other).second; }

    BigInt powmod(BigInt exp, BigInt mod) const {
	BigInt res(1), base(*this);
	res = res % mod;
	for (auto chunk : exp.digs)
	    for (int i = 0; i < basesz; ++i) {
		if ((chunk >> i) & 1)
		    res = (res * base) % mod;
		base = (base * base) % mod;
	    }
	return res;
    }

    string str(int base=10) const {
	const char* alph = "0123456789abcdef";

	BigInt bigbase(base), tmp(*this);
	string res;
	while (!tmp.zero()) {
	    res += alph[(tmp % bigbase).value()];
	    tmp = tmp / base;
	}
	if (res.empty()) res += '0';
	reverse(res.begin(), res.end());
	return res;
    }

    string bin() const { return str(2); }
    string hex() const { return str(16); }

    static BigInt parse(const string& s, int base=10) {
	const char* alph = "0123456789abcdef";
	BigInt res(0), basebig(base);
	for (char c: s) {
	    c = tolower(c);
	    const char* p = strchr(alph, c);
	    res = res * basebig + BigInt(p - alph);
	}
	return res;
    }
};

int count(int s1, int s2, int ri, int rj) {
    rep(i, n) rep(j, m) seen[i][j] = false;
    int ans = 0;
    rep(i, n) rep(j, m) if (!seen[i][j]) {
        int ni = i, nj = j, p = 0;
        while (!seen[ni][nj]) {
            seen[ni][nj] = 1;
            p++;
            if (s1) { int t = ni; ni = n - nj - 1; nj = t; }
            if (s2) { ni = n - ni - 1; nj = m - nj - 1; }
            ni = (ni + ri) % n;
            nj = (nj + rj) % m;
        }
        ans++;
    }
    return ans;
}

int main() {
    //freopen("tickets.in", "r", stdin);
    //freopen("tickets.out", "w", stdout);
    scanf("%d%d", &n, &m);
    BigInt ans(0);
    rep(s2, 2) rep(i, n) rep(j, m) {
        if (n == m) {
            rep(s1, 2) {
                int c = count(s1, s2, i, j);
                BigInt tmp(1);
                rep(t, c) tmp = tmp * BigInt(2);
                ans = ans + tmp;
            }
        } else {
            int c = count(0, s2, i, j);
            BigInt tmp(1);
            rep(t, c) tmp = tmp * BigInt(2);
            ans = ans + tmp;
        }
    }
    BigInt res;
    if (n == m) {
        assert(ans % (4 * n * m) == 0);
        res = ans / BigInt(4 * n * m);
    } else {
        assert(ans % (2 * n * m) == 0);
        res = ans / BigInt(2 * n * m);
    }
    printf("%s\n", res.str().c_str());
}
