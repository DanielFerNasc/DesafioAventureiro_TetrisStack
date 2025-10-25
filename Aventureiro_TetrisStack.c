/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Constantes: Tamanho Máximo da Fila/Pilha das Peças */
#define MAX_FILA 5
#define MAX_PILHA 3


/* Estruturas: Definição da Fila e das Peças */
typedef struct{
    char nome[1];
    int id;
} Elemento;

typedef struct{
    Elemento itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct{
    Elemento itens[MAX_PILHA];
    int topo;
} Pilha;


/* Protótipos: Declaração das Funções */
 int FilaCheia(Fila *fila);
 int FilaVazia(Fila *fila);
 int PilhaCheia(Pilha *pilha);
 int PilhaVazia(Pilha *pilha);
void AtualizaFila(Fila *fila, int *numero);
void RemoveFila(Fila *fila, Elemento *elemento);
void VisualizaFila(const Fila *fila);
void InicializarPilha(Pilha *pilha);
void Reservar_Push(Pilha *pilha, Elemento elemento);
void Usar_Pop(Pilha *pilha);
void VisualizaPilha(const Pilha *pilha);
void limparBufferEntrada();


/* Main(): Declaração da Função Principal */
int main(){
    //Declaração das Variáveis
    int opcao;
    int numero = 0;
    Fila fila;  fila.total = 0;
    Pilha pilha;
    Elemento elemento;
        
    //Inicialização da Fila de Elemento
    AtualizaFila(&fila, &numero);
    InicializarPilha(&pilha);

    //Meno do TETRIS STACK
    do{
        printf("======================================\n");
        printf("             TETRIS STACK             \n");
        printf("======================================\n");
        printf("1. Jogar Elemento da Fila\n");
        printf("2. Reservar Elemento na Pilha\n");
        printf("3. Usar Elemento da Pilha\n");
        printf("4. Visualizar Fila e Pilha de Elementos\n");
        printf("0. Sair\n");
        printf("--------------------------------------\n");
        printf("Selecao: ");
        scanf("%d",&opcao);
        limparBufferEntrada();

        // Confições do Menu
        switch (opcao){
            case 1:
                RemoveFila(&fila,&elemento);
                AtualizaFila(&fila, &numero);
                break;
            
            case 2:
                if(PilhaCheia(&pilha) == 0){
                    RemoveFila(&fila,&elemento);
                    AtualizaFila(&fila, &numero);
                    Reservar_Push(&pilha, elemento);
                }
                break;

            case 3:
                if(PilhaVazia(&pilha) == 0){
                    Usar_Pop(&pilha);
                }
                break;

            case 4:
                VisualizaFila(&fila);
                VisualizaPilha(&pilha);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Erro: Digite outro valor.\n");
                break;
        }

    }while(opcao != 0);

    return 0;
}


/* Funções: Detalhamento de Cada Função */
void AtualizaFila(Fila *fila, int *numero){
    //Variável Auxiliar
    int tmp;

    //Start do Número Aleatório
    srand(time(NULL));

    if(fila->total == 0){
        //Inicialização do Vetor    
        fila->fim = (MAX_FILA - 1);
        fila->inicio = 0;
        fila->total = 0;

        //Cria os Primeiros Vetores de Elementos
        for (int i = 0; i < MAX_FILA; i++){
            tmp = (rand() % 5);

            if (tmp == 0){
                strcpy(fila->itens[i].nome,"I");
                fila->itens[i].id = *numero;
                fila->total++;
            }else if (tmp == 1){
                strcpy(fila->itens[i].nome,"O");
                fila->itens[i].id = *numero;
                fila->total++;
            }else if (tmp == 2){
                strcpy(fila->itens[i].nome,"T");
                fila->itens[i].id = *numero;
                fila->total++;
            }else{
                strcpy(fila->itens[i].nome,"L");
                fila->itens[i].id = *numero;
                fila->total++;
            }
            *numero = *numero + 1;
        }
    }else{
        //Atualização da Fila com os Elementos Ausentes
        int idy = MAX_FILA - fila->total;
        for (int i = 0; i < idy; i++){
            
            fila->fim = (fila->fim + 1) % MAX_FILA; //Lógica Circular: Atualiza o Índice do Final da Fila
            tmp = (rand() % 5);

            if (tmp == 0){
                strcpy(fila->itens[fila->fim].nome,"I");
                fila->itens[fila->fim].id = *numero;
                fila->total++;
            }else if (tmp == 1){
                strcpy(fila->itens[fila->fim].nome,"O");
                fila->itens[fila->fim].id = *numero;
                fila->total++;
            }else if (tmp == 2){
                strcpy(fila->itens[fila->fim].nome,"T");
                fila->itens[fila->fim].id = *numero;
                fila->total++;
            }else{
                strcpy(fila->itens[fila->fim].nome,"L");
                fila->itens[fila->fim].id = *numero;
                fila->total++;
            }
            *numero = *numero + 1;
        }
    }
}


void VisualizaFila(const Fila *fila){
    printf("Fila: ");
    for (int i = 0, idx = fila->inicio; i < fila->total; i++, idx = (idx + 1)%MAX_FILA){
        printf("[%s %d]", fila->itens[idx].nome, fila->itens[idx].id);
    }
    printf("\n");
}


void RemoveFila(Fila *fila, Elemento *elemento){
    //Verifica se a Fila está Vazia
    if(FilaVazia(fila)){return;}

    //Remove os Dados no Novo Elemento
    strcpy(elemento->nome,fila->itens[fila->inicio].nome);
    elemento->id = fila->itens[fila->inicio].id;

    printf("Elementos Removidos: [%s %d]\n",elemento->nome,elemento->id);

    //Atualiza o Índice do Início da Fila
    fila->inicio = (fila->inicio + 1) % MAX_FILA; //Lógica Circular
    fila->total--; 
}


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);    
}


int FilaCheia(Fila *fila){
    if (fila->total == MAX_FILA){
        printf("Fila Completa de Elementos!\n");
        return 1;
    }
    return 0;
}


int FilaVazia(Fila *fila){
    if (fila->total == 0){
        printf("Fila Vazia!\n");
        return 1;
    }
    return 0;
}


int PilhaCheia(Pilha *pilha){
    if (pilha->topo == (MAX_PILHA - 1)){
        printf("Pilha Reserva Cheia!\n");
        return 1;
    }
    return 0;
}


int PilhaVazia(Pilha *pilha){
    if (pilha->topo < 0){
        printf("Pilha Reserva Vazia!\n");
        return 1;
    }
    return 0;
}


void InicializarPilha(Pilha *pilha){
    pilha->topo = -1;
}


void Reservar_Push(Pilha *pilha, Elemento elemento){
    
    pilha->topo++;
    pilha->itens[pilha->topo].id = elemento.id;
    strcpy(pilha->itens[pilha->topo].nome, elemento.nome);
}


void Usar_Pop(Pilha *pilha){
    
    printf("Elementos Removidos: [%s %d]\n",pilha->itens[pilha->topo].nome,pilha->itens[pilha->topo].id);
    pilha->topo--;
}


void VisualizaPilha(const Pilha *pilha){
    printf("Pilha (topo -> base):\n");
    for (int i = pilha->topo; i >= 0; i--){
        printf("[%s %d]\n", pilha->itens[i].nome, pilha->itens[i].id);
    }
    printf("\n");
}