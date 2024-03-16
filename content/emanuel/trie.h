int nodes = 1;

void insert(string& s) {
	int pos = 0;
	
	for(int i = 0; i < (int) s.size(); i++) {
		int nxt = mapping(s[i]);
		
		if(trie[pos][nxt] == 0) 
			trie[pos][nxt] = nodes++;

		pos = trie[pos][nxt],
	}
	terminal[pos] = 1;
}

bool search(string& s) {
	int pos = 0;
	
	for(int i = 0; i < (int) s.size(); i++) {
		int nxt = mapping(s[i]);
		if(trie[pos][nxt] == 0) return false;
		pos = trie[pos][nxt];
	}
	
	return true;
}

void erase(string& s) {
	int pos = 0;
	
	for(int i = 0; i < (int) s.size(); i++) {
		int nxt = mapping(s[i]);
		frec[pos] -= 1;
		pos = trie[pos][nxt];
	}
	
	frec[pos] -= 1;
}
