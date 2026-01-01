// Fortemente baseado em: https://www.geeksforgeeks.org/competitive-programming/hamiltonian-path-using-dynamic-programming/
// Resolução do problema do caminho hamiltoniano usando programação dinâmica (algoritmo de Bellman–Held–Karp)

#include <bits/stdc++.h>
#include "utils.h"
#define forx(x, e) for (int x = 0; x < e; x++)

using namespace std;


int main(int argc, char* argv[]) {
    // TODO: Gerar modo experimento - retorna dados de memória
    // utilizada e tempo de execução. O modo deve ser recebido
    // por parâmetros na linha de comando.

    auto adj = read_graph();

    int n = adj.size();
    bool **dp = new bool*[n];

    forx(i, n) {
        dp[i] = new bool[1<<n];
        memset(dp[i], 0, sizeof(bool)*(1<<n));
    }

    forx(i, n) {
        dp[i][1<<i] = 1;
    }

    forx(i, 1<<n) {
        forx(j, n) {
            if (i & (1 << j)) {
                forx(k, n) {
                    if (i & (1 << k) && adj[k][j] && j != k && dp[k][i ^ (1 << j)]) {
                        dp[j][i] = true;
                        break;
                    }
                }
            }
        }
    }

    forx(i, n) {
        if (dp[i][(1 << n) - 1]) {
            cout << "SIM\n";
            return 0;
        }
    }

    cout << "NAO\n";
}