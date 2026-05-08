ll mul(ll a, ll b, ll m) {
  ll q = (ll)((ld)a * (ld)b / (ld)m);
  ll r = a * b - q * m;
  return (r + 5 * m) % m;
}
