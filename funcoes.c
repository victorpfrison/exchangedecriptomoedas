#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#define SUCESSO 0  // Define SUCESSO como 0
#define ERRO 1     // Define ERRO como 1


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
  int transacao = 0;
  for (int i = 0; i < MAXTRANSACOES; i++) {
    if (usuario->extrato[i][0] != '\0') { // verifica se há transações
      printf("%s\n", usuario->extrato[i]);
      transacao = 1; // encontrou uma transação
    } else  if (!transacao) {
        printf("Não há transações realizadas até o momento.\n");
    }
  }
  return OK;
}
RESULTADOS depositarReais(Usuario *usuario, float valor) {
  printf("Digite o valor a depositar: ");
  scanf("%f", &valor);
  if (valor <= 0) {
          printf("[ERRO] O valor do depósito deve ser positivo.\n");
          return ERRO;  
      }

      usuario->saldoReais += valor;  // add valor
      printf("Depósito de R$%.2f realizado com sucesso! Seu novo saldo é R$%.2f\n", valor, usuario->saldoReais);
       // Adicionando a transação ao extrato
    for (int i = 0; i < MAXTRANSACOES; i++) {
      if (usuario->extrato[i][0] == '\0') { 
        snprintf(usuario->extrato[i], sizeof(usuario->extrato[i]), "Depósito de R$%.2f", valor);
        break;
      }
    }

      return OK;

}
RESULTADOS sacarReais(Usuario *usuario, float valor, char senha[]) {
    printf("Digite sua senha: ");
    scanf("%s", senha);
    clearBuffer();
    printf("Digite o valor a sacar: ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("[ERRO] O valor do saque deve ser positivo.\n");
        return ERRO;
    }

    // Verifica se a senha está correta
    if (strcmp(usuario->senha, senha) != 0) {
        printf("[ERRO] Senha incorreta.\n");
        return ERRO;
    }

    // Verifica se o usuário tem saldo suficiente
    if (usuario->saldoReais < valor) {
        printf("[ERRO] Saldo insuficiente. Saldo atual: R$%.2f\n", usuario->saldoReais);
        return ERRO;
    }

    // Realiza o saque
    usuario->saldoReais -= valor;
    printf("Saque de R$%.2f realizado com sucesso! Saldo restante: R$%.2f\n", valor, usuario->saldoReais);
     // Adicionando a transação ao extrato
    for (int i = 0; i < MAXTRANSACOES; i++) {
        if (usuario->extrato[i][0] == '\0') { // Encontra um espaço vazio
          snprintf(usuario->extrato[i], sizeof(usuario->extrato[i]), "Saque de R$%.2f", valor);
          break;
      }
    }


    return OK;
}
RESULTADOS comprarCriptomoeda(Usuario *usuario, float valor, char senha[], char nomeCripto[]) {
    int opcao;
    printf("Comprar criptomoeda\n");
    printf("[1] Bitcoin\n");
    printf("[2] Ethereum\n");
    printf("[3] Ripple\n");
    printf("Digite:");
    scanf("%d", &opcao);

    printf("Digite o valor em reais que deseja trocar: ");
    scanf("%f", &valor);

    float taxacomBitcoin = 0.02;
    float taxacomEthereum = 0.01;
    float taxacomRipple = 0.01;

    if (usuario->saldoReais >= valor) {
        switch (opcao) {
        case 1:  // Bitcoin
            usuario->saldoBitcoin += valor * (1 - taxacomBitcoin);
            usuario->saldoReais -= valor;
            printf("Compra de Bitcoin realizada com sucesso!\n");
            break;
        case 2:  // Ethereum
            usuario->saldoEthereum += valor * (1 - taxacomEthereum);
            usuario->saldoReais -= valor;
            printf("Compra de Ethereum realizada com sucesso!\n");
            break;
        case 3:  // Ripple
            usuario->saldoRipple += valor * (1 - taxacomRipple);
            usuario->saldoReais -= valor;
            printf("Compra de Ripple realizada com sucesso!\n");
            break;
        default:
            printf("Opção inválida.\n");
            return ERRO;
        }

        // Registra a transação no extrato
        for (int i = 0; i < MAXTRANSACOES; i++) {
            if (usuario->extrato[i][0] == '\0') {
                snprintf(usuario->extrato[i], sizeof(usuario->extrato[i]), "Compra de %.2f em %s", valor, nomeCripto);
                break;
            }
        }
    } else {
        printf("Saldo insuficiente para realizar a compra.\n");
        return ERRO;
    }

    return SUCESSO;
}
RESULTADOS venderCriptomoeda(Usuario *usuario, float valor, char senha[], char nomeCripto[]) {
    int opcao;
    printf("Vender criptomoeda\n");
    printf("Qual criptomoeda deseja vender?\n");
    printf("[1] Bitcoin\n");
    printf("[2] Ethereum\n");
    printf("[3] Ripple\n");
    printf("Digite:");
    scanf("%d", &opcao);

    printf("Quantas criptomoedas deseja vender?\n");
    printf("Digite:");
    scanf("%f", &valor);

    float taxavenBitcoin = 0.03;
    float taxavenEthereum = 0.02;
    float taxavenRipple = 0.01;

    switch (opcao) {
    case 1:  // Bitcoin
        if (usuario->saldoBitcoin >= valor) {
            usuario->saldoReais += valor * (1 - taxavenBitcoin);
            usuario->saldoBitcoin -= valor;
            printf("Venda de Bitcoin realizada com sucesso!\n");
        } else {
            printf("Saldo de Bitcoin insuficiente para venda.\n");
            return ERRO;
        }
        break;
    case 2:  // Ethereum
        if (usuario->saldoEthereum >= valor) {
            usuario->saldoReais += valor * (1 - taxavenEthereum);
            usuario->saldoEthereum -= valor;
            printf("Venda de Ethereum realizada com sucesso!\n");
        } else {
            printf("Saldo de Ethereum insuficiente para venda.\n");
            return ERRO;
        }
        break;
    case 3:  // Ripple
        if (usuario->saldoRipple >= valor) {
            usuario->saldoReais += valor * (1 - taxavenRipple);
            usuario->saldoRipple -= valor;
            printf("Venda de Ripple realizada com sucesso!\n");
        } else {
            printf("Saldo de Ripple insuficiente para venda.\n");
            return ERRO;
        }
        break;
    default:
        printf("Opção inválida.\n");
        return ERRO;
    }

    // Registra a transação no extrato
    for (int i = 0; i < MAXTRANSACOES; i++) {
        if (usuario->extrato[i][0] == '\0') {
            snprintf(usuario->extrato[i], sizeof(usuario->extrato[i]), "Venda de %.2f em %s", valor, nomeCripto);
            break;
        }
    }
      return SUCESSO;
}
RESULTADOS atualizarCotacao() {
  srand(time(NULL));
    // cotação incial moedas
    float cotacaoBcoin = 600000; 
    float cotacaoEth = 2000;   
    float cotacaoRip = 1000;     

    printf("Cotações iniciais:\n");
    printf("Bitcoin: %.2f\n", cotacaoBcoin);
    printf("Ethereum: %.2f\n", cotacaoEth);
    printf("Ripple: %.2f\n", cotacaoRip);

    // atualização das moedas em random
        cotacaoBcoin *= 1 + (rand() % 11 - 5) / 100.0; 
        cotacaoEth *= 1 + (rand() % 11 - 5) / 100.0; 
        cotacaoRip *= 1 + (rand() % 11 - 5) / 100.0; 
        printf("\nAtualização\n");
        printf("Bitcoin: %.2f\n", cotacaoBcoin);
        printf("Ethereum: %.2f\n", cotacaoEth);
        printf("Ripple: %.2f\n", cotacaoRip);

}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}