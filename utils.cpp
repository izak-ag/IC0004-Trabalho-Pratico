// Aqui ficam funções e bibliotecas que funcionam em mais de um SO

#include <bits/stdc++.h>
#define fori(e) for (int i=0; i<e; i++)

using namespace std;

vector<vector<bool>> read_graph() {
    int n, m, u, v;
    cin >> n >> m;

    vector<vector<bool>> adj(n);

    fori(n) {
        adj[i] = vector<bool>(n);
        fill(adj[i].begin(), adj[i].end(), 0);
    }

    fori(m) {
        cin >> u >> v;
        adj[u][v] = true;
        adj[v][u] = true;
    }

    return adj;
}


#ifdef _WIN32
// Bibliotecas e versões de funções específicas para Windows

// #include <windows.h>

#elif __linux__
// Bibliotecas e versões de funções específicas para Linux

#endif