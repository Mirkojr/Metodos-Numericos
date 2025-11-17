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

Um jato supersônico, ao vencer a barreira do som, tem o deslocamento de sua extremidade dada pela equação **f(d) = a*d – d*ln(d)**, onde d é o deslocamento medido em cm e a é um parâmetro de ajuste para que se projete um jato com a máxima segurança e eficiência possível. Caso esse deslocamento passe dos 2 cm esse jato irá explodir,  causando  sérios  danos  e  um  prejuízo  gigantesco.  Vários  testes  e  simulações  são feitos  de  modo  a garantir  que  esse  jato  seja  desenvolvido  com  toda  segurança  possível.  Desenvolva  um  sistema  para  calcular esse deslocamento d da extremidade de um jato supersônico desse tipo considerado com requisitos abaixo: 

a) Implementar algoritmo para calcular d pelo método da Bissecção.  
b) Implementar algoritmo para calcular d pelo método da Posição Falsa.  
c) Implementar algoritmo para calcular d pelo método de Newton-Raphson. 
d) Testar os seus resultados usando como padrão a = 1, isolamento = (2, 3) e e = 10-5.  
e) Fornecer um quadro resposta, variando os valores de a para vários jatos. 
f) Fornecer um quadro comparativo, com isolamento, raízes e dados para cada método. 
g) Analisar o efeito da variação do valor de a de cada jato, para cada método dado. 

**Dados de entrada:** n (número de jatos), a (de cada jato) e e (precisão). 
**Dados de saída:** quadros resposta (com d e erro para cada jato e método) e comparativo.  

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
