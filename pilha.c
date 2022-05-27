#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "pilha.h"


PilhaOperandos* retornaUltimo(PilhaOperandos* p){
  PilhaOperandos* aux=p;
  while(aux->prox != NULL){
    aux=aux->prox;
  }
  return aux;
}

PilhaOperadores* retornaUltimoOperadores(PilhaOperadores* p){
  PilhaOperadores* aux=p;
  while(aux->prox!=NULL){
    aux=aux->prox;
  }
  return aux;
}

PilhaOperandos* retornaProximoTopoOperandos(PilhaOperandos* p){
  PilhaOperandos* aux=p;
  PilhaOperandos* anterior=aux;
  while(aux->prox!=NULL){
    anterior=aux;
    aux=aux->prox;
  }
  return anterior;
}

PilhaOperadores* retornaProximoTopoOperadores(PilhaOperadores* p){
  PilhaOperadores* aux=p;
  PilhaOperadores* anterior=aux;
  while(aux->prox!=NULL){
    anterior=aux;
    aux=aux->prox;
  }
  return anterior;
}

void pushNumeroPilha(PilhaOperandos** p, double numero){
  PilhaOperandos* novoNo = (PilhaOperandos*) malloc(sizeof(PilhaOperandos));
  if((*p)==NULL){
    novoNo->info=numero;
    novoNo->prox=NULL;
    (*p)=novoNo;
  }else{
    PilhaOperandos* ultimo = retornaUltimo(*p);
    novoNo->info=numero;
    novoNo->prox=NULL;
    ultimo->prox=novoNo;
  }
}

void pushCaracterPilha(PilhaOperadores** p, char caracter){
  PilhaOperadores* novoNo = (PilhaOperadores*) malloc(sizeof(PilhaOperadores));
  if((*p)==NULL){
    novoNo->info=caracter;
    novoNo->prox=NULL;
    (*p)=novoNo;
  }else{
    PilhaOperadores* ultimo = retornaUltimoOperadores(*p);
    novoNo->info=caracter;
    novoNo->prox=NULL;
    ultimo->prox=novoNo;
  }
}


double popNumeroPilha(PilhaOperandos** p){
  if((*p) != NULL){
    PilhaOperandos* proximoTopo= retornaProximoTopoOperandos(*p);
    if(proximoTopo==(*p) && proximoTopo->prox==NULL) {
      PilhaOperandos* removido = proximoTopo;
      (*p)=NULL;
      return removido->info;
    }else{
      PilhaOperandos* removido = proximoTopo->prox;
      proximoTopo->prox=NULL;
      return removido->info;
      }
  }
  return -1;
}

char popCaracterPilha(PilhaOperadores** p){
  if((*p) != NULL){
    PilhaOperadores* proximoTopo= retornaProximoTopoOperadores(*p);
    if(proximoTopo==(*p) && proximoTopo->prox==NULL){
      PilhaOperadores* removido = proximoTopo;
      (*p)=NULL;
      return removido->info;
    }else{
      PilhaOperadores* removido = proximoTopo->prox;
      proximoTopo->prox=NULL;
      return removido->info;
      }
  }
  return '1';
}


double operacaoPilha(PilhaOperandos** operandos, PilhaOperadores** operadores)
{
    double num1 = popNumeroPilha(operandos);
    double num2 =0;
    char operador = popCaracterPilha(operadores);
    if(operador!='~'){
      num2 = popNumeroPilha(operandos);
      
    }
    
    switch (operador)
    {
    case '+':
        printf("%f %c %f\n",num1,operador,num2);
        return num1 + num2;
    case '-':
        printf("%f %c %f\n",num1,operador,num2);
        return num1 - num2;
    case '*':
        printf("%f %c %f\n",num1,operador,num2);
        return num1 * num2;
    case '/':
        if (num1 == 0)
        {
            exit(0);
        }
        else
        {
            printf("%f %c %f\n",num2,operador,num1);
            return num2 / num1;
        }
      case '^':
        printf("%f %c %f\n",num2,operador,num1);
        return pow(num2,num1);
      case '~':
        printf("%f %c\n",num1,operador);
        return sqrt(num1);
    }
    return 0;
}


int isOperador(char caracter)
{
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter=='~' || caracter =='^');
}


int precedencia(char operador)
{
    switch (operador)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
      return 3;
      case '~':
      return 3;
    }
    return -1;
}

int precedenciaEspeciais(char operador)
{
    switch (operador)
    {
    case ')':
        return 1;
    case ']':
        return 2;
    case '}':
        return 3;
    default:
      return -1;
   }
}

void printaPilha(PilhaOperandos* pO,PilhaOperadores* pOp){
  PilhaOperadores* auxpOp=pOp;
  PilhaOperandos* auxpO=pO;
  while(auxpOp!=NULL){
    printf("%c, ",auxpOp->info);
    auxpOp=auxpOp->prox;
  }
  printf("\n");
  while(auxpO!=NULL){
     printf("%f, ",auxpO->info);
    auxpO=auxpO->prox;
  }
  printf("\n");
}

double calculoPilha(char expressao[]){
  double resultado;
  PilhaOperandos *operandos=NULL;
  PilhaOperadores *operadores=NULL;
  
  int i;
  int eNum = 0;
  int eOperador=0;
  for(i=0; expressao[i]!= '\0'; i++){
    
    char caracter = expressao[i];
    printf("\nCaracter da vez %c\n",caracter);
    
    if(isdigit(caracter)){
      int num=0;
      num = num * 10 + (caracter - '0');
      pushNumeroPilha(&operandos,num);
      printaPilha(operandos,operadores);
      if(eOperador>1){
         pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
         printaPilha(operandos,operadores);
      }
      eNum=1;
    }else if(caracter=='(' || caracter=='[' || caracter == '{'){
      pushCaracterPilha(&operadores,caracter);
      printaPilha(operandos,operadores);
      eNum=0;
      eOperador=0;
    }else if((caracter == ')' || caracter==']' || caracter == '}') && eNum!=0){
      //pushCaracterPilha(&operadores,caracter);
      switch(precedenciaEspeciais(caracter)){
        case 1:
          while(retornaUltimoOperadores(operadores)->info != '('){
             pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
             
          }
        break;
        case 2:
          while(retornaUltimoOperadores(operadores)->info != '['){
            pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
             
          }
        break;
        case 3:
        while(retornaUltimoOperadores(operadores)->info != '{'){
             pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
             
          }
        break;
        }
      //Tira a abertura dos parenteses
      popCaracterPilha(&operadores);         
      printaPilha(operandos,operadores);
      if(retornaUltimoOperadores(operadores)->info=='*'){
        pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
      }
       
    }else if(caracter == ')' && (eNum==0 && eOperador==0)){
      return -1; 
    }else if(isOperador(caracter)){
      if(caracter == '-'){
        pushCaracterPilha(&operadores,'+');
        pushNumeroPilha(&operandos,-1);
        pushCaracterPilha(&operadores,'*');
      }else{
        pushCaracterPilha(&operadores,caracter);
      }
      printaPilha(operandos,operadores);  
      eOperador=precedencia(caracter);
      eNum=0;
    }
  }

  
  while(operandos->prox!=NULL){    
    pushNumeroPilha(&operandos,operacaoPilha(&operandos,&operadores));
    printaPilha(operandos,operadores);
  }
  
  printf("\n");
  printaPilha(operandos,operadores);  
  resultado = popNumeroPilha(&operandos);
  return resultado;
}


