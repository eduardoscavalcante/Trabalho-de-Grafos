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
int grafo[MAX][MAX], distancia[MAX][MAX];

void imprimir(int distancia[][MAX]) {
    printf("\nA matriz seguinte mostra a distância mínima entre cada par de vértices,");
    printf("\napós o cálculo de distâncias do algoritmo Floyd Warshall.\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        if (distancia[i][j] == INF)
            printf("%4s", "INF");
        else
            printf("%4d", distancia[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int matriz[][MAX]) {
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        distancia[i][j] = matriz[i][j];

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (distancia[i][k] + distancia[k][j] < distancia[i][j])
                distancia[i][j] = distancia[i][k] + distancia[k][j];
            }
        }
    }
    printf("\n\n");

    imprimir(distancia);
}

int main(int argc, char *argv[])
{
    int v1, v2, w;

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

                for(int i=0;i<m;i++)
                {
                    fscanf(file, "%d %d %d" , &v1, &v2, &w);
                    grafo[v1-1][v2-1]=w;
                }                
                break;
		}
	}
    printf("\nA matriz seguinte mostra a relação de pesos iniciais entre cada par de vértices.\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo[i][j] == INF){
                printf("%4s", "INF");
            }
            else{
                printf("%4d", grafo[i][j]);
            }
        }

        printf("\n");
    }
 
    floydWarshall(grafo);
    return 0;
}
