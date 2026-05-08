r[i] = 1;
for (int i = 2; i < MOD; ++i)
	r[i] = (MOD - (MOD / i) * r[MOD % i] % MOD) % MOD;
