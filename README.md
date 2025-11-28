# 1º Trabalho de Métodos Numéricos I - Raízes de Equação

Implementação do primeiro trabalho da cadeira Métodos Numéricos I da Universidade Federal do Ceará no semestre 2025.2

O  objetivo  desse  trabalho  é  implementar  os  métodos  numéricos  estudados  para  achar  raízes  de  equações. Além disso, pretende-se depois resolver vários problemas com os métodos numéricos a serem implementados

## Equipe

| Discente                               | Matrícula |
| -------------------------------------- | --------- |
| ANA ISABELA SOUSA CARVALHO             | 565979    |
| CARLOS REINALDO CRISOSTOMO FREITAS     | 422163    |
| FLAVIO VINICIUS SILVA                  | 572988    |
| GABRIEL VICTOR MAGALHAES DA SILVA      | 539922    |
| MARCOS ANTONIO ALENCAR DA ROCHA JUNIOR | 496563    |

## Enunciado - Tema 2

As oscilações causadas por ondas sísmicas são regidas pela função `f(d) = a*e^d – 4*d^2`, onde `a` são amplitudes devidas à oscilação encontrada em  cada onda considerada e `d` é o deslocamento  encontrado  em  cada  onda considerada, variando com o valor de a. Caso esse deslocamento passe de 0,7m essa oscilação amplifica, causando sérios danos e um problema gigantesco. O método de Newton modificado é tal que a função de iteração φ(x) é dada por `φ(x) = x – (f(x) / f ’(xo))`, onde xo é uma aproximação inicial e é tal que `f′(x0​) ≠ 0`. Desenvolva um sistema para calcular o valor do deslocamento d, que deve atender a todos requisitos abaixo: 

a) Implementar algoritmo para calcular d pelo método da Newton-Raphson.   
b) Implementar algoritmo para calcular d pelo método de Newton modificado.   
c) Implementar algoritmo para calcular d pelo método da Secante tradicional.   
d) Testar os resultados para d usando como padrão a = 1, d0 = 0,5 e e = 10-4.   
e) Fornecer um quadro resposta, com d calculado para cada método dado.   
f) Fornecer um quadro comparativo, com todos os dados para cada método.   
g) Analisar o efeito da variação do valor de a para cada método considerado.   

**Dados de entrada:** n (número de valores de a), a (para cada n) e e (precisão).   
**Dados de saída:** quadros resposta (com d e erro para cada a e método) e comparativo.  

## Como compilar e rodar

O código acompanha um **Makefile** para automatizar a compilação. A maioria das distrubuições Linux já vêm com o comando `make` pré instalado. Para usuários de Windows será necessário instalar através de algum gerenciador de pacotes como o [Chocolatey](https://chocolatey.org/), pela página oficial do [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm), ou simplesmente compilando manualmente.

* Windows - Manual
    ```bash
    > cd src/
    > mkdir -p bin
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

[...]
