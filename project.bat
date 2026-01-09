@echo off

set CPPVER=c++23 & rem Deve ser maior ou igual à 20

IF "%1"=="build" (
    g++ generate_test_cases.cpp -std=%CPPVER% -o generator.exe
    g++ utils.cpp bmk.cpp -std=%CPPVER% -O2 -o bmk.exe
)

IF "%1"=="run" (
    generator

    FOR %%F IN (testcases\*) DO (
        echo %%F -^> BMK
        bmk 1 < %%F
    )
)

IF "%1"=="clear" (
    rmdir /s /q testcases 2>NUL
    del /q results_*.csv 2>NUL
    del generator.exe 2>NUL
    del bmk.exe 2>NUL
)

IF "%1"=="help" (
    echo Gerencia o projeto
    echo.
    echo project build^|run^|clear
    echo.
    echo     build        Compila todos os arquivos
    echo     run          Gera os casos de testes ^(se não existir^) e executa os experimentos
    echo     clear        Apaga todos os arquivos compilados e gerados pelo experimento
)