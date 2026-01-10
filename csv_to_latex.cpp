/*
    Converte os arquivos com os resultados obtidos (results_*.csv)
    em um outro .csv que será utilizado pelo latex para plotar
    os gráficos no relatório
*/

#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <map>
#include <sstream>
#include <vector>
#define mean(v) accumulate(v.begin(), v.end(), 0.0)/v.size()

using namespace std;

class CSVData {
    vector<double> bmk_time, sat_time;
    vector<int> bmk_mem, sat_mem;
    
    public:
    int n;
    CSVData(){}

    CSVData(int n) {
        this->n = n;
    }

    void add(double bt, int bm, double st, int sm) {
        bmk_time.push_back(bt);
        bmk_mem.push_back(bm);
        sat_time.push_back(st);
        sat_mem.push_back(sm);
    }

    friend ostream& operator<<(ostream& os, const CSVData& c) {
        double bt = mean(c.bmk_time), 
               bm = mean(c.bmk_mem),
               st = mean(c.sat_time),
               sm = mean(c.sat_mem);
        
        if (bt == NAN || bm == NAN || st == NAN || sm == NAN) {
            return os;
        }

        os << format("\n{},{:.4f},{:.4f},{:.4f},{:.4f}", c.n, bt, bm, st, sm);
        return os;
    }
};

void comma_to_space(string& str) {
    for (char& c: str) {
        if (c == ',') {
            c = ' ';
        }
    }
}

int main() {
    ifstream bmk("results/results_bmk.csv"), sat("results/results_sat.csv");

    if (!bmk || !sat) return 1;

    bool ignore = true;
    map<int, CSVData> esp, med, den, datas[] = {esp, med, den};
    int bm, sm, n, datas_idx = 0;
    double bt, st;
    string _;

    for (int i = 5; i <= 25; i += 5) {
        for (auto& d: datas)
            d.insert({i, CSVData(i)});
    }

    for (string line_b, line_s; getline(bmk, line_b) && getline(sat, line_s);) {
        if (ignore) {
            ignore = false;
            continue;
        }

        comma_to_space(line_b);
        comma_to_space(line_s);

        istringstream sb(line_b), ss(line_s);
        sb >> n >> _ >> bt >> bm;
        ss >> _ >> _ >> st >> sm;

        datas[datas_idx][n].add(bt, bm, st, sm);
        ++datas_idx %= 3;
    }

    string fn[] = {"sparse", "medium", "dense"};

    for (int i = 0; i < 3; i++) {
        ofstream out("results/results_" + fn[i] + ".csv", ios::app);
        out << "n,bmk_time,sat_time,bmk_memory,sat_memory";

        for (auto& ln: datas[i]) {
            out << ln.second;
        }
    }
}