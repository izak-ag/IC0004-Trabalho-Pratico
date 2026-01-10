// Resolução do problema do caminho hamiltoniano reduzindo-o para SAT e solucionando com CDCL

#include <iostream>
#include "utils/utils.h"
#include "sat_solver/cdcl.h"
#define pii pair<int, int>

using namespace std;

int var(int k, int i, int n) {
    return k * n + i + 1;
}

int main(int argc, char* argv[]) {
    bool expmode = argc > 1;
    Benchmark bench;

    auto [adj, n, m] = read_graph();

    if (expmode) {
        bench.start();
    }

    vector<vector<int>> clauses;

    // Vide página 4 de https://www.csie.ntu.edu.tw/~lyuu/complexity/2011/20111018.pdf
    // Redução de HAMPATH para SAT

    // 1
    for (int j = 0; j < n; ++j) {
        vector<int> clause;
        for (int k = 0; k < n; ++k)
            clause.push_back(var(k, j, n));
        clauses.push_back(clause);
    }

    // 2
    for (int j = 0; j < n; ++j)
        for (int k1 = 0; k1 < n; ++k1)
            for (int k2 = k1 + 1; k2 < n; ++k2)
                clauses.push_back({-var(k1, j, n), -var(k2, j, n)});

    // 3
    for (int k = 0; k < n; ++k) {
        vector<int> clause;
        for (int j = 0; j < n; ++j)
            clause.push_back(var(k, j, n));
        clauses.push_back(clause);
    }

    // 4
    for (int k = 0; k < n; ++k)
        for (int j1 = 0; j1 < n; ++j1)
            for (int j2 = j1 + 1; j2 < n; ++j2)
                clauses.push_back({-var(k, j1, n), -var(k, j2, n)});

    // 5
    for (int k = 0; k < n - 1; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j && !adj[i][j])
                    clauses.push_back({-var(k, i, n), -var(k + 1, j, n)});
    
    stringstream ss;
    int nv = n*n, nc = clauses.size();

    ss << "p cnf " << nv << " " << nc << "\n";

    for (auto& c: clauses) {
        for (int lit: c)
            ss << lit << " ";
        ss << "0\n";
    }

    SATSolverCDCL solver;
    solver.initialize(ss);
    int sol = solver.CDCL();

    cout << (sol == RetVal::r_satisfied ? "SIM" : "NAO") << endl;

    if (expmode) {
        bench.stop();
        bench.save_results("results_sat", n, m);
    }
}