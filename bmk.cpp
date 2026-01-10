// Fortemente baseado em: https://www.geeksforgeeks.org/competitive-programming/hamiltonian-path-using-dynamic-programming/
// Resolução do problema do caminho hamiltoniano usando programação dinâmica (algoritmo de Bellman–Held–Karp)

#include <cstring>
#include <iostream>
#include "utils/utils.h"
#define forx(x, e) for (int x = 0; x < e; x++)

using namespace std;


int main(int argc, char* argv[]) {
    bool expmode = argc > 1;
    Benchmark bench;

    auto [adj, n, m] = read_graph();

    if (expmode) {
        bench.start();
    }

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
            goto end_exp;
        }
    }

    cout << "NAO\n";

    end_exp:
    if (expmode) {
        bench.stop();
        bench.save_results("results_bmk", n, m);
    }
}