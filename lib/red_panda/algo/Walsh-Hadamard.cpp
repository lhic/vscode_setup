void fft1(int *a, int n) {
    for (int bl = 1; bl < n; bl *= 2) {
        for (int i = 0; i < n; i += 2 * bl) {
            for (int j = i; j < i + bl; ++j) {
                int u = a[j];
				int v = a[j + bl];
                a[j] = (u + v) % MOD;
                a[j + bl] = (u - v + MOD) % MOD;
            }
        }
    }
}

/*
 * Inverse "fft"
 * B2 - inverse of 2 modulo MOD
 */

void fft2(int *a, int n) {
    for (int bl = n / 2; bl >= 1; bl /= 2) {
        for (int i = 0; i < n; i += 2 * bl) {
            for (int j = i; j < i + bl; ++j) {
                int u = a[j];
				int v = a[j + bl];
                a[j] = (ll)(u + v) * B2 % MOD;
                a[j + bl] = (ll)(u - v + MOD) * B2 % MOD;
            }
        }
    }
}
