//getPoint - возвращает направляющий вектор полуплоскости (l: getPoint(l)^p>=0)
//Считаем, что все прямые нормированы
//Считаем, что есть bounding box
//Возвращает вектор точек пересечения в ccw порядке

sort(lines.begin(), lines.end(), [] (line al, line bl) -> bool {
			point a = getPoint(al);
			point b = getPoint(bl);
			if (a.y >= 0 && b.y < 0)
				return 1;
			if (a.y < 0 && b.y >= 0)
				return 0;
			if (a.y == 0 && b.y == 0)
				return a.x > 0 && b.x < 0;
			return a * b > 0;
		});
vector<pair<line, int>> st;
for (int it = 0; it < 2; ++it)
	for (int i = 0; i < lines.size(); ++i) {
		int fl = 0;
		while (!st.empty()) {
			if ((getPoint(st.back().first) - getPoint(lines[i])).len() <= eps) {
				if (st.back().first.c >= lines[i].c) {
					fl = 1;
					break;
				}
				else
					st.pop_back();
			}
			else if (getPoint(st.back().first) * getPoint(lines[i]) <= eps / 2)
				return {}; //don't intersect
			else if (st.size() >= 2 &&
					st[st.size() - 2].first.get(cross(st.back().first, lines[i])) < 0) {
				st.pop_back();
			}
			else
				break;
		}
		if (!fl)
			st.push_back({lines[i], i});
	}
fill(en, en + lines.size(), -1);
vector<point> p;
for (int i = 0; i < st.size(); ++i) {
	int x = st[i].second;
	if (en[x] == -1)
		en[x] = i;
	else {
		for (int j = en[x]; j < i; ++j)
			p.push_back(cross(st[j].first, st[j + 1].first));
		break;
	}
}
return p;
