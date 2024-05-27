<h1 align="center" style="font-weight: bold;">Gerenciador de Estoque</h1>

<h4>Repositório criado referente ao projeto disciplinar da disciplina de Algoritmos e Estruturas de Dados</h4>


<h2 id="plataforma">Plataforma de desenvolvimento</h2>

<p>É desenvolvido completamente na linguageme C . A linguagem C é utilizada para implementar o núcleo do sistema de estoque. A biblioteca Cjson é empregada para a manipulação eficiente de dados JSON no código C, permitindo uma rápida conversão entre dados JSON e estruturas de dados C</p>
 
<h3 id="requisitos">Pré Requisitos</h3>

- [GCC Compiler](https://gcc.gnu.org/)
- [Git](https://git-scm.com/downloads)

<h3>Executando o projeto</h3>

Clone o projeto com:
```
git clone https://github.com/klesleybr/crud_estoqueinC.git
```

<h4>Compilando o projeto</h4>

Navegue até a pasta raiz do projeto e execute:
```
gcc -I./cjson -I./methods -c main.c -c ./cjson/operationHistory.c -c ./methods/functions.c cjson/cJSON-1.7.18/cJSON.c
```
Em seguida:
```
gcc main.o operationHistory.o functions.o cJSON.o -o main
```
Por fim, rode o executável resultante.

<h3>Integrantes</h3>

- [Alexandre Azevedo](https://github.com/Alexandre-Siqueira)  
- [Bruno de Medeiros](https://github.com/Bruno0M)  
- [Eduardo Pimenta](https://github.com/Pyments)  
- [José Kayky](https://github.com/KaykySiq)  
- [José Klesley](https://github.com/klesleybr)  
- [Pablo Henrique](https://github.com/Pablohdantas)  
- [Pedro Henrique](https://github.com/PHCavalcante)  
- [Thiago Ferreira](https://github.com/thiagoffs)    
- [Vinicius Alves](https://github.com/Vinilves)  

