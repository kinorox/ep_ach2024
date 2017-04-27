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
#include <limits.h>
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
typedef struct {
    int flag; // para uso na busca em largura e profundidade, se necessario
    NO* inicio;
} VERTICE;

typedef struct {
    NO* inicio;
    NO* fim;
} fila;

void entrarFila(fila* f, int ch) {

    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->v = ch;
    novo->prox = null;
    if(f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;

}

VERTICE* criaGrafo(int nVertices, int *aberto) {

    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * (nVertices + 1));

    for(int i = 1; i<= nVertices; i++) {
        g[i].inicio = null;
        g[i].flag = 0;
    }

    return g;

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

int getMinVertex(int distances[], int visited[], int vertices){
	int min = INT_MAX, index = -1, i;

	for (i = 1; i <= vertices; ++i) {
		if (visited[i] == 0 && min > distances[i]) {
			min = distances[i];
			index = i;
		}
	}

	return index;
}

void inserirAresta(VERTICE* g, int i, int j, int peso) {

    printf("inserindo nova aresta\n");
    printf("origem: %d\n", i);
    printf("destino: %d\n", j);
    printf("peso: %d\n", peso);

    NO *novo = (NO*) malloc(sizeof(NO));

    novo->v = j;
    novo->prox = g[i].inicio;
    novo->peso = peso;
    g[i].inicio = novo;

}

int* createAndInitializeArray(int nVertices) {

    int* dist = (int*) malloc(nVertices * sizeof(int));
    for(int j = 0; j<nVertices; j++) {
        dist[j] = INT_MAX;
    }

    return dist;

}

//TODO falta fazer o disjktra retornar um NO* com o caminho percorrido até chegar no destino
int dijkstra(VERTICE* g, int startVertex, int fim, int vertices, int distances[], NO* caminho, int* aberto)
{
    int i, visited[vertices + 1];

    // Initially no routes to vertices are know, so all are infinity
    for (i = 1; i <= vertices; ++i) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    caminho = (NO*) malloc(sizeof(NO));

    // Setting distance to source to zero
    distances[startVertex] = 0;

    for (i = 1; i <= vertices; ++i) {     // Untill there are vertices to be processed

        int minVertex = getMinVertex(distances, visited, vertices);	// Greedily process the nearest vertex

        printf("minVertex: %d \n", minVertex);

		NO* trav = g[minVertex].inicio;    // Checking all the vertices adjacent to 'min'

		visited[minVertex] = 1;

        while (trav != NULL) {
        	int u = minVertex;
        	int v = trav->v;
        	int w = trav->peso;

            printf("u: %d \n", u);
            printf("v: %d \n", v);
            printf("w: %d \n", w);

            if (distances[u] != INT_MAX && distances[v] > distances[u] + w) {

                if(!aberto[u]) {
                    return 1;
                }

                printf("Nova rota mais curta por um caminho aberto....");
                distances[v] = distances[u] + w;

                if(v == fim)
                    return 0;
            }

            trav = trav->prox;
        }
    }

    return 0;
}

void PrintCaminho(NO* caminho){

    printf("printando caminho ... \n");

    while(caminho != NULL){
        printf("%d \n", caminho->v);
    }

}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
    NO* resp;

	VERTICE* g = criaGrafo(N, aberto);

    for(int i=0; i<A; i = i+3)
        inserirAresta(g, ijpeso[i], ijpeso[i + 1], ijpeso[i + 2]);

    int distances[N + 1];

    //percorre o primeiro dijsktra até chegar na sala final ou até encontrar uma sala fechada
    int passouPorSalaFechada = dijkstra(g, inicio, fim, N, distances, resp, aberto);

    if(passouPorSalaFechada){ //passou por uma sala fechada no menor caminho encontrado

        NO* caminhoAteChave;

        dijkstra(g, inicio, chave, N, distances, caminhoAteChave, aberto); // calcula o menor caminho até a sala da chave

        dijkstra(g, chave, fim, N, distances, resp, aberto); // calcula o menor caminho da sala da chave até a sala destino

        //TODO
        //computar os dois caminhos e retornar como resposta...

    }

	return resp;
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

    int A = 9;
	int N=3; // grafo de 3 vértices 1..3
	int aberto[] = {0,0,0}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,10};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = null;
	teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);
	return 1;

}
// por favor nao inclua nenhum código abaixo da função main()
