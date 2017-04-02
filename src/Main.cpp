//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Gabriel Bombardi E Marcos Pinheiro Moura
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#define null 0

// ######### ESCREVA O NROUSP DO PRIMEIRO INTEGRANTE AQUI
char* nroUSP1() {
    return("7972237");
}

// ######### ESCREVA O NROUSP DO SEGUNDO INTEGRANTE AQUI (OU DEIXE COM ZERO)
char* nroUSP2() {
    return("7971841");
}

// elemento das listas de adjacência e de resposta
typedef struct estr {
    int v; // elemento
    int peso; // custo (não precisa ser usado na resposta)
    struct estr *prox;
} NO;

// vertices do grafo (salas) - use este tipo ao criar o grafo
typedef struct
{
    int flag; // para uso na busca em largura e profundidade, se necessario
    bool aberto; // vale true se a sala em questao esta aberta
    NO* inicio;
} VERTICE;

typedef struct {
    NO* inicio;
    NO* fim;
} fila;

void entrarFila(fila* f, int ch) {

    NO * novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->v = ch;
    novo->prox = null;
    if(f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;

}

int sairFila(fila* f) {

    NO * aux;
    int ch;
    if(!f->inicio) return(-1);
    ch = f->inicio->v;
    aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    if (!f->inicio) f->fim = null;

    return(ch);

}

void inicializar(fila* f) {

    f->inicio = null;
    f->fim = null;

}

void zerarFlags(VERTICE* g, int nVertices) {

    for(int i=0; i<nVertices; i++)
        g[i].flag = 0;

}

void largura(VERTICE* g, int i) {

    zerarFlags(g);

    fila f;
    inicializar(&f);

    g[i].flag = 1;
    entrarFila(&f, i);

    while(f.inicio) {

        i = sairFila(&f);
        NO * p = g[i].inicio;
        while (p){

            if (g[p->v].flag == 0) {
                entrarFila (&f, p->v);
                g[p->v].flag = 1;
            }

            p = p->prox;

        }

        g[i].flag = 2;
    }

}

bool arestaExiste (VERTICE* g, int i, int j) {
    NO *p = g[i].inicio;

    while(p) {
        if(p->v ==j) return true;

        p = p->prox;
    }

    return false;
}

void inserirAresta(VERTICE* g, int i, int j, int peso) {

    printf("inserindo nova aresta\n");
    printf("origem: %d\n", i);
    printf("destino: %d\n", j);
    printf("peso: %d\n", peso);

    //if(arestaExiste(g,i,j)) return;

    NO *novo = (NO*) malloc(sizeof(NO));

    novo->v = j;
    novo->prox = g[i].inicio;
    novo->peso = peso;
    g[i].inicio = novo;

}

VERTICE* criaGrafo(int nVertices, int *aberto) {

    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * (nVertices + 1));

    for(int i = 1; i<= nVertices; i++) {
        g[i].inicio = null;
        g[i].aberto = aberto[i];
    }

    return g;

}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	VERTICE* g = criaGrafo(N, aberto);

	int i = 0;
	while(ijpeso[i]) {

        inserirAresta(g, ijpeso[i], ijpeso[i + 1], ijpeso[i + 2]);

        i = i + 3;
	}

	return resp;
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	int N=3; // grafo de 3 vértices 1..3
	int aberto[] = {1,1,1}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,10};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = null;
	teste = caminho(N, ijpeso, aberto, inicio, fim, chave);
	return 1;

}
// por favor nao inclua nenhum código abaixo da função main()
