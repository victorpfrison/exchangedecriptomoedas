#include "funcoes.h"
#include <stdio.h>
#include <string.h>

RESULTADOS login(Usuario usuarios[], int numUsuarios, char cpf[],
                 char senha[]) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      printf("BEM-VINDO(A)!\n");
      return i; // Retorna o índice do usuário logado
    }
  }
  return -1; // CPF ou senha inválidos
}
RESULTADOS carregarUsuario(Usuario usuarios[], int *numUsuarios) {
  FILE *file = fopen("usuarios.bin", "rb");
  if (file) {
    *numUsuarios = fread(usuarios, sizeof(Usuario), 100, file);
    fclose(file);
  }
}
RESULTADOS cadastrarUsuario(Usuario usuarios[], int *numUsuarios) {
  Usuario novoUsuario;
  printf("Digite seu CPF: ");
  scanf("%s", novoUsuario.cpf);

  printf("Digite sua senha: ");
  scanf("%s", novoUsuario.senha);

  // saldos do novo usuario
  novoUsuario.saldoReais = 0.0;
  novoUsuario.saldoBitcoin = 0.0;
  novoUsuario.saldoEthereum = 0.0;
  novoUsuario.saldoRipple = 0.0;

  usuarios[(*numUsuarios)++] = novoUsuario;
  printf("Cadastro realizado com sucesso! Agora faça o login\n");
  salvarUsuario(usuarios, &numUsuarios); // Passando numUsuarios como ponteiro
  return 0;
}

RESULTADOS salvarUsuario(Usuario usuarios[], int *numUsuarios) {
  FILE *file = fopen("usuarios.bin", "wb");
  if (file) {
    fwrite(usuarios, sizeof(Usuario), *numUsuarios, file); // Usar *numUsuarios
    fclose(file);
    return OK;
  } else {
    printf("[ERRO] Não foi possível abrir o arquivo.\n");
    return ARQUIVO_NAO_ENCONTRADO;
  }
}

RESULTADOS consultarSaldo(Usuario *usuario) {
  printf("Consultar saldo\n");
  printf("Saldo atual:\n");
  printf("Saldo em Reais: %.2f\n", usuario->saldoReais);
  printf("Saldo em Bitcoin: %.2f\n", usuario->saldoBitcoin);
  printf("Saldo em Ethereum: %.2f\n", usuario->saldoEthereum);
  printf("Saldo em Ripple: %.2f\n", usuario->saldoRipple);
  return OK;
}
RESULTADOS consultarExtrato(Usuario *usuario) {
  printf("Consultar extrato\n");
  for (int i = 0; i < MAXTRANSACOES; i++) {
    if (usuario->extrato[i][0] != '\0') { // verifica se há transações
      printf("%s\n", usuario->extrato[i]);

    } else {
      printf("Não há transações realizadas até o momento.\n");
      break;
    }
  }
  return OK;
}
RESULTADOS depositarReais(Usuario *usuario, float valor) {
  printf("Depositar reais\n");
}
RESULTADOS sacarReais(Usuario *usuario, float valor, char senha[]) {
  printf("Sacar reais\n");
}
RESULTADOS comprarCriptomoeda(Usuario *usuario, float valor, char senha[],
                              char nomeCripto[]) {
  printf("Comprar criptomoeda\n");
  printf("Comprar criptomoeda\n");
  printf("[1] Bitcoin\n");
  printf("[2] Ethereum\n");
  printf("[3] Ripple\n");
  int opcao;
  scanf("%d", &opcao);

  printf("Digite o valor em real que deseja trocar:");
  scanf("%f", &valor);
  float taxacomBitcoin = 0.02;
  float taxacomEthereum = 0.01;
  float taxacomRipple = 0.01;

  if (usuario->saldoReais >= valor) {
    switch (opcao) {
    // Bitcoin
    case 1:
      usuario->saldoBitcoin += valor * taxacomBitcoin;
      usuario->saldoReais -= valor;
      printf("Compra realizada com sucesso!\n");
      break;
    // Ethereum
    case 2:
      usuario->saldoEthereum += valor * taxacomEthereum;
      usuario->saldoReais -= valor;
      printf("Compra realizada com sucesso!\n");
      break;
    // Ripple
    case3:
      usuario->saldoRipple += valor * taxacomRipple;
      usuario->saldoReais -= valor;
      printf("Compra realizada com sucesso!\n");
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  } else {
    printf("Saldo insuficiente para realizar a compra\n");
  }
}
RESULTADOS venderCriptomoeda(Usuario *usuario, float valor, char senha[],
                             char nomeCripto[]) {
  int opcao;
  printf("Vender criptomoeda\n");
  printf("Qual criptomoeda deseja vender?\n");
  printf("[1] Bitcoin\n");
  printf("[2] Ethereum\n");
  printf("[3] Ripple\n");
  scanf("%d", &opcao);

  printf("Quantas criptomoedas deseja vender?\n");
  scanf("%f", &valor);
  float taxavenBitcoin = 0.03;
  float taxavenEthereum = 0.02;
  float taxavenRipple = 0.01;

  switch (opcao) {
  // Venda Bitcoin
  case 1:
    if (usuario->saldoBitcoin >= valor) {
      usuario->saldoReais += valor * taxavenBitcoin;
      usuario->saldoBitcoin -= valor;
      printf("Venda realizada com sucesso!\n");
    } else {
      printf("Valor de Bitcoin insuficiente para venda.\n");
    }
    break;

  case2:
    if (usuario->saldoEthereum >= valor) {
      usuario->saldoReais += valor * taxavenEthereum;
      usuario->saldoEthereum -= valor;
      printf("Venda realizada com sucesso!\n");
    } else {
      printf("Valor de Ethereum insuficiente para venda.\n");
    }
    break;
  case3:
    if (usuario->saldoRipple >= valor) {
      usuario->saldoReais += valor * taxavenRipple;
      usuario->saldoRipple -= valor;
      printf("Venda realizada com sucesso!\n");
    } else {
      printf("Valor de Ripple insuficiente para venda.\n");
    }
    break;
  default:
    printf("Opção inválida.\n");
    break;
  }
}
RESULTADOS atualizarCotacao() { printf("Atualizar cotacao\n"); }
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}