/* 
    utils.h - Módulo de funções que:
    1 - São utilizadas por mais de um programa; ou
    2 - São implementadas de maneira diferente para cada sistema operacional
*/

#include <vector>

// Lê um grafo pela entrada padrão. O grafo segue o mesmo padrão proposto no trabalho
std::vector<std::vector<bool>> read_graph();