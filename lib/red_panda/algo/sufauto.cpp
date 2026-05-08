const int AL = 26;
const int SYM = 'a';

struct SA {
	vector<int> sf;
	vector<array<int, AL>> go;
	vector<int> len;
	int newn() {
		sf.push_back(-1);
		go.emplace_back(array<int, AL>());
		go.back().fill(-1);
		len.push_back(0);
		return sf.size() - 1;
	}
	SA(string s) {
		int cur = newn();
		for (int i = 0; i < s.size(); ++i) {
			int c = s[i] - SYM;
			int nw = newn();
			len[nw] = i + 1;
			while (cur != -1 && go[cur][c] == -1)
				go[cur][c] = nw, cur = sf[cur];
			if (cur == -1)
				sf[nw] = 0;
			else {
				int q = go[cur][c];
				if (len[q] == len[cur] + 1)
					sf[nw] = q;
				else {
					int cl = len.size();
					len.push_back(len[cur] + 1);
					go.push_back(go[q]);
					sf.push_back(sf[q]);
					sf[q] = sf[nw] = cl;
					while (cur != -1 && go[cur][c] == q)
						go[cur][c] = cl, cur = sf[cur];
				}
			}
			cur = nw;
		}
	}
};


