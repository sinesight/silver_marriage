enum type {End, Plus, Minus, Mul, Div, Pow, Root, BrOpen, BrClose, Num};

struct cur {
	type lexem;
	double value;
	int pos;
};

cur a;
string s;
int expr();
double ans;

void error() {
	cout << "Error in " << a.pos << " symbol.\n";
	exit(0);
}

void nextlexem() {
	switch (s[a.pos]) {
		case '.': {a.lexem = End; break;}
		case '+': {a.lexem = Plus; break;}
		case '-': {a.lexem = Minus; break;}
		case '*': {a.lexem = Mul; break;}
		case '/': {a.lexem = Div; break;}
		case '^': {a.lexem = Pow; break;}
		case '#': {a.lexem = Root; break;}
		case '(': {a.lexem = BrOpen; break;}
		case ')': {a.lexem = BrClose; break;}
		default: {
			if ('0' <= s[a.pos] && s[a.pos] <= '9') {
				a.value = 0;
				while ('0' <= s[a.pos] && s[a.pos] <= '9') {
					a.value = a.value * 10 + s[a.pos] - '0';
					a.pos++;
				}
				a.pos--;
				a.lexem = Num;
			} else
				error();
		}
	}
	a.pos++;
}

int mnog() {
	int r, t, znak = 1;
	while (a.lexem == Minus) {
		znak *= -1;
		nextlexem();
	}
	if (a.lexem == Num) {
		r = znak * a.value;
		nextlexem();
		return r;
	}
	if (a.lexem == BrOpen) {
		nextlexem();
		r = znak * expr();
		if (a.lexem != BrClose)
			error();
		nextlexem();
		return r;
	}
	error();
}

int slag() {
	int r, t;
	r = mnog();
	while (a.lexem == Mul) {
		nextlexem();
		t = mnog();
		r = r * t;
	}
	return r;
}

int expr() {
	int r, t, znak;
	r = slag();
	while (a.lexem == Plus || a.lexem == Minus) {
		if (a.lexem == Plus)
			znak = 1;
		else
			znak = -1;
		nextlexem();
		t = znak * slag();
		r = r + t;
	}
	return r;
}

<...>

	cin >> s;
	s += '.';
	a.pos = 0;
	nextlexem();
	ans = expr();