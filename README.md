# IC0004-Trabalho-Pratico

Este repositório contém o material desenvolvido no trabalho prático da disciplina Algoritmos e Grafos (IC0004) do PGCOMP/UFBA.

O trabalho consiste em um estudo teórico e experimental sobre o Problema do Caminho Hamiltoniano, com foco na análise comparativa de desempenho entre duas abordagens exatas para a sua versão de decisão.

Aqui estão disponíveis:

* o código-fonte dos algoritmos implementados e dos programas utilizados para execução do experimento
* os dados gerados durante as execuções

O código-fonte do relatório resultante do estudo também está disponível neste repositório, no diretório [`relatório`](./relatório).


## Requisitos

Para executar o projeto, é necessário apenas que o compilador `g++` esteja instalado na máquina, preferencialmente em uma versão compatível com o padrão **C++23**.

O padrão C++20 também é suportado, mas nesse caso é necessário alterar a variável `CPPVER` no arquivo `project.bat` ou `project.sh`. Versões anteriores ao C++20 não são compatíveis com o projeto.

O sistema operacional deve ser ou **Windows** ou **Linux**. O projeto pode ser executado em ambos sem restrições ou limitações.


## Execução do projeto

O projeto pode ser executado por meio dos scripts `project.bat` (Windows) ou `project.sh` (Linux). Ambos possuem o mesmo comportamento e aceitam os mesmos parâmetros.

### Forma de uso

No Windows:

```sh
project <parâmetro>
```

No Linux:

```sh
./project.sh <parâmetro>
```

Se o script não puder ser executado no Linux, conceda permissão de execução com:

```sh
chmod +x project.sh
```

e tente novamente.

Nos exemplos a seguir, **será utilizado o padrão do Windows**. Os parâmetros são idênticos ao utilizar `project.sh` no Linux.

### Compilação

Antes de executar os experimentos, é necessário compilar os programas:

```sh
project build
```

### Execução dos experimentos

Para executar o experimento, utilize:

```sh
project run
```

Ao final da execução:

* os casos de teste serão gerados no diretório `testcases`
* os resultados serão salvos no diretório `results`, em formato CSV
* cada algoritmo terá seu próprio arquivo de resultados (`results_bmk.csv` e `results_sat.csv`)

### Limpeza

Para remover todos os arquivos gerados pelo projeto (executáveis, casos de teste e resultados), utilize:

```sh
project clear
```

### Extra: geração de gráficos

Para gerar os gráficos, o relatório utiliza arquivos CSV em um formato específico, diferente do gerado diretamente pelo experimento. Por esse motivo, é necessária uma conversão prévia.

O conversor já está incluído no projeto e é compilado automaticamente ao executar `project build`. Com os arquivos de resultados presentes no diretório `results`, execute:

No Windows:

```sh
converter
```

No Linux:

```sh
./converter
```

Isso gerará os arquivos no formato adequado para a construção dos gráficos no relatório (`results_sparse.csv`, `results_medium.csv` e `results_sparse.csv`). No relatório, os arquivos convertidos devem estar na pasta [`resultados`](./relatório/resultados/).

## Componentes de terceiros

Este projeto utiliza os seguintes componentes de terceiros, que estão incluídos no repositório:

* [`jngen`](https://github.com/ifsmirnov/jngen): Biblioteca utilizada para a geração de grafos para os casos de teste. Disponível no arquivo [`jngen.h`](./jngen.h).

* [`SAT-Solver-CDCL`](https://github.com/sukrutrao/SAT-Solver-CDCL): Implementação do algoritmo CDCL utilizada como solucionador SAT nos experimentos. Disponível no diretório [`sat_solver`](./sat_solver/).
