#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 

#define INF 9999
#define NULO -1
#define MAX 100

int m, n;

FILE *file;

int g[MAX][MAX];

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

                for(int i=0;i<m;i++)
                {
                    fscanf(file, "%d %d %d" , &v1, &v2, &w);
                    g[v1-1][v2-1]=w;
                    g[v2-1][v1-1]=w;
                }                
                break;
		}
	}

    int cont=0;
    int marca[n];
    memset(marca, false, sizeof(marca));

    marca[0] = true;

    while (cont < n-1) {
        int min = INF, s=0, v=0;

        for (int i = 0; i < n; i++) {
            if (marca[i]) {
                for (int j = 0; j < n; j++) {
                    if (!marca[j] && g[i][j]){
                        if (min > g[i][j]) {
                            min = g[i][j];
                            s = i;
                            v = j;
                        }
                    }
                }
            }
        }
        printf("%d -> %d: %d\n", s+1, v+1, g[s][v]);
        marca[v] = true;
        cont++;
    }

    return 0;
}
