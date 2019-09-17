#include <stdio.h>
#include <stdlib.h>


typedef struct no{
    int digito;
    struct no *prox;
    struct no *ant;    
}*bigInt;


bigInt criaBigInt(char *s){
    
    bigInt prev = NULL, next;
    int num;
    
    while(*s){
        next = (bigInt) malloc (sizeof(bigInt));
        if(!next){
            printf("Falta de Memória");
        }else{
           num = (int)s[0] - 48;
           next -> digito = num;
           next -> prox = NULL;
           next -> ant = prev;
           if(prev){
              prev -> prox = next;
           }
           prev = next;
           s++;           
        }        
    }
           
    return prev;
}



void mostraBigInt(bigInt big){  // MOSTRAR O VALOR DIGITADO PELO USUÁRIO;
    
    while(big -> ant){
       big = big -> ant;
    }
    
    while(big){
        printf("%d" , big -> digito);
        big = big -> prox;
    }
    
}

void mostraResultado(bigInt b){  // MOSTRAR RESULTADO DAS OPERAÇÕES;
    int i = 0;    
    
    while(b){
        if(i == 2){
            printf("%d",b -> digito);
            i = 0;
        }
        else{
           printf("%d",b -> digito);
           i++;
        }
        b = b-> ant;
    }    
}

bigInt soma(bigInt num,bigInt num2){
    
    bigInt resultado,prev = NULL;
    int soma,vaiCima = 0;
  
    while(num || num2){
        resultado = (bigInt) malloc (sizeof(bigInt));
        if(!resultado){
            printf("Falta de Memória");
        }else{
          if(!num){
             soma = num2 -> digito + vaiCima;
             num2 = num2 -> ant;
          }else
          if(!num2){
             soma = num -> digito + vaiCima;
             num = num -> ant;
          }else
          if(num && num2){
             soma = num -> digito + num2 -> digito + vaiCima;
             num = num -> ant;
             num2 = num2 -> ant;
          }          
          if(num || num2){
            vaiCima = soma / 10;
            soma = soma % 10;
          }                    
          
          resultado -> digito = soma;
          resultado -> prox = NULL;
          resultado -> ant = prev;
          if(prev){
              prev -> prox = resultado;
          }
          prev = resultado;          
        }        
    }
    return prev;    
}

bigInt subtrair(bigInt num,bigInt num2){
        
    bigInt resultado,prev = NULL;
    int diferenca,dig1,dig2,vaiCima = 0;
    
    while(num || num2){
        resultado = (bigInt) malloc (sizeof(bigInt));
        if(!resultado){
            printf("Falta de Memória");
        }else{
            if(!num){
                dig1 = 0;
                dig2 = num2 -> digito;
                num2 = num2 -> ant;
            }else if(!num2){
                dig2 = 0;
                dig1 = num -> digito;
                num = num -> ant;
            }else{
                dig1 = num -> digito;
                dig2 = num2 -> digito;
                num2 = num2 -> ant;
                num = num -> ant;
            }
            if(dig1 >= dig2+vaiCima){
                diferenca = dig1 - (dig2+vaiCima);
                vaiCima = 0;
            }
            if((dig2+vaiCima > dig1)&&(num || num2)){
                dig1 += 10;
                diferenca = dig1 - (dig2 + vaiCima);
                vaiCima = 1;
            }
            if((!num && !num2)&&(dig2+vaiCima > dig1)){
                diferenca = (dig2+vaiCima) - dig1;
                diferenca *= -1;
            }
            
            resultado -> digito = diferenca;
            resultado -> prox = NULL;
            resultado -> ant = prev;
            if(prev){
                prev -> prox = resultado;
            }
            prev = resultado;
        }
    }
    return prev;
}

bigInt multiplicar(bigInt num,bigInt num2){
    
    bigInt resultado,prev = NULL,somatorio,somaAnt,fim;
    int produto, vaiCima = 0, i = 0,j;
   
   printf("chegou");
    
   resultado = (bigInt) malloc (sizeof(bigInt)); 
   if(!resultado){
       printf("Falta de Memoria!");
   }
   
   printf("chegou");
   resultado -> digito = 0;
   resultado -> prox = NULL;
   resultado -> ant = NULL;
   
   while(num2){ 
     somaAnt = NULL;
     printf("chegou2");
     for(j = i;j<1;j--){
         somatorio = (bigInt) malloc (sizeof(bigInt));
         if(!somatorio){
             printf("Falta de Memoria!");
         }
         somatorio -> digito = 0;
         somatorio -> prox = NULL;
         somatorio -> ant = somaAnt;
         if(somaAnt){
             somaAnt -> prox = somatorio;
         }
         somaAnt = somatorio;
     }
     i++;
     fim = num;
     while(fim){
         somatorio = (bigInt) malloc (sizeof(bigInt));
         if(!somatorio){
             printf("Falta de Memória!");
         }
         produto = num2 -> digito * fim -> digito + vaiCima;
         vaiCima = produto / 10;
         produto = produto % 10;
         printf(" : %d , %d ",produto,vaiCima);
         somatorio -> digito = produto;
         somatorio -> ant = somaAnt;
         somatorio -> prox = NULL;
         if(somaAnt){
             somaAnt -> prox = somatorio;
         }
         somaAnt = somatorio;
         fim = fim -> ant;
     }
     resultado = soma(resultado,somatorio);
     while(resultado -> prox){
         resultado = resultado -> prox;
     }
   }
   return resultado;
}



int main(int argc, char** argv) {

    
    char str[100] = "25";
    char str2[100] = "12";
    
    bigInt num = criaBigInt(str);
    bigInt num2 = criaBigInt(str2);
    
    mostraBigInt(num);
    printf("\n*\n");
    mostraBigInt(num2);
    
    printf("\n-------------------------------------------------------------------------\n");
    bigInt result = multiplicar(num,num2);
    mostraResultado(result);
    printf("\n");
    
    return (EXIT_SUCCESS);
}


