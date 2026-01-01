@echo off

set CPPVER=c++20 & rem Deve ser maior ou igual à 17

IF "%1"=="build" (
    g++ generate_test_cases.cpp -std=%CPPVER% -o generator.exe
    g++ utils.cpp bmk.cpp -std=%CPPVER% -O2 -o bmk.exe
)

IF "%1"=="run" (
    generator
)

IF "%1"=="clear" (
    rmdir /s /q testcases
    del generator.exe
    del bmk.exe
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