/* 
    utils.h - Módulo de funções que:
    1 - São utilizadas por mais de um programa; ou
    2 - São implementadas de maneira diferente para cada sistema operacional
*/

#pragma once
#include <chrono>
#include <vector>
#define TimePoint std::chrono::system_clock::time_point

// Classe para registrar as métricas do experimento
class Benchmark {
    TimePoint start_time;
    size_t start_memory_usage, total_memory_usage;
    double execution_time;

    size_t max_memory_usage();

    size_t current_memory_usage();

public:
    // Deve ser executado antes de executar experimento.
    // Marca o momento inicial e o uso atual de memória antes do experimento.
    void start();

    // Deve ser executado depois de executar experimento.
    // Calcula o tempo de execução e uso de memória do experimento.
    void stop();

    // Acrescenta os resultados do experimento em "[filename].csv".
    // Se esse arquivo não existir, ele é criado.
    void save_results(std::string filename, int n, int m);
};

// Lê um grafo pela entrada padrão. O grafo segue o mesmo padrão proposto no trabalho.
// Retorna a tripla <matriz de adjacencia, n, m>.
std::tuple<std::vector<std::vector<bool>>, int, int> read_graph();