#include <stdio.h>  
#ifndef FUNCOES_H
#define FUNCOES_H
#define MAXTRANSACOES 100
#define MAXUSUARIO 10

// para armazenr informações do usuario
typedef struct{
  char cpf[12];
  char senha[6];
  float saldoReais;
  float saldoBitcoin;
  float saldoEthereum;
  float saldoRipple;
  char extrato[100][256];
} Usuario;
typedef enum{
    OK,
    LIMITEUSUARIOS,
    ERRO,
    ARQUIVO_NAO_ENCONTRADO,
    ABRIR,
    ESCREVER,
    FECHAR,
    LER
}RESULTADOS;

typedef RESULTADOS (*funcoes)(Usuario*, void *);

// para o login e cadastro
RESULTADOS login(Usuario usuarios[], int numUsuarios, char cpf[], char senha[]);
RESULTADOS  carregarUsuario(Usuario usuarios[], int *numUsuarios);
RESULTADOS  cadastrarUsuario(Usuario usuarios[], int *numUsuarios);
RESULTADOS  salvarUsuario(Usuario usuarios[], int *numUsuarios);
// fim do login e cadastro.
//operações
RESULTADOS  consultarSaldo(Usuario *usuario);
RESULTADOS  consultarExtrato(Usuario *usuario);
RESULTADOS  depositarReais(Usuario *usuario, float valor);
RESULTADOS  sacarReais(Usuario *usuario, float valor, char senha []);
RESULTADOS  comprarCriptomoeda(Usuario *usuario, float valor, char senha [], char nomeCripto[]);
RESULTADOS  venderCriptomoeda(Usuario *usuario, float valor, char senha [], char nomeCripto[]);
RESULTADOS  atualizarCotacao();
void clearBuffer();

#endif 