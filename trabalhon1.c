#include <stdio.h>   
#include <stdlib.h>  
#include <ctype.h>
#include <windows.h>

// Codigo feito por Bernardo Menna, Algoritmos 2.

// O codigo foi feito para ser executado em Windows pois utiliza a biblioteca windows.h para utilizar os comandos "Beep" e "Sleep"

// Por conta do uso das cores, é recomendado usar terminais modernos (Windows Terminal, PowerShell, VS Code), terminais muito antigos podem não executar de maneira correta

#define N 10

#define E3  164 // Essa e uma lista de variaveis globais com a frequencia aproximada das notas musicas(Do, Re, Mi, etc)
#define C4  262 // A lista foi gerada com auxilio de IA junto com uma lista das frequencias do site https://producelikeapro.com/blog/note-frequency-chart/
#define D4  294
#define E4  330
#define F4  349
#define G4  392
#define A4  440
#define B4  494
#define C5  523

// Lista com defines para chamar instruções ANSI para o terminal (Gerada com auxilio de IA)

// \033 Inicia um comando | [ Inicia um parametro | 31 (e outros) são os codigos das cores | "m" aplica a alteração

#define VERMELHO    "\033[31m" 
#define AMARELO "\033[33m"
#define VERDE   "\033[32m"
#define AZUL    "\033[34m"
#define RESET "\033[0m"
#define CIANO       "\033[36m"

void musicaDoJogo(int nota, int duracao){ 

    // Funcao para chamar a nota junto com a duracao, pois facilita a nao precisar escrever a frequencia varias vezes.
    

    Beep(nota, duracao);
}

void mostrarLabirinto(int labirinto[N][N], int x, int y){

    for (int i = 0; i < N; i ++){
            for (int j = 0; j < N; j++){
                
                if (i == x && j == y){ // A posicao do jogador e definida por X e Y, Ex na inicializacao: labirinto[i][j] = labirinto[0][0] - posicao do jogador
                    printf(VERDE "@ " RESET); // @ Representa o jogador
                }
                else if (labirinto[i][j] == 1){
                    printf(AZUL "X " RESET); // X representa as paredes do labirinto
                }
                else if (labirinto[i][j] == -1){
                    printf(AMARELO "& " RESET); // & Representa o final
                }
                else if (labirinto[i][j] == 2){
                    printf(VERMELHO "$ " RESET);                   // $ Representa a armadilha.
                }
                else {
                    printf(CIANO ". " RESET);
                }

            }
            printf("\n");
        }
}

void validarMovimento(int novox, int novoy, int labirinto[N][N], int *x, int *y, int *contador, int *pontos){

    /*
        Esse trecho usa ponteiros porque, sem eles, mostrarLabirinto vai receber APENAS o X e o Y declarados no Main (0 e 0) e só vão ser alterados dentro dessa função
        Com ponteiros, eles são alterados de maneira com que altere diretamente o valor no endereço de x e y

        Resumidamente, sem ponteiros o labirinto nunca vai atualizar a posicao do jogador
    
    
    */


        if (novox >= 0 && novoy >= 0 && novox < N && novoy < N && labirinto[novox][novoy] == 2){
            printf("\nVoce caiu em uma armadilha! Voce voltou ao inicio do jogo.");
            Beep(300, 500);

            novox = 0;
            novoy = 0;
            *x = novox;
            *y = novoy;
        
            Sleep(1300); // Sleep é utilizado para o jogador ter tempo de ler a mensagem

        }

    
        else if (novox >= 0 && novoy >= 0 && novox < N && novoy < N && labirinto[novox][novoy] != 1){ 
            
                *x = novox; // Altera o valor de x e y armazenado diretamente no seu endereco
                *y = novoy;
                (*contador)++; // como contador vai ser acessado na main caso o jogador ganhe, ele precisa ser alterado por ponteiros tambem
                Beep(700, 500);
            
            
            
        } 
        
        else {
            printf("\nMovimento invalido!\n");
            *pontos = *pontos - 5; // Mesma coisa vale para os pontos que vao ser mostrados ao finalizar o labirinto
            
            printf("%d, %d", novox, novoy);
            Beep(500, 500);
            Sleep(200);
        }
      
}

int main()
{
    int x = 0; 
    int y = 0;

    int novox = 0;
    int novoy = 0;

    char escolha;

    int contador = 0;
    int pontos = 100;

    int labirinto[N][N] = 
    {
    {0, 0, 1, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, -1},
    {0, 2, 1, 0, 1, 1, 1, 1, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 2, 0, 0, 1, 0, 0}
    };
    int p;

    

    while (1)
    {
        
        system("clear || cls"); // Comando para limpar a tela (Windows)

        printf("\nJogo do labirinto\n");
        printf("O seu objetivo e chegar na saida (&).\nAnde usando W (cima) S (Baixo). A (Esquerda), D (Direita)\n\n");

        mostrarLabirinto(labirinto, x , y); 

        /*
            @ = Jogador
            X = Parede
            & = Final
            $ = Armadilha
        
        
        */ 

        
        printf("\nCoordenada atual:\nX: %d\nY: %d", x, y);
        printf("\nDigite seu movimento: ");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);

        novox = x;
        novoy = y; // Se o movimento for invalido, quando o codigo sair da funcao validarMovimento() os valores de novoy e novox nao vao ser alterados para a proxima vez que a funcao for chamada

        if (escolha == 'W'){ // "" É para string e '' é para char.
            novox--;
        } else if (escolha == 'A'){
            novoy--;
        } else if (escolha == 'S'){
            novox++;
        } else if (escolha == 'D'){
            novoy++;
        }
        
        if (labirinto[novox][novoy] == -1){

            if (contador <= 20){ // Bonus por movimento (18 e o minimo para terminar)
                pontos = pontos + 30;
            } else if (contador <= 25){
                pontos = pontos + 20;
            }

            printf("Voce chegou ao final! Parabens.\nVoce usou %d movimentos e fez %d pontos", contador, pontos);

            // Melodia da musica "Parabens pra Voce" criada baseada em um video ensinando a toca-la no piano.

            musicaDoJogo(C4, 500);
            musicaDoJogo(C4, 350);
            musicaDoJogo(D4, 500);
            musicaDoJogo(C4, 500);
            musicaDoJogo(F4, 500);
            musicaDoJogo(E4, 700);

            musicaDoJogo(C4, 500);
            musicaDoJogo(C4, 350);
            musicaDoJogo(D4, 500);
            musicaDoJogo(C4, 500);
            musicaDoJogo(G4, 500);
            musicaDoJogo(F4, 700);
            break;
        }

        validarMovimento(novox, novoy, labirinto, &x, &y, &contador, &pontos); // E passado para a funcao o ENDERECO das variaveis x, y, contador, pontos, para que elas sejam modificadas pelos ponteiros por referencia.


        
    }
    









}
