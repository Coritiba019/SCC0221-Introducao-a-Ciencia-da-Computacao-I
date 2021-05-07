/*
Trabalho 1 – Memorizando Sequências
Autor: Fabio Dias da Cunha
Número USP: 11320874
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funções utilizadas no programa
void sleep(time_t delay);
void limpa_linha(void);

int main()
{

    int seed, numseq, qtd, i, j, k, l, seq[9], input[9], try, control, tentativas, acertos, pts=0, ptsr, p, pmax, wrong, mp, z=0, x=0;
    char nivel;

    tentativas = 3;//Variavel para controlar as tentativas
    control = 1;//Variavel para controlar a geração de novas sequencias
    acertos = 0;//número de acertos de sequencias do usuario
    p = 0;//numero de digitos que o usuario acertou
    mp = 0;//Variavel para controlar a repetição de sequências para calcular a pontuação

    //leitura da semente e nivel, para alimentar a srand
    scanf("%d %c", &seed, &nivel);
    srand(seed);

    //definicao de parametros, de acordo com o nivel
    if(nivel=='F')
    {
        numseq = 5;
        qtd = 3;
        ptsr = 50;
    }
    else if(nivel=='I')
    {
        numseq = 7;
        qtd = 4;
        ptsr = 70;
    }
    else if(nivel=='A')
    {
        numseq = 9;
        qtd = 5;
        ptsr = 90;
    }

    i = 1;//Variavel para controlar o numero da sequencia
    pmax = ptsr;//Variavel que assume o valor maximo de cada sequencia
    
    if (nivel=='F' || nivel=='I' || nivel=='A')
    {
    
        while(tentativas>0 && acertos!=qtd)
        { 
            try = 0;//numero de acertos em cada sequencia
            p = 0;//pontos de cada rodada
            wrong = 0;//pontuação baseada nos erros em cada rodada

            if(i>x)
            {
                z = 0;
            }
       
            if(control==1)
            {
                printf("Sequencia #%d:\n", i);
            
                for(j=0;j<numseq;j++)
                {
                    seq[j] = rand()%10;//geracao de numeros

                    if(j==numseq-1)
                    {
                        printf("%d", seq[j]);
                        fflush (stdout);//limpeza do buffer
                    }
                    else 
                    {
                        printf("%d ", seq[j]);
                        fflush (stdout);//limpeza do buffer
                    }
                }
                printf("\n");//apagar o printf ,se for executar o programa com o tempo
                
                //Controle do tempo que a sequencia ficara visivel;
                /*
                if(nivel=='F')
                {
                    sleep(5);
                }
                else if(nivel=='I')
                {
                    sleep(7);
                }   
                else if(nivel=='A')
                {
                    sleep(9);
                }
                */

                //Comando para limpar a tela
                /*
                limpa_linha(); 
                */
        }

        else if(control==0)
        {
            printf("Sequencia #%d:\n", i);
            
            for(j=0;j<numseq;j++)
            {

                if(j==numseq-1)
                {
                    printf("%d", seq[j]);
                    fflush (stdout);//limpeza do buffer
                }
                else 
                {
                    printf("%d ", seq[j]);
                    fflush (stdout);//limpeza do buffer
                }

            }
                //Controle do tempo que a sequencia ficara visivel;
                /*
                if(nivel=='F')
                {
                    sleep(5);
                }
                else if(nivel=='I')
                {
                    sleep(7);
                }   
                else if(nivel=='A')
                {
                    sleep(9);
                }
                */

                //Comando para limpar a tela
                /*
                limpa_linha(); 
                */

            printf("\n");//apagar o printf ,se for executar o programa com o tempo
        }
        
        
        for(k=0;k<numseq;k++)
        {
            scanf("%d", &input[k]);
        }

            for(l=0;l<numseq;l++)
            {
                if(seq[l]==input[l])
                {
                    try += 1;
                    p += 10;
                }
                else 
                {
                    wrong += 10;
                }   

        }

        if(wrong==pmax)
        {
            x = i;
            z = 1;
        }
        
        if(try==numseq)
        {
            printf("Correto!\nTentativas disponiveis: %d\n", tentativas);
            acertos += 1;
            control = 1;
            i += 1;
        }
        else 
        {
            tentativas -= 1;
            printf("Incorreto!\nTentativas disponiveis: %d\n", tentativas);
            control = 0;
            mp += 1;

            ptsr = ptsr - wrong;

        }


        //caso o usuario, acerte todos os numeros
        if(try==numseq)
        {   
            if(mp==0)//se, o usuario acertar todos os numeros na 1° tentiva
            {
                pts = pts + pmax;
            }
            else//se, o usuario acertar todos os numeros apos a 1° tentativa
            {
                pts = pts+0;
            }
            
            printf("Pontuacao: %d\n", pts);

            mp = 0;
            ptsr = pmax;
        }
        //caso o usuario, acerte pelo menos um numero
        else if(z!=1)
        {
            if(mp==1)//se, o usuario errar apenas uma vez
            {
                pts = pts + ptsr;
            }
            else if(mp>1)//se, o usuario errar mais de uma vez
            {
                pts = pts - wrong;
                
            }
           
            if(pts<0)
            {
            pts = 0;
            }


            printf("Pontuacao: %d\n", pts);
        }
        //caso o usuario, erre todos os numeros da sequencia
        else 
        {
            printf("Pontuacao: %d\n", pts);
        }

        
   }

    //saida, de acordo com o desempenho do usuario
    if(nivel=='F' || nivel=='I' || nivel=='A')
    {
        if(acertos==qtd)
        {
        printf("Otima memoria! Parabens!!!\n");
        }
        else
        {
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        }
    }
   
}

    return 0;
}

//funcao para controlar o tempo
void sleep(time_t delay)
{
    time_t timer0, timer1;
    time(&timer0);
    do
    {
    time(&timer1);
    } while ((timer1-timer0)<delay);
    
}

//funcao para limpar a tela
void limpa_linha()
{
     int i;//indice do caracter na linha
     int caracter=50;//indica o maximo de caracter que a linha pode chegar a ter
     printf("\r");//retorna para o inicio da linha, apenas posiciona o cursor ao inicio da linha

     
     //substitui todos os caracteres existentes por espaço em branco
     for(i=0;i<caracter;i++){
        printf(" ");//vai preenchendo a linha com espaços em branco
     }

     printf("\r");//volta ao inicio da linha.

}

  