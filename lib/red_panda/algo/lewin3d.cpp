//call dfs(i,j), i,j is any edge on convex hull,  will visit all faces
void dfs(int i, int j) {
	if (vis[i][j]) return;
	vis[i][j] = true;

	int k = 0;
	while (k == i || k == j) k++;
	for (int l = 0; l < n; l++) {
		//side returns which side pts[l] lies on plane defined by pts i, j, k
		if (l != i && l != j && side(pts[i], pts[j], pts[k], pts[l]) > 0)
			k = l;
	}
	// points i,j,k form a face on convex hull.
	dfs(k, j);
	dfs(i, k);
}
