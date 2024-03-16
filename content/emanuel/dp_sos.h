
for(int i = 0; i < m; ++i) {
	for(int mask = 0; mask < (1<<m); mask++){
		if(mask & (1<<i)) dp[mask] += dp[mask^(1<<i)];                 
	}
}
