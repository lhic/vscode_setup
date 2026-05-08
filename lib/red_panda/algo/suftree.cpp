const int inf = 1e9;
char s[maxn];
map<int, int> to[maxn];
int len[maxn] = {inf}, fps[maxn], link[maxn];
int node, pos;
int sz = 1, n = 0;
 
int make_node(int _pos, int _len) {
    fps[sz] = _pos;
    len [sz] = _len;
    return sz++;
}
void go_edge() {
    while(pos > len[to[node][s[n - pos]]]) {
        node = to[node][s[n - pos]];
        pos -= len[node];
    }
}
void add_letter(int c) {
    s[n++] = c;
    pos++;
    int last = 0;
    while(pos > 0) {
        go_edge();
        int edge = s[n - pos];
        int &v = to[node][edge];
        int t = s[fps[v] + pos - 1];
        if(v == 0) {
            v = make_node(n - pos, inf);
            link[last] = node;
            last = 0;
        }
        else if(t == c) {
            link[last] = node;
            return;
        }
        else {
            int u = make_node(fps[v], pos - 1);
            to[u][c] = make_node(n - 1, inf);
            to[u][t] = v;
            fps[v] += pos - 1;
            len [v] -= pos - 1;
            v = u;
            link[last] = u;
            last = u;
        }
        if(node == 0)
            pos--;
        else
            node = link[node];
    }
}
//fps - first occurrence in string
//len - length of edge (inf for last edges
//link - suf link for vertices
