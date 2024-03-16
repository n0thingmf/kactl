ll mul(ll a, ll b, ll c) {
	ll ans = 0;

	while(b > 0) {
		if(b&1) ans = (ans + a) % c;
		a = (a + a) % c;
		b >>= 1;
	}

	return ans;
}

ll ex(ll a, ll b, ll c) {
	ll ans = 1;

	while(b > 0) {
		if(b&1) ans = (ans * a) % c;
		a = (a * a) % c;
		b >>= 1;
	}

	return ans;
}
