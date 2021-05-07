/*
Autor : Fabio Dias da Cunha
Número USP : 11320874
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct cl//struct das coordenadas
{
    int x;
    int y;
    int c;
}coordenadas;

//Protótipo das funções

int **Alocar_matriz(int m, int n);
int **Liberar_matriz(int m, int n, int **v);
coordenadas *Alocar_Struct(int n);
coordenadas *Liberar_Struct(coordenadas *v);
char *Alocar_String(void);
char *Liberar_String(char *v);
void busca(int **MatN, int **MatR, int x, int y, int c, int N, int M, int q, int *numM, double *soma);

int main(void)
{
    FILE *arq;

    coordenadas *cord;
    int p1=0, i=0,j=0,l=0,q=0, a=0, N=0, M=0, I=0, K=0, x=0,y=0,c=0,**MatN, **MatR, *numM=&p1;
    double p2=0, *soma=&p2;
    char *s, *nomearq;

    //Alocação dos parâmetros da função
    numM = (int *) calloc(3, sizeof(int)); 
    soma = (double *) calloc(3, sizeof(double));

    //Verificando a alocação dos ponteiros acima
    if (numM==NULL || soma==NULL) 
    {
        printf ("Memória Cheia\n");
    }
    
    s = Alocar_String();
    nomearq = Alocar_String();

    scanf("%s", nomearq);
    arq = fopen(nomearq, "r");//Abertura do arquivo
    fscanf(arq, "%s %d %d %d", s, &N, &M, &I);//Leitura de dados do arquivo
    
    MatN = Alocar_matriz(M, N);//Alocação das matrizes
    MatR = Alocar_matriz(M, N);

    //Leitura da Matriz
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            fscanf(arq, "%d", &MatN[i][j]);
        }
    }
    
    scanf("%d", &K);//Leitura do número de buscas

    cord = Alocar_Struct(K);//Alocação da struct
    
    //Leitura das coordenadas
    for(l=0;l<K;l++)
    {
        scanf("%d %d %d", &cord[l].x, &cord[l].y, &cord[l].c);
    }

    //Buscando as regiões segmentadas
    for(q=0;q<K;q++)
    {
        x = cord[q].x;
        y = cord[q].y;
        c = cord[q].c;
        numM[0]=0;
        soma[0]=0;
        busca(MatN, MatR, x, y, c, N, M, q, numM, soma);
    }
    
    //Impressão das bordas da imagem
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            a = 0;

            if(i-1>=0)//cima
            {
                if(MatR[i-1][j]!=MatR[i][j])
                {
                    a = 1;
                }
            }
            if(j+1<=N-1)//direita
            {
                if(MatR[i][j+1]!=MatR[i][j])
                {
                    a = 1;
                }
            }
            if(i+1<=M-1)//baixo
            {
                if(MatR[i+1][j]!=MatR[i][j])
                {
                    a = 1;
                }
            }
            if(j-1>=0)//esquerda
            {
                if(MatR[i][j-1]!=MatR[i][j])
                {
                    a = 1;
                }
            }

            if(a==1)
            {
                printf("(%d, %d)\n", i, j);
            }

        }
    }

    //Liberação da memória alocada
    Liberar_matriz(M, N, MatN);
    Liberar_matriz(M, N, MatR);
    Liberar_Struct(cord);
    Liberar_String(s);
    Liberar_String(nomearq);
    free(numM);
    free(soma);
    fclose(arq);

    return 0;
}

//Função para buscar as regiões segmentadas

void busca(int **MatN, int **MatR, int x, int y, int c, int N, int M, int q, int *numM, double *soma)
{
    int i=q+1;
    double result=0, media=0;
    
    if(MatR[x][y]==0)
    {
        if(numM[0]==0)
        {
            soma[0]=0;
            MatR[x][y]=i;
            soma[0] += MatN[x][y];
            numM[0] += 1;
        }
        else if(numM[0]>0)
        {
            media = soma[0]/numM[0];
            result = MatN[x][y]-media;

            if(result<0)
            {
                result *= (-1);
            }

            if(result<=c)
            {
                MatR[x][y]=i;
                soma[0] += MatN[x][y];
                numM[0] += 1; 
            }
            else
            {
                return;
            }
        }
        

        if(x-1>=0)//cima
        {
            if(MatR[x-1][y]==0 && MatR[x][y]!=0)
            {
                busca(MatN, MatR, x-1, y, c, N, M, q, numM, soma);
            }
        }

        if(y+1<=N-1)//direita
        {
            if(MatR[x][y+1]==0 && MatR[x][y]!=0)
            {
                busca(MatN, MatR, x, y+1, c, N, M, q, numM, soma);
            }
        }

        if(x+1<=M-1)//baixo
        {
            if(MatR[x+1][y]==0 && MatR[x][y]!=0)
            {
                busca(MatN, MatR, x+1, y, c, N, M, q, numM, soma);
            }
        }

        if(y-1>=0)//esquerda
        {
            if(MatR[x][y-1]==0 && MatR[x][y]!=0)
            {
                busca(MatN, MatR, x, y-1, c, N, M, q, numM, soma);
            }
        }
    }

    else 
    {
        return;
    }
        
}

//Funções auxiliares para alocar memória

int **Alocar_matriz(int m, int n)//Função para alocar a matriz
{
    int **v;  
    int i;    
    if(m<1 || n<1) 
    {  
        printf("Parâmetro inválido\n");
        return(NULL);
    }

    v = (int **) calloc(m, sizeof(int *));
    if (v==NULL) 
    {
        printf ("Memória Cheia\n");
        return (NULL);
    }
  
    for(i=0;i<m;i++)   
    {
        v[i] = (int*) calloc(n, sizeof(int));	
        if (v[i] == NULL) 
        {
            printf ("Memória Cheia\n");
            return (NULL);
        }
    }
    return (v); 
}

int **Liberar_matriz(int m, int n, int **v)//Função para liberar a matriz
{
    int  i;  
    if(v==NULL)
    {
        return (NULL);
    } 
  
    if(m<1 || n<1) 
    {  
        printf ("Parâmetro inválido\n");
        return (v);
    }
    for(i=0;i<m;i++)
    {
        free (v[i]); 
    } 
    free (v);      
    return (NULL); 
}

coordenadas *Alocar_Struct(int n)//Função para alocar a struct
{
    coordenadas *v;        
    if(n<1) 
    {  
        printf ("Parâmetro invalido\n");
        return (NULL);
    }
  
    v = (coordenadas *) calloc(n, sizeof(coordenadas));
    if (v==NULL) 
    {
        printf ("Memória Cheia\n");
        return (NULL);
    }
    return (v);
}

coordenadas *Liberar_Struct(coordenadas *v)//Função para liberar a struct
{
    if(v==NULL)
    {
        return (NULL);
    }
    free(v);        
    return (NULL);  
}

char *Alocar_String(void)//Função para alocar a string(nome do arquivo)
{
    char *v;        
    
    v = (char *) calloc(15, sizeof(char));
    if (v==NULL) 
    {
        printf ("Memória Cheia\n");
        return (NULL);
    }
    return (v);
}

char *Liberar_String(char *v)//Função para liberar a string
{
    if(v==NULL)
    {
        return (NULL);
    }
    free(v);        
    return (NULL);  
}

