int ds[MAXN];

void run(int l, int r) {
	if (l + 1 == r)
		return;
	int m = (l + r) >> 1;
	run(l, m), run(m, r);
	s1 = s.substr(m, r - m) + "#" + s.substr(l, m - l);
	s2 = s1;
	reverse(ALL(s2));
	zf(s1, z1);
	zf(s2, z2);
	for (int i = l; i <= r; ++i)
		ds[i] = 0;
	//BEGIN PRIMITIVE TANDEMS
	for (int i = 1; i < r - m; ++i) {
		if (ds[m + i])
			continue;
		int go = z1[i] / i;
		for (int j = 1; j <= go; ++j)
			ds[m + (j + 1) * i] = 1;
	}
	for (int i = 1; i < m - l; ++i) {
		if (ds[m - i])
			continue;
		int go = z2[i] / i;
		for (int j = 1; j <= go; ++j)
			ds[m - i * (j + 1)] = 1;
	}
	//END PRIMITIVE TANDEMS
	for (int len = 1; len <= m - l; ++len) {
		int x = m - len;
		if (ds[x])
			continue;
		int xl = max(x - len + 1, x - z2[len]);
		int xr = min(x, x - len + z1[r - m + 1 + x - l]);
		for (int j = xl; j <= xr; ++j)
			vv[len].push_back(j);
	}
	for (int len = 1; len <= r - m; ++len) {
		int x = m + len;
		if (ds[x])
			continue;
		int xl = max(x + 1, x + len - z2[m - l + 1 + r - x]) - 2 * len;
		int xr = min(x + len - 1, x + z1[len]) - 2 * len;
		for (int j = xl; j <= xr; ++j)
			vv[len].push_back(j)
	}
}

