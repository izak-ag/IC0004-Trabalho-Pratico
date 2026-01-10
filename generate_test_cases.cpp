// Gerador de casos de testes

#include <bits/stdc++.h>
#include "jngen.h"
#define pii pair<int, int>

using namespace std;
namespace fs = filesystem;

map<int, tuple<pii, pii, pii>> graph_edges = {
//   Nº de vértices        Esparso        Médio        Denso
    {5,             {       {4, 5},       {6, 7},      {8, 9}        }},
    {10,            {       {9, 20},      {21, 30},    {31, 40}      }},
    {15,            {       {14, 30},     {31, 60},    {61, 90}      }},
    {20,            {       {19, 40},     {41, 80},    {81, 140}     }},
    {25,            {       {24, 60},     {61, 120},   {121, 210}    }},
  //{30,            {       {29, 90},     {91, 170},   {171, 300}    }}
};

void generate_graph_file(int n, int m, int& inc) {
    ostringstream filename;
    filename << setw(2) << setfill('0') << inc++;
    ofstream out("testcases/"+filename.str());

    Graph g = Graph::random(n, m)
                    .directed(false)
                    .allowMulti(false)
                    .allowLoops(false)
                    .connected(true)
                    .g();      
    out << g.printN().printM() << endl;
}

int main() {
    // Por questões de reprodutibilidade, o seed é fixo (os casos de testes são sempre os mesmos)
    rnd.seed(1767236400);

    if (!fs::exists("testcases")) {
        fs::create_directory("testcases");
    }

    int inc = 1;

    for (auto [n, m]: graph_edges) {
        auto [me, mm, md] = m;
        for (auto [m_min, m_max]: {me, mm, md}) {
            for (int i = 0; i < 3; i++){
                generate_graph_file(n, rnd.next(m_min, m_max), inc);
            }
        }
    }
}