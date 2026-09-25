#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

Trabalho da N2

Aluno: Bernardo Menna

Algoritmos 1


*/

int main()
{
    
    srand((unsigned)time(NULL)); // gera uma seed aleatoria (para os números não se repetirem)

    
    int produtos = rand () % 200 + 1; // (Gera o número de produtos de forma aleatoria, entre 1 e 200)
    int clientes = rand() % 50 + 1; // (Gera o número de clientes de forma aleatoria, entre 1 e 50)

    int p[200]; // Vetor que define os produtos totais (tamanho máximo 200)
    int c[50]; // Vetor que define os clientes (tamanho máximo 50)
    int soma = 0; // Variavel que guarda a soma de todos os valores dos produtos
    
    
    printf("\nForam gerados:\n\n"); // parte visual que vai ser mostrada ao final do código
    printf("%d produtos\n", produtos);
    printf("%d clientes\n", clientes);

    printf("\n----------------------------\n");
    printf("Cliente  Produto  Valor (R$)\n");
    printf("----------------------------\n");

    for (int j = 0; j < produtos; j++) // For vai definir os valores dos produtos de maneira aleatoria
    {
        int valor = rand() % (100 - 5 + 1) + 5; // Valores variam de 5 a 100 
        p[j] = valor; // Armazena os valores dentro do Vetor "p" (produtos) em ordem
        
             
    }

    for (int i = 0; i < clientes; i++) // For vai definir o produto que cada cliente irá comprar
    {
        int compra = rand() % (produtos); // Randomiza os produtos dentro da variavel "compra"
        c[i] = compra; // Define os produtos para cada cliente dentro do vetor "c"

        soma = soma + p[c[i]]; // Soma todos os valores dos itens comprados (vai ser mostrado ao final do código)

        printf("%-10d %-10d %-10d\n", i + 1, c[i], p[c[i]]); // Mostra os clientes, produtos e valores (-10 usado para alinhar o texto)  e i + 1 usado para começar a partir do 1.

        /*
            Nessa etapa, "i" vai mostrar o indice do cliente, enquanto c[i] vai mostrar o produto comprado
            p[c[i]] acessa os valores de c[i] (No caso, o produto que o cliente comprou) e depois usa esse indice dentro dos vetores de produtos "p". 

            Por exemplo: Cliente 0 comprou Produto 7 = c[0] = p[7] (valor de c[i] se torna indice de p[], no caso p[7])

        */ 

        
    }
    printf("----------------------------\n");
    printf("Total vendido: %d\n", soma); // Mostra a soma final dos valores
    
}

