@echo off

set CPPVER=c++23 & rem Deve ser maior ou igual à 20

IF "%1"=="build" (
    echo Compilando "generate_test_cases.cpp" -^> "generator.exe"
    g++ generate_test_cases.cpp -std=%CPPVER% -o generator.exe

    echo Compilando "csv_to_latex.cpp" -^> "converter.exe"
    g++ csv_to_latex.cpp -std=%CPPVER% -o converter.exe

    echo Compilando "bmk.cpp" -^> "bmk.exe"
    g++ utils/utils.cpp bmk.cpp -std=%CPPVER% -O2 -o bmk.exe

    echo Compilando "sat.cpp" -^> "sat.exe"
    g++ utils/utils.cpp sat_solver/cdcl.cpp sat.cpp -std=%CPPVER% -O2 -o sat.exe
)

IF "%1"=="run" (
    echo Gerando casos de testes
    generator

    echo Executando experimento

    FOR %%F IN (testcases\*) DO (
        echo %%F -^> BMK
        bmk 1 < %%F
    )

    FOR %%F IN (testcases\*) DO (
        echo %%F -^> SAT
        sat 1 < %%F
    )
)

IF "%1"=="clear" (
    rmdir /s /q testcases 2>NUL
    rmdir /s /q results 2>NUL
    del generator.exe 2>NUL
    del converter.exe 2>NUL
    del bmk.exe 2>NUL
    del sat.exe 2>NUL
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