@echo off

IF "%1"=="build" (
    g++ generate_test_cases.cpp -std=c++20 -o generator.exe
)

IF "%1"=="run" (
    generator
)

IF "%1"=="clear" (
    rmdir /s /q testcases
    del generator.exe
)

IF "%1"=="help" (
    echo Gerencia o projeto
    echo.
    echo project build^|run^|clear
    echo.
    echo     build        Compila todos os arquivos
    echo     run          Gera os casos de testes e executa os experimentos
    echo     clear        Apaga todos os arquivos compilados e gerados pelo experimento
)