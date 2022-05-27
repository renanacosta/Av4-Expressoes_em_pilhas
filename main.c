#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "pilha.h"

int main()
{
    char expressao[50];
    printf("=====================================\n");
    printf(" EXPRESSÕES MATEMÁTICAS USANDO PILHAS\n");
    printf("=====================================\n");

    printf("\nOperacoes permitidas: +   -   *   /  ^   (   )   [  ]  {  }  ~\n");
    printf("\nInfo:");
    printf("\nNao use espacos na expressao");
    printf("\nUtilize apenas expressões com digitos");
    printf("Digite a expressao: ");
    scanf("%s", expressao);
    printf("%.2f", calculoPilha(expressao));
}