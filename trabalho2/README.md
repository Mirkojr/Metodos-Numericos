# 2º Trabalho de Métodos Numéricos I - Sistemas de Equações

Implementação do segundo trabalho da cadeira Métodos Numéricos I da Universidade Federal do Ceará no semestre 2025.2

O objetivo desse trabalho é implementar os métodos numéricos estudados para achar sistemas de equações. Além disso, pretende-se depois resolver vários problemas com os métodos numérios a serem implementados.

## Equipe

| Discente                               | Matrícula |
| -------------------------------------- | --------- |
| ANA ISABELA SOUSA CARVALHO             | 565979    |
| CARLOS REINALDO CRISOSTOMO FREITAS     | 422163    |
| FLAVIO VINICIUS SILVA                  | 572988    |
| GABRIEL VICTOR MAGALHAES DA SILVA      | 539922    |
| MARCOS ANTONIO ALENCAR DA ROCHA JUNIOR | 496563    |

## Enunciado - Tema 2

Em ondas sísmicas, seus deslocamentos d1, d2,..., dn encontrados são dados pela solução do sistema de equações lineares Ad = b, onde A é a matriz das propriedades, d é o vetor das incógnitas e b é o vetor dos termos independentes (vetor constante). Caso um desses deslocamentos passe de 0,4 cm, em módulo, podem ocorrer sérios danos e um problema gigantesco. Uma das soluções possíveis para achar o vetor d é através da inversa de A (d = A-¹b). Se A é uma matriz nxn que possui como inversa uma matriz A-¹ então AA-¹ = I, onde I é a matriz Identidade, e uma maneira de se achar A¹ é achar-se as colunas de A-¹ uma por vez, através de A(A)1 = {1 0 ... 0}T, A(A¹)2 = {0 1 ... 0} ... A(A¹) = {00 ... 13T, onde (A¹)1, (A¹)2... (A¹) são as n colunas de A-¹. Desenvolva um sistema para calcular deslocamentos d, dessas partes com os requisitos abaixo:

a) Implementar algoritmo para calcular A¹ e depois {d} pelo método de Gauss-Jacobi.     
b) Implementar algoritmo para calcular A¹ e depois {d} pelo método de Gauss-Seidel.     
c) Calibrar o sistema feito usando como padrão matriz [A] e vetor {b} dados abaixo.     
d) Fornecer um quadro resposta para cada método, variando os valores de [A] e de {b}.       
e) Analisar o que vai acontecer nas ondas sismicas, para esse sistema mencionado abaixo.        

<!-- nao sei latex -->
$$
[A] =
\begin{bmatrix}
5 & 3 & 1 \\
5 & 6 & 1 \\
1 & 6 & 7
\end{bmatrix}
\qquad
\{b\} =
\left\{
\begin{matrix}
1 \\
2 \\
3
\end{matrix}
\right\}
$$

**Dados de entrada:** n (número de deslocamentos), termos de [A]nxn e de {b}nxl es (precisão).
**Dados de saída:** A-¹ e os termos de {d} xl que representam os n deslocamentos d1, d2,..., dn

## Como compilar e executar o projeto

O compilador utilizado é o **g++** (GCC - GNU Compiler Collection). Para instalar o compilador, siga as instruções na página oficial do [GCC](https://gcc.gnu.org/install/).

O código acompanha um **Makefile** para automatizar a compilação. A maioria das distrubuições Linux já vêm com o comando `make` pré instalado. Para usuários de Windows será necessário instalar através de algum gerenciador de pacotes como o [Chocolatey](https://chocolatey.org/), pela página oficial do [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm), ou simplesmente compilando manualmente.

* Windows - Manual
    ```bash
    > cd src/
    > mkdir bin
    > g++ -o bin/main.exe *.cpp
    > ./bin/main.exe
    ```

* Windows - Make
    ```bash
    > cd src/
    > make
    > make run
    ```

* Linux
    ```sh
    $ cd src/
    $ make && make run
    ```

## Documentação

### Métodos implementados

#### Método de Gauss-Jacobi

* Algoritmo 
    ```
    Algoritmo: Gauss_Jacobi
    Entrada: n, A, b, ε, iterMax
    Saída: x, k
        {construção da matriz e do vetor de iterações}
        para i ← 1 até n faça:
            r ← 1/A[i][i]
            para j ← 1 até n faça:
                se i ≠ j então:
                    A[i][j] ← A[i][j] * r
                fim se
            fim para
            b[i] ← b[i] * r
            x[i] ← b[i]
        fim para
        k ← 0
        {iterações de Jacobi}
        repita
            k ← k + 1
            para i ← 1 até n faça:
                soma ← 0
                para j ← 1 até n faça:
                    se i ≠ j então:
                        soma ← soma + A[i][j] * x[j]
                    fim se
                fim para
                v[i] ← b[i] - soma
            fim para
            norma ← calcula_norma(n,x,v)
            escreva k, x, norma
            se norma ≤ ε ou k ≥ iterMax então:
                interrompa
            fim se
        fim repita
    fim algoritmo
    ```

* Algoritmo auxiliar
    ```
    Algoritmo: calcula_norma
    Entrada: n, x, v
    Saída: norma     
        normaNum ← 0
        normaDen ← 0   
        para i ← 1 até n faça:
            t ← abs(v[i] - x[i])
            se t > normaNum então normaNum ← t
            se abs(v[i]) > normaDen então normaDen ← abs(v[i])
            {vetor x é atualizado com o vetor v}
            x[i] ← v[i]  
        fim para
        norma ← normaNum/normaDen
    fim algoritmo
    ```
* Código
    ```cpp
    ```

#### Método de Gauss-Seidel

* Algoritmo
    ```
    Algoritmo: Gauss_Seidel
    Entrada: n, A, b, ε, iterMax
    Saída: x, k
        {construção da matriz e do vetor de iterações}
        para i ← 1 até n faça:
            r ← 1/A[i][i]
            para j ← 1 até n faça:
                se i ≠ j então:
                    A[i][j] ← A[i][j] * r
                fim se
            fim para
            b[i] ← b[i] * r
            x[i] ← b[i]
        fim para
        k ← 0
        {iterações de Gauss-Seidel}
        repita
            k ← k + 1
            para i ← 1 até n faça:
                soma ← 0
                para j ← 1 até n faça:
                    se i ≠ j então:
                        soma ← soma + A[i][j] * x[j]
                    fim se
                fim para
                v[i] ← x[i]; x[i] ← b[i] - soma
            fim para
            norma ← calcula_norma(n,v,x)
            escreva k, x, norma
            se norma ≤ ε ou k ≥ iterMax então:
                interrompa
            fim se
        fim repita
    fim algoritmo
    ```
* Algoritmo Auxiliar
    ```
    Algoritmo: calcula_norma
    Entrada: n, x, v
    Saída: norma
        normaNum ← 0
        normaDen ← 0
        para i ← 1 até n faça:
            t ← abs(v[i] - x[i])
            se t > normaNum então normaNum ← t
            se abs(v[i]) > normaDen então normaDen ← abs(v[i])
            {vetor x é atualizado com o vetor v}
            x[i] ← v[i]
        fim para
        norma ← normaNum/normaDen
    fim algoritmo
    ```

* Código
    ```cpp
    ```

## Referências e links importantes

1. Slides do Professor Joaquim Bento, disponibilizados no classroom da disciplina
1. Calculadora de Métodos online, [https://solve-it.pages.dev/#/home](https://solve-it.pages.dev/#/home)
1. GCC the gnu compiler, [https://gcc.gnu.org/](https://gcc.gnu.org/)
1. GNU Make, [https://www.gnu.org/software/make/](https://www.gnu.org/software/make/)
1. Git, [https://git-scm.com/](https://git-scm.com/)
1. GitHub, [https://github.com/](https://github.com/)

