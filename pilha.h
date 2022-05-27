
typedef struct pilha{
  double info;
  struct pilha *prox;
}PilhaOperandos;

typedef struct pilha2{
  char info;
  struct pilha2 *prox;
}PilhaOperadores;


int isOperador(char caracter);

int precedencia(char operador);

PilhaOperandos* retornaUltimo(PilhaOperandos* p);

PilhaOperadores* retornaUltimoOperadores(PilhaOperadores* p);

PilhaOperandos* retornaProximoTopoOperandos(PilhaOperandos* p);

PilhaOperadores* retornaProximoTopoOperadores(PilhaOperadores* p);

void pushNumeroPilha(PilhaOperandos** p, double numero);

void pushCaracterPilha(PilhaOperadores** p, char caracter);

double popNumeroPilha(PilhaOperandos** p);

char popCaracterPilha(PilhaOperadores** p);

double operacaoPilha(PilhaOperandos** operandos, PilhaOperadores** operadores);

double calculoPilha(char expressao[]);

int precedenciaEspeciais(char operador);

void printaPilha(PilhaOperandos* pO,PilhaOperadores* pOp);