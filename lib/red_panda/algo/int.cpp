const ld C1 = sqrt(3.0 / 7 - 2.0 * sqrt(6.0 / 5) / 7.0);
const ld C2 = sqrt(3.0 / 7 + 2.0 * sqrt(6.0 / 5) / 7.0);
const ld D1 = (18.0 + sqrt(30)) / 36;
const ld D2 = (18.0 - sqrt(30)) / 36;
ld h = (rb - lb) / C / 2;
for (int i = 0; i < C; ++i) {
	ld x = (i + 1) * h * 2 + lb;
	ans += h * (D2 * (f(x - h * C2) + f(x + h * C2)) + D1 * (f(x - h * C1) + f(x + h * C1)));
}
