// Chinese simplex

//WARNING: MAXN and MAXM are too small.
const ld eps = 1e-10;
struct Simplex{
	ld a[MAXN][MAXM], b[MAXN], c[MAXM], d[MAXN][MAXM];
	ld x[MAXM];
	int ix[MAXN + MAXM]; // !!! array all indexed from 0
	// max{cx} subject to {Ax<=b,x>=0}
	// n: constraints, m: vars !!!
	// x[] is the optimal solution vector
	// usage : 
	// value = simplex(a, b, c, N, M);
	Simplex() {
		memset(this, 0, sizeof(*this));
	}
	pair<ld,bool> simplex(int n, int m){
		++m;
		int r = n, s = m - 1;
		memset(d, 0, sizeof(d));
		for (int i = 0; i < n + m; ++i) ix[i] = i;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m - 1; ++j) d[i][j] = -a[i][j];
			d[i][m - 1] = 1;
			d[i][m] = b[i];
			if (d[r][m] > d[i][m]) r = i;
		}
		for (int j = 0; j < m - 1; ++j) d[n][j] = c[j];
		d[n + 1][m - 1] = -1;
		for (ld dd;; ) {
			if (r < n) {
				swap(ix[s], ix[r + m]);
				d[r][s] = 1.0 / d[r][s];
				for (int j = 0; j <= m; ++j)
					if (j != s) d[r][j] *= -d[r][s];
				for (int i = 0; i <= n + 1; ++i) if (i != r) {
					for (int j = 0; j <= m; ++j) if (j != s)
						d[i][j] += d[r][j] * d[i][s];
					d[i][s] *= d[r][s];
				}
			}
			r = -1; s = -1;
			for (int j = 0; j < m; ++j)
				if (s < 0 || ix[s] > ix[j]) {
					if (d[n + 1][j] > eps ||
							(d[n + 1][j] > -eps && d[n][j] > eps))
						s = j;
				}
			if (s < 0) break;
			for (int i = 0; i < n; ++i) if (d[i][s] < -eps) {
				if (r < 0 ||
						(dd = d[r][m] / d[r][s] - d[i][m] / d[i][s]) < -eps ||
						(dd < eps && ix[r + m] > ix[i + m]))
					r = i;
			}
			if (r < 0) return { 0 , false }; // not bounded
		}
		if (d[n + 1][m] < -eps) return { 0 , false }; // not executable
		ld ans = 0;
		for(int i=0; i<m; i++) x[i] = 0;
		for (int i = m; i < n + m; ++i) { // the missing enumerated x[i] = 0
			if (ix[i] < m - 1){
				ans += d[i - m][m] * c[ix[i]];
				x[ix[i]] = d[i-m][m];
			}
		}
		return { ans , true }; 
	}
};

// magic simplex by Ivan Belonogov

struct Simplex {
	// maximize C^{t}x suspect to Ax <= b
    ll a[MAX_M][MAX_N];
    ll b[MAX_M];
    ll c[MAX_N];
    ll v;    
    ll n, m;
    ll left[MAX_M];
    ll up[MAX_N];
	ll res[MAX_N];
	int pos[MAX_N];

   	Simplex() {
		memset(this, 0, sizeof(*this));
	}
 
    void pivot(ll x, ll y) {
        swap(left[x], up[y]); 
        ll k = a[x][y];
        assert(abs(k) == 1);
        a[x][y] = 1;
        b[x] /= k;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            a[x][i] = a[x][i] / k;
            if (a[x][i] != 0)
                pos[cur++] = i;
        }
        
        for (int i = 0; i < m; i++) {
            if (i == x || a[i][y] == 0) continue;
            ll cof = a[i][y];
            b[i] -= cof * b[x];
            a[i][y] = 0;
            for (int j = 0; j < cur; j++)
                a[i][pos[j]] -= cof * a[x][pos[j]];
        }
        ll cof = c[y];
        v += cof * b[x];
        c[y] = 0;
        for (int i = 0; i < cur; i++) {
            c[pos[i]] -= cof * a[x][pos[i]];
        }
    }

    void solve(int nn, int mm) {
		n = nn, m = mm;
        for (int i = 0; i < n; i++)
            up[i] = i;
        for (int i = 0; i < m; i++)
            left[i] = i + n;

        int c1 = 0;
        while (1) {
            int x = -1;
            for (int i = 0; i < m; i++)
                if (b[i] < 0 && (x == -1 || b[i] < b[x])) {
                    x = i;
                }
            if (x == -1) break;

            int y = -1;
            for (int j = 0; j < n; j++)
                if (a[x][j] < 0) {
                    y = j; 
                    break;
                }
            if (y == -1) {
                assert(false); // no solution
            }
            c1++;
            pivot(x, y);
        }
        while (1) {
            int y = -1;
            for (int i = 0; i < n; i++)
                if (c[i] > 0  && (y == -1 || (c[i] > c[y]))) {
                    y = i;
                }
            if (y == -1) break;
            
            int x = -1;
            for (int i = 0; i < m; i++) {
                if (a[i][y] > 0) {
                    if (x == -1 || (b[i] / a[i][y] < b[x] / a[x][y])) {
                        x = i;
                    } 
                }
            }
            if (y == -1) {
                assert(false); // infinite solution
            }
            pivot(x, y);
        }

        memset(res, 0, sizeof(res));

        for (int i = 0; i < m; i++) {
            if (left[i] < n) {
                res[left[i]] = b[i];
            }
        } 
      	
		// res is an answer, v = C^{T}res
    }
};
