struct segment_tree {
    ll value, number[2];
    bool colour[2];
};

segment_tree t[MAXK * 2 + 1];

void tree_build() {
	forn(i, MAXK * 2 + 1) {
        t[i].value = 0;
        forn(j, 2) {
			t[i].colour[j] = 0;
			t[i].number[j] = 0;
		}
    }
}

void push(int v, int l, int r) {
    int len = (r - l + 1) / 2;
	forn(i, 2) {
		if (t[v].colour[i]) {
			if (v < MAXK) {
				t[2 * v].colour[i] = t[2 * v + 1].colour[i] = 1;
				if (i == 0) {
					t[2 * v].number[i] += t[v].number[i];
					t[2 * v + 1].number[i] += t[v].number[i];
					t[2 * v].value += t[v].number[i] * len;
					t[2 * v + 1].value += t[v].number[i] * len;
				} else {
					t[2 * v].number[i] = t[v].number[i];
					t[2 * v + 1].number[i] = t[v].number[i];
					t[2 * v].value = t[v].number[i] * len;
					t[2 * v + 1].value = t[v].number[i] * len;
				}
			}
			t[v].colour[i] = 0;
			t[v].number[i] = 0;
		}
	}
}

void update(int v, int l, int r, int a, int b, int x, int type) {
    push(v, l, r);
    if ((r < a) || (b < l))
        return;
    if ((a <= l) && (r <= b)) {
        t[v].colour[type] = 1;
		if (type == 0) {
			t[v].number[type] += x;
			t[v].value += x * (r - l + 1);
		} else {
			t[v].number[type] = x;
			t[v].value = x * (r - l + 1);
		}		
        return;
    }

    update(2 * v, l, (l + r) / 2, a, b, x, type);
    update(2 * v + 1, (l + r) / 2 + 1, r, a, b, x, type);
    t[v].value = t[2 * v].value + t[2 * v + 1].value;
}

ll get(int v, int l, int r, int a, int b) {
    push(v, l, r);
    if ((r < a) || (b < l))
        return 0;
    if ((a <= l) && (r <= b))
        return t[v].value;
    return get(2 * v, l, (l + r) / 2, a, b) + get(2 * v + 1, (l + r) / 2 + 1, r, a, b);
}
