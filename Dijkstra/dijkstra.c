#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INF 9999
#define NULO -1
#define TRUE 1
#define FALSE 0
#define MAX 100

FILE *file;
int n,m;
int grafo[MAX][MAX];

void dijkstra(int grafo [][MAX], int inicio, int destino){
    int mindist, c, custo[MAX][MAX], ant[MAX],visitados[MAX],dist[MAX], prox;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        if (grafo[i][j] == 0)
            custo[i][j] = INF;
        else
            custo[i][j] = grafo[i][j];
    }

    for (int i = 0; i < n; i++) {
        dist[i] = custo[inicio][i];
        ant[i] = inicio;
        visitados[i] = 0;
    }

    dist[inicio] = 0;
    visitados[inicio] = 1;
    c = 1;

    while (c < n - 1) {
        mindist = INF;

        for (int i = 0; i < n; i++)
        
        if (dist[i] < mindist && !visitados[i]) {
            mindist = dist[i];
            prox = i;
        }

        visitados[prox] = 1;
        for (int i = 0; i < n; i++)
        if (!visitados[i]){
            if (mindist + custo[prox][i] < dist[i]) {
                dist[i] = mindist + custo[prox][i];
                ant[i] = prox;
            }
        }
        c++;
    }
    
    printf("A distância mínima de %d para %d é: %d\n", inicio+1, destino+1, dist[destino]);
    
}

int main(int argc, char *argv[]){
    int v1, v2, w, inicio, destino ;

    if (argc == 1){
        printf("\nAdicione um texto de entrada! (ex: -f entrada.txt)\n");
        exit(0);
    }

    int opcao;
    while((opcao = getopt(argc, argv, "help:f:")) != -1)
	{
		switch(opcao)
		{
            case 'h':
                printf("\nUse o parâmetro -f para colocar a entrada. (ex: -f entrada.txt)\n");
                return 0;
            case 'f':
                file = fopen(optarg, "r");
                if(file == NULL){
                    printf("TXT vazio.\n");
                    return 0;
                }

                fscanf(file, "%d %d" , &n, &m);

                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        if(i==j){
                            grafo[i][j]=0;
                        }
                        else{
                            grafo[i][j]=INF;
                        }
                    }
                }
                    
                for (int j=0; j<m; j++ ){
                    fscanf(file, "%d %d %d" , &v1, &v2, &w);
	                grafo[v1-1][v2-1] = w;
	                grafo[v2-1][v1-1] = w;
                }
            break;
	    }
    }

    printf("\nDigite o vértice inicial: ");
    scanf("%d", &inicio);

    printf("\nDigite o vértice final: ");
    scanf("%d", &destino);

    dijkstra(grafo, inicio-1, destino-1);
    return 0;
 }
