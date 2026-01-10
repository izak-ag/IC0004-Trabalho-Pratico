#!/bin/bash

CPPVER="c++23" # Deve ser maior ou igual a 20

case "$1" in
    "build")
        echo "Compilando \"generate_test_cases.cpp\" -> \"generator\""
        g++ generate_test_cases.cpp -std="$CPPVER" -o generator

        echo "Compilando \"csv_to_latex.cpp\" -> \"converter\""
        g++ csv_to_latex.cpp -std="$CPPVER" -o converter

        echo "Compilando \"bmk.cpp\" -> \"bmk\""
        g++ utils/utils.cpp bmk.cpp -std="$CPPVER" -O2 -o bmk

        echo "Compilando \"sat.cpp\" -> \"sat\""
        g++ utils/utils.cpp sat_solver/cdcl.cpp sat.cpp -std="$CPPVER" -O2 -o sat
        ;;

    "run")
        echo "Gerando casos de testes"
        ./generator

        echo "Executando experimento"

        for F in testcases/*; do
            echo "$F -> BMK"
            ./bmk 1 < "$F"
        done

        for F in testcases/*; do
            echo "$F -> SAT"
            ./sat 1 < "$F"
        done

        ;;

    "clear")
        rm -rf testcases
        rm -f results_*.csv
        rm -f generator
        rm -f converter
        rm -f bmk
        rm -f sat
        ;;

    "help")
        echo "Gerencia o projeto"
        echo
        echo "project.sh build|run|clear"
        echo
        echo "    build        Compila todos os arquivos"
        echo "    run          Gera os casos de testes (se não existir) e executa os experimentos"
        echo "    clear        Apaga todos os arquivos compilados e gerados pelo experimento"
        ;;
esac
