// Aqui ficam funções e bibliotecas que funcionam em mais de um SO

#include <bits/stdc++.h>
#include "utils.h"
#define fori(e) for (int i=0; i<e; i++)

using namespace std;
namespace fs = filesystem;

tuple<vector<vector<bool>>, int, int> read_graph() {
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

    return {adj, n, m};
}

void Benchmark::start() {
    start_time = chrono::high_resolution_clock::now();
    start_memory_usage = current_memory_usage();
}

void Benchmark::stop() {
    TimePoint end_time = chrono::high_resolution_clock::now();
    size_t end_memory_usage = max_memory_usage();

    execution_time = (end_time - start_time).count();
    total_memory_usage = end_memory_usage - start_memory_usage;
}

void Benchmark::save_results(string filename, int n, int m) {
    ostringstream content;

    if (!fs::exists(filename+".csv")) {
        content << "n,m,time,memory";
    }

    content << format("\n{},{},{:.5f},{}", n, m, execution_time, total_memory_usage);
    ofstream(filename+".csv", ios::app) << content.str();
}


#ifdef _WIN32
// Bibliotecas e versões de funções específicas para Windows

#include <processthreadsapi.h>
#include <psapi.h>

PROCESS_MEMORY_COUNTERS memory_info() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    return pmc;
}

size_t Benchmark::max_memory_usage() {
    return memory_info().PeakWorkingSetSize/1024;
}

size_t Benchmark::current_memory_usage() {
    return memory_info().WorkingSetSize/1024;
}

#elif __linux__
// Bibliotecas e versões de funções específicas para Linux

size_t memory_status(string key) {
    ifstream status("/proc/self/status");
    string line, linekey;

    while (getline(status, line)) {
        istringstream iss(line);
        iss >> linekey;

        if (linekey == key) {
            size_t value;
            iss >> value;
            return value;
        }
    }

    return -1;
}

size_t Benchmark::max_memory_usage() {
    return memory_status("VmRSS:");
}

size_t Benchmark::current_memory_usage() {
    return memory_status("VmHWM:");
}

#endif