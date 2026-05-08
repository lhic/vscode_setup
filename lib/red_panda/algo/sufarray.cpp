void buildsa() {
	s[n] = 0;
	++n;
	int sz = max(AL, n + 1) + 2;
	memset(cnt, 0, sizeof(cnt[0]) * sz);
	for (int i = 0; i < n; ++i)
		c[i] = s[i], ++cnt[c[i] + 1];
	for (int i = 1; i < sz; ++i)
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; ++i)
		p[cnt[c[i]]++] = i;
	for (int k = 0; (1 << k) < n; ++k) {
		for (int i = 0; i < n; ++i)
			p[i] = nm(p[i] - (1 << k), n);
		memset(cnt, 0, sizeof(cnt[0]) * sz);
		for (int i = 0; i < n; ++i)
			++cnt[c[i] + 1];
		for (int i = 1; i < sz; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = 0; i < n; ++i)
			p2[cnt[c[p[i]]]++] = p[i];
		memcpy(p, p2, sizeof(p[0]) * n);
		c2[p[0]] = 0;
		int now = 0;
		for (int i = 1; i < n; ++i) {
			if (c[p[i]] == c[p[i - 1]] &&
					c[nm(p[i] + (1 << k), n)] == c[nm(p[i - 1] + (1 << k), n)])
				c2[p[i]] = now;
			else
				c2[p[i]] = ++now;
		}
		memcpy(c, c2, sizeof(c[0]) * n);
		if (now == n - 1)
			break;
	}
	int lst = 0;
	for (int i = 0; i < n; ++i) {
		int x = c[i];
		lst = max(0, lst - 1);
		if (x == n - 1)
			lst = 0;
		else {
			int y = p[x + 1];
			while (i + lst < n && y + lst < n && s[i + lst] == s[y + lst])
				++lst;
			lcp[x] = lst;
		}
	}
	--n;
	for (int i = 0; i < n; ++i)
		p[i] = p[i + 1], --c[i], lcp[i] = lcp[i + 1];
}
