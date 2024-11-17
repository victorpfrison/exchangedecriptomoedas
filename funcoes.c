#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#define SUCESSO 0  // Define SUCESSO como 0
#define ERRO 1     // Define ERRO como 1


int loginAdministrador(char cpf[12], char senha[50]){
  printf("LOGIN ADM");
}
void carregarInvestidor(Investidor investidores[], int *numInvestidores){
    FILE *file = fopen("investidores.bin", "rb");
    if (file) {
        *numInvestidores = fread(investidores, sizeof(Investidor), 100, file);
        fclose(file);
    }
}
// funcao salvar
void salvarInvestidor(Investidor investidores[], int *numInvestidores){
      FILE *file = fopen("investidores.bin", "wb");
    if (file) {
        fwrite(investidores, sizeof(Investidor), *numInvestidores, file);
        fclose(file);
        return 0; 
    } else { 
        printf("[ERRO] Não foi possível abrir o arquivo.\n");
        return 1; 
}
}
void cadastrarInvestidor(Investidor *investidores, int *numInvestidores) {
    Investidor novoInvestidor;
    
    printf("\n\nCadastre o Investidor(a)\n\n");
    printf("Digite seu CPF: ");
    scanf("%s", novoInvestidor.cpf);
    clearBuffer();
    printf("Digite sua senha: ");
    scanf("%s", novoInvestidor.senha);

  
    novoInvestidor.saldoBitcoin = 0.0;
    novoInvestidor.saldoEthereum = 0.0;
    novoInvestidor.saldoRipple = 0.0;

    investidores[(*numInvestidores)++] = novoInvestidor;
    printf("Cadastro realizado com sucesso! Agora faça o login\n");

    salvarInvestidor(investidores, numInvestidores);
    return 0;
}
void excluirInvestidor(Investidor *investidores, int *numInvestidores) {
    char cpf[12];
    int i, posicao = -1;

    if (*numInvestidores == 0) {
        printf("Não há investidores cadastrados.\n");
        return;
    }

    printf("Digite o CPF do investidor que deseja deletar: ");
    scanf("%s", cpf);
    clearBuffer();

    // Procurar o investidor pelo CPF
    for (i = 0; i < *numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Investidor com CPF %s não encontrado.\n", cpf);
        return;
    }

    for (i = posicao; i < *numInvestidores - 1; i++) {
        investidores[i] = investidores[i + 1];
    }

    (*numInvestidores)--; 
    printf("Investidor com CPF %s foi excluído com sucesso.\n", cpf);

    salvarInvestidor(investidores, numInvestidores);
}


void cadastrarCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos){
  printf("Cadastrar Criptomoeda");
  }

void excluirCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos){
  printf("Excluir Cripto");
}
void consultarSaldo(Investidor *investidores, int numInvestidores) {
    char cpf[12];
    int encontrado = 0;

    if (numInvestidores == 0) {
        printf("Não há investidores cadastrados.\n");
        return;
    }

    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);
    clearBuffer();

    // Procurar o investidor pelo CPF
    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            printf("\nSaldo do Investidor com CPF %s:\n", cpf);
            printf("saldo em Reais: R$ %.2f\n", investidores[i].saldoReais);
            printf("saldo em Bitcoin: %.2f\n", investidores[i].saldoBitcoin);
            printf("saldo em Ethereum: %.2f\n", investidores[i].saldoEthereum);
            printf("saldo em Ripple: %.2f\n", investidores[i].saldoRipple);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Investidor com CPF %s não encontrado.\n", cpf);
    }
}
void consultarExtrato(Investidor *investidores, int numInvestidores){
  printf("Consultar extrato");
  }
void atualizarCotacao(Criptomoeda *criptomoedas, int numCriptos){
  printf("Atualizar Cotacao");

}
//clearbuffer
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}