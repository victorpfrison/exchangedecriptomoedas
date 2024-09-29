#include "funcoes.h"
#include <stdio.h>

typedef RESULTADOS (*funcoes)(Usuario *, void *);
int main() {
  // funcoes criada na funcoes.h para as operacoes
  funcoes funcao[] = {consultarSaldo,  consultarExtrato,   depositarReais,
                      sacarReais,      comprarCriptomoeda, venderCriptomoeda,
                      atualizarCotacao};
  Usuario usuarios[MAXUSUARIO];
  int numUsuarios = 0;
  char cpf[12];
  char senha[6];
  int usuarioLogon = -1;
  // carregando usuarios cadastrados
  carregarUsuario(usuarios, &numUsuarios);
  // efetuando o login
  while (usuarioLogon == -1) {
    printf("PROJETO 1 - EXCHANGE DE CRIPTOMOEDAS\n");
    printf("{1} para login\n");
    printf("{2} para cadastrar\n");
    printf("{0} SAIR\n");
    printf("DIGITE AQUI: ");
    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite seu CPF: ");
      scanf("%s", cpf);
      clearBuffer();
      printf("Digite sua senha: ");
      scanf("%s", senha);
      clearBuffer();
      usuarioLogon = login(usuarios, numUsuarios, cpf, senha);
      if (usuarioLogon == -1) {
        printf("CPF ou senha inválidos. Tente novamente.\n");
      }
      break;
    case 2:
      cadastrarUsuario(usuarios, &numUsuarios);
      break;
    case 0:
      printf("Saindo do programa...\n");
      return 0;
    default:
      printf("Opção inválida.\n");
    }
  }
  int opcao;
  do {
    printf("\n\tMENU PRINCIPAL\n\t\n");
    printf("\t1 - Consultar saldo\n\t");
    printf("2 - Consultar extrato\n\t");
    printf("3 - Depositar reais\n\t");
    printf("4 - Sacar reais\n\t");
    printf("5 - Comprar criptomoeda\n\t");
    printf("6 - Vender criptomoeda\n\t");
    printf("7 - Atualizar cotacao\n\t");
    printf("0 - Sair\n\t");
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      funcao[0](&usuarios[usuarioLogon],
                NULL); // chamando a funcao consultarSaldo
      break;
    case 2:
      funcao[1](&usuarios[usuarioLogon],
                NULL); // chamando a funcao consultarExtrato
      break;
    case 3:
      funcao[2]; // chamando a funcao depositarReais
      break;
    case 4:
      funcao[3]; // chamando a funcao sacarReais
      break;
    case 5:
      funcao[4]; // chamando a funcao comprarCriptomoeda
      break;
    case 6:
      funcao[5]; // chamando a funcao venderCriptomoeda
      break;
    case 7:
      funcao[6]; // chamando a funcao atualizarCotacao
      break;
    case 0:
      salvarUsuario(usuarios, &numUsuarios);
      printf("Saindo. ATÉ A PRÓXIMA\n");
      return 0;
      break;
    default:
      printf("OPÇÃO INVALIDA");
    }
  }

  while (opcao != 0);
  salvarUsuario(usuarios, &numUsuarios);
  return 0;
}