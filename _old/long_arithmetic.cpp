const int base = (int)1E9;

struct lnum {
	vector<int> a;
	lnum() {
		a.clear();
		a.push_back(0);
	};
	lnum(int x) {
		a.clear();
		a.push_back(x);
	};

	void read() {
		char s[MAXN];
		scanf("%s", s);
		int len = strlen(s);

		a.clear();
		for (int i = len; i > 0; i -= 9) {
			s[i] = 0;
			a.push_back(atoi(i >= 9 ? s + i - 9 : s));
		}
	}

	void print() {
		int len = a.size() - 1;
		printf("%d", a.empty() ? 0 : a.back());
		ford(i, len)
			printf("%09d", a[i]);
		printf("\n");
	}

	void operator+=(lnum b) {
		int rest = 0, len = max(a.size(), b.a.size());
		for (int i = 0; i < len || rest; i++) {
			if ((int)a.size() <= i) a.push_back(0);
			a[i] += (i < (int)b.a.size() ? b.a[i] : 0) + rest;
			rest = a[i] >= base;
			if (rest) a[i] -= base;
		}
	}

	void operator-=(lnum b) {
		int rest = 0;
		for (int i = 0; i < (int)b.a.size() || rest; i++) {
			a[i] -= (i < (int)b.a.size() ? b.a[i] : 0) + rest;
			rest = a[i] < 0;
			if (rest) a[i] += base;
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
	}
};

typedef vector<int> lnum;

lnum readlnum() {
	char s[MAXN];
	scanf("%s", &s);
	int len = strlen(s);

	lnum res;
	res.clear();
	for(int i = len; i > 0; i -= 9) {
		s[i] = 0;
		res.push_back(atoi(i >= 9 ? s + i - 9 : s));
	}
	return res;
}

void writelnum(lnum a) {
	int len = a.size() - 1;
	printf("%d", a.empty() ? 0 : a.back());
	ford(i, len)
		printf("%09d", a[i]);
	printf("\n");
}

int operator>(lnum a, lnum b) {
	if (a.size() > b.size()) return 1;
	if (a.size() < b.size()) return -1;
	ford(i, a.size()) {
		if (a[i] > b[i]) return 1;
		if (a[i] < b[i]) return -1;
	}
	return 0;
}

lnum operator+(lnum a, lnum b) {
	lnum res;
	res.clear();
	int rest = 0, len = max(a.size(), b.size());
	for (int i = 0; i < len || rest; i++) {
		res.push_back(0);
		res[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0) + rest;
		rest = res[i] >= base;
		if (rest) res[i] -= base;
	}
	return res;
}

lnum operator-(lnum a, lnum b) {
	int rest = 0;
	for (int i = 0; i < b.size() || rest; i++) {
		a[i] -= (i < b.size() ? b[i] : 0) + rest;
		rest = a[i] < 0;
		if (rest) a[i] += INF;
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	return a;
}

lnum operator*(lnum a, lnum b) {
	lnum res(a.size() + b.size());
	for (int i = 0; i < a.size(); i++)
		for (int j = 0, rest = 0; j < b.size() || rest; j++) {
			ll cur = res[i + j] + 1ll * a[i] * (j < b.size() ? b[j] : 0) + rest;
			res[i + j] = int(cur % base);
			rest = int(cur / base);
		}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	return res;
}

lnum operator/(lnum a, int b) {
	int rest = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		ll cur = a[i] + rest * 1ll * INF;
		a[i] = int(cur / b);
		rest = int(cur % b);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	return a;
}

lnum longgcd(lnum a, lnum b) {
	int cmp = a > b;
	if ((a.size() == 1) && (a[0] == 0) || cmp == 0)
		return b;
	if ((b.size() == 1) && (b[0] == 0))
		return a;

	if ((a[0] % 2 == 0) && (b[0] % 2 == 0))
		return longgcd(a / 2, b / 2) * c; //c must be = 2
	if (a[0] % 2 == 0)
		return longgcd(a / 2, b);
	if (b[0] % 2 == 0)
		return longgcd(b / 2, a);

	if (cmp == 1)
		return longgcd(a - b, b);
	return longgcd(b - a, a);
}