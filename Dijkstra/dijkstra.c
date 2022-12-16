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
void dijkstra(int grafo [MAX][MAX], int n, int inicio, int destino , int *custos){
    int i, v, mindist, ant[MAX],visitados[MAX],dist[MAX];
     for (i=0;i<n;i++) {
    if (custos[(inicio-1)*n+i]!=-1) {
      ant[i]=inicio-1; 
      dist[i]=custos[(inicio-1)*n+i];
    }
    else {
      ant[i]=-1;
      dist[i]=INF;
    }
    visitados[i]=0;
  }
  visitados[inicio-1]=1;
  dist[inicio-1]=0;
    do {
         mindist= INF;
    for (i=0;i<n;i++)
      if (!visitados[i])
        if (dist[i]>=0 && dist[i]<mindist) {mindist=dist[i];v=i;}
          if (mindist!=INF && v!=destino-1) {
      visitados[v]=1;
      for (i=0;i<n;i++)
        if (!visitados[i]) {
          if (custos[v*n+i]!=-1 && dist[v]+custos[v*n+i]<dist[i])
            { dist[i]=dist[v]+custos[v*n+i];ant[i]=v; }
        }
    }
  } while (v!=destino-1 && mindist!=INF);
   if (mindist==INF)
    printf("\nNão existe caminho entre %d e %d !!\n",inicio,destino);
  else {
    printf("\nO caminho mínimo entre os vértices %d e %d  é :\n",
           inicio,destino);
    i=destino;
    printf("%d",i);
    i=ant[i-1];
    while (i!=-1) {
      printf("<-%d",i+1);
      i=ant[i];
    }
   
    printf("\nO custo deste caminho é: %d\n",(int) dist[destino-1]);
  }
  
}
 int main(int argc, char *argv[]){
  int v1, v2, w, inicio, destino ;
  int grafo[MAX][MAX];
  int *custos = NULL;

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
                   
                    for (int j=0; j<m; j++ ){
                
                 fscanf(file, "%d %d %d" , &v1, &v2, &w);
	                    grafo[v1-1][v2-1] = w;
	                    grafo[v2-1][v1-1] = w;
                }
           break;
		}
        dijkstra(grafo,n,inicio , destino, custos);
	}
 }
 }
