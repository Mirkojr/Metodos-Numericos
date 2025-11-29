# 1º Trabalho de Métodos Numéricos I - Raízes de Equação

Implementação do primeiro trabalho da cadeira Métodos Numéricos I da Universidade Federal do Ceará no semestre 2025.2

O  objetivo  desse  trabalho  é  implementar  os  métodos  numéricos  estudados  para  achar  raízes  de  equações. Além disso, pretende-se depois resolver vários problemas com os métodos numéricos a serem implementados.

## Equipe

| Discente                               | Matrícula |
| -------------------------------------- | --------- |
| ANA ISABELA SOUSA CARVALHO             | 565979    |
| CARLOS REINALDO CRISOSTOMO FREITAS     | 422163    |
| FLAVIO VINICIUS SILVA                  | 572988    |
| GABRIEL VICTOR MAGALHAES DA SILVA      | 539922    |
| MARCOS ANTONIO ALENCAR DA ROCHA JUNIOR | 496563    |

## Enunciado - Tema 2

As oscilações causadas por ondas sísmicas são regidas pela função `f(d) = a*e^d – 4*d^2`, onde `a` são amplitudes devidas à oscilação encontrada em  cada onda considerada e `d` é o deslocamento  encontrado  em  cada  onda considerada, variando com o valor de a. Caso esse deslocamento passe de 0,7m essa oscilação amplifica, causando sérios danos e um problema gigantesco. O método de Newton modificado é tal que a função de iteração φ(x) é dada por `φ(x) = x – (f(x) / f'(xo))`, onde xo é uma aproximação inicial e é tal que `f'(x0​) ≠ 0`. Desenvolva um sistema para calcular o valor do deslocamento d, que deve atender a todos requisitos abaixo: 

a) Implementar algoritmo para calcular d pelo método da Newton-Raphson.   
b) Implementar algoritmo para calcular d pelo método de Newton modificado.   
c) Implementar algoritmo para calcular d pelo método da Secante tradicional.   
d) Testar os resultados para d usando como padrão a = 1, d0 = 0,5 e e = 10^-4.   
e) Fornecer um quadro resposta, com d calculado para cada método dado.   
f) Fornecer um quadro comparativo, com todos os dados para cada método.   
g) Analisar o efeito da variação do valor de a para cada método considerado.   

**Dados de entrada:** n (número de valores de a), a (para cada n) e e (precisão).   
**Dados de saída:** quadros resposta (com d e erro para cada a e método) e comparativo.  

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

#### Bisseção

* Algoritmo
    ```
    Algoritmo: Bisseção 
    Entrada: a, b, ε, maxIter 
    Saída: raiz 
    Fa ← f(a); Fb ← f(b) 
    se Fa * Fb > 0 então  
        escreva "Erro: função não muda de sinal entre a e b"
        sair() 
    fimse 
    intervX ← abs(b-a); k ← 0 
    repita 
        x ← (a+b)/2; Fx ← f(x) 
        escreva k, a, Fa, b, Fb, x, Fx, intervX 
        se intervX ≤ ε ou k ≥ iterMax então 
            interrompa 
        fim se 
        se Fa * Fx > 0 então a ← x; Fa ← Fx 
        senão b ← x; Fb ← Fx 
        intervX ← intervX/2; k ← k+1 
    fim repita 
    raiz ← x 
    fim algoritmo
    ```

* Código
    ```cpp
    double Metodos::bissecao( double a, double b, double epslon, int maxIter){
        double Fa = F(a);
        double Fb = F(b);

        cout << Fa << endl;
        cout << Fb << endl;

        if (Fa * Fb > 0){
            cout << "Erro: A função não troca de sinal entre a e b." << endl;
            return NAN;
        }

        double intervX = abs(b-a);
        int k = 0;
        double x;
        while(true){
            x = (a+b)/2; 
            double Fx = F(x);

            if(intervX <= epslon || k >= maxIter) break;
            if(Fa*Fx > 0){
                a = x;
                Fa = Fx;
            }
            else{
                b = x;
                Fb = Fx;
            }
            intervX = intervX/2;
            k++;
        }   
        return x;
    }
    ```

#### Posição Falsa

* Algoritmo

```
Algoritmo: Posição Falsa 
Entrada: a, b, ε1, ε2, iterMax 
Saída: raiz 
  Fa ← f(a); Fb ← f(b) 
  se Fa * Fb > 0 então  
    escreva "Erro: função não muda de sinal entre a e b"
    sair() 
  fimse 
  intervX ← abs(b-a); 
  se intervX < ε1 então raiz ← escolha(a,b); Fim. 
  se abs(Fa) < ε2 então raiz ← a; Fim. 
  se abs(Fb) < ε2 então raiz ← b; Fim. 
  k ← 0
  repita 
     x ← (aFb - bFa)/(Fb-Fa); Fx ← f(x) 
     escreva k, a, Fa, b, Fb, x, Fx, intervX 
     se abs(f(x)) < ε2 ou k ≥ iterMax então raiz ← x; Fim. 
     se Fa * Fx > 0 então a ← x; Fa ← Fx 
     senão b ← x; Fb ← Fx  
     intervX ← abs(b-a)  
     se intervX ≤ ε1 então 
         raiz ← escolha(a,b); Fim. 
     fim se 
     k ← k+1 
  fim repita 
fim algoritmo
```

* Código

```cpp
double Metodos::posicaoFalsa(double a, double b, double epsilon1, double epsilon2, int maxIter){
    double root;

    double Fa = F(a);
    double Fb = F(b);

    cout << "Fa: " << Fa << endl;
    cout << "Fb: " << Fb << endl;

    if (Fa * Fb > 0){
        cout << "Erro: A função não troca de sinal entre a e b." << endl;
        return NAN;
    }

    double intervX = abs(b-a);
    if(intervX < epsilon1) return choose(a,b);
    if(abs(F(a)) < epsilon2) return a;
    if(abs(F(b)) < epsilon2) return b;
    
    int k = 0;
    double x; double Fx;
    while(true){
        x = (a*F(b) - b*(F(a)))/(F(b)-F(a));
        Fx = F(x);

        if((abs(Fx) < epsilon2) || (k>=maxIter)){
            root = x;
            break;
        }
        if(Fa*Fx > 0){
            a = x;
            Fa = Fx;
        }
        else{
            b = x;
            Fb = Fx;
        }

        intervX = abs(b-a);

        if(intervX <= epsilon1){
            root = choose(a,b);
            break;
        }

        k++;
    }
    
    return root;
}
```

#### Ponto Fixo

* Algoritmo

```
Algoritmo: MPF 
Entrada: x0, ε1, ε2, iterMax 
Saída: raiz 
  se abs(f(x0)) < ε1 então raiz ← x0; Fim. 
  k ← 1 
  repita 
     x1 ← φ(x0) 
     escreva k, x1, x0, x1-x0, f(x1) 
     se abs(f(x1)) < ε1 ou abs(x1-x0) < ε2 ou k ≥ iterMax então 
       raiz ← x1; Fim. 
     fim se 
     x0 ← x1 
     k ← k+1 
  fim repita 
fim algoritmo
```

* Código

```cpp
double Metodos::pontoFixo(double x0, double epsilon1, double epsilon2, int maxIter){

    if (this->phiFunc.empty()) return (cerr << "Erro: É necessário definir uma phi para calcular ponto fixo" << endl, NAN);

    if(abs(F(x0)) < epsilon1) return x0;

    int k = 1;
    while(true){
        double x1 = Phi(x0);
        if(abs(F(x1)) < epsilon1 || abs(x1-x0) < epsilon2 || k >= maxIter) return x1;
        x0 = x1;
        k++;
    }
}
```

#### Newton-Raphson

* Algoritmo
    ```
    Algoritmo: Newton-Raphson 
    Entrada: x0, ε1, ε2, iterMax 
    Saída: raiz 
    se abs(f(x0)) < ε1 então raiz ← x0; Fim. 
    k ← 1 
    repita 
        x1 ← x0 - f(x0)/f'(x0) 
        escreva k, x1, f(x1) 
        se abs(f(x1)) < ε1 ou abs(x1-x0) < ε2 ou k ≥ iterMax então 
        raiz ← x1; Fim. 
        fim se 
        x0 ← x1 
        k ← k+1 
    fim repita 
    fim algoritmo
    ```

* Código

    ```cpp
    Resultado Metodos::newtonRaphson(double x0, double epsilon1, double epsilon2, int maxIter){
        
        if(this->derivate.empty()){
            cerr << "Erro: É necessário definir uma derivada para calcular Newton-Raphson" << endl;
            return {NAN, 0, NAN};
        }

        if(abs(F(x0)) < epsilon1) return {x0, 0, 0.0};

        int k = 0;
        double x1;
        while(true){
            x1 = x0 - F(x0)/D(x0);
            double erro = abs(x1 - x0);
            if(abs(F(x1)) < epsilon1 || erro < epsilon2 || k >= maxIter) return {x1, k, erro};
            x0 = x1;
            k++;
        }
    }
    ```

#### Secante

* Algoritmo
    ```
    Algoritmo: Secante 
    Entrada: x0, x1, ε1, ε2, iterMax 
    Saída: raiz 
    se abs(f(x0)) < ε1 então raiz ← x0; Fim. 
    se abs(f(x1)) < ε1 ou abs(x1-x0) < ε2 então raiz ← x1; Fim. 
    k ← 1 
    repita 
        x2 ← x1 - f(x1)/(f(x1) - f(x0)) * (x1-x0) 
        escreva k, x2, f(x2) 
        se abs(f(x2)) < ε1 ou abs(x2-x1) < ε2 ou k ≥ iterMax então 
        raiz ← x2; Fim. 
        fim se 
        x0 ← x1 
        x1 ← x2 
        k ← k+1 
    fim repita 
    ``` 

* Código
    ```cpp
    Resultado Metodos::secante(double x0, double x1, double epsilon1, double epsilon2, int maxIter){
        if(abs(F(x0)) < epsilon1) return {x0, 0, 0.0};
        if(abs(F(x1)) < epsilon1 || abs(x1-x0) < epsilon2) return {x1, 0, abs(x1-x0)};

        double x2;
        int k = 1;

        while(true){
            x2 = x1 - (F(x1)/(F(x1)-F(x0)) * (x1-x0));
            double erro = abs(x2 - x1);
            if(abs(F(x2)) < epsilon1 || erro < epsilon2 || k >= maxIter){
                return {x2, k, erro};
            }
            x0 = x1;
            x1 = x2;
            k++;
        }
    }
    ```

#### Newton Modificado

* Código
    ```cpp
    Resultado Metodos::newtonRaphsonModificado(double x0, double epsilon1, double epsilon2, int maxIter) {
        
        if (this->derivate.empty()){
            cerr << "Erro: É necessário definir uma derivada para calcular Newton Modificado" << endl;

            return {NAN, 0, NAN};
        }

        double d0 = D(x0);
        if (d0 == 0){
            cerr << "Erro: f'(x0) = 0 em Newton Modificado" << endl;
            return {NAN, 0, NAN};
        }

        if (abs(F(x0)) < epsilon1){
            return {x0, 0, 0.0};
        }

        int k = 1;
        double x1;

        while (true) {

            if (isnan(x0) || isinf(x0) || x0 > 1e6 || x0 < -1e6) {
                cerr << "Divergência numérica detectada." << endl;
                return {NAN, k, NAN};
            }

            x1 = x0 - F(x0) / d0;

            if (isnan(x1) || isinf(x1)) {
                cerr << "Divergência: x1 inválido." << endl;
                return {NAN, k, NAN};
            }

            double erro = abs(x1 - x0);
            if (abs(F(x1)) < epsilon1 || erro < epsilon2 || k >= maxIter)
                return {x1, k, erro};

            x0 = x1;
            k++;
        }
    }
    ```

## Referências e links importantes

1. Slides do Professor Joaquim Bento, disponibilizados no classroom da disciplina
1. Calculadora de Métodos online, [https://solve-it.pages.dev/#/home](https://solve-it.pages.dev/#/home)
1. GCC the gnu compiler, [https://gcc.gnu.org/](https://gcc.gnu.org/)
1. GNU Make, [https://www.gnu.org/software/make/](https://www.gnu.org/software/make/)
1. Git, [https://git-scm.com/](https://git-scm.com/)
1. GitHub, [https://github.com/](https://github.com/)
