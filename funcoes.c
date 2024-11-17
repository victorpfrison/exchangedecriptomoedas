#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#define SUCESSO 0  // Define SUCESSO como 0
#define ERRO 1     // Define ERRO como 1

void cadastrarAdministrador(char cpf[12], char senha[50]) {
    FILE *file = fopen("admin.txt", "w");  
    
    if (file) {
        fprintf(file, "%s\n%s", cpf, senha);  
        fclose(file);
        printf("Administrador cadastrado com sucesso!\n");
    } else {
        printf("[ERRO] Não foi possível abrir o arquivo de cadastro do administrador.\n");
    }
}

int verificarAdministrador(char cpf[12], char senha[50]) {
    FILE *file = fopen("admin.txt", "r");
    if (file) {
        char cpfSalvo[12], senhaSalva[50];
        fscanf(file, "%s\n%s", cpfSalvo, senhaSalva);
        fclose(file);

        if (strcmp(cpf, cpfSalvo) == 0 && strcmp(senha, senhaSalva) == 0) {
            return 1; 
        }
    }
    return 0;
}

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
void excluirInvestidor(Investidor *investidores, int *numInvestidores){
  printf("Excluir Investidor");
}

void cadastrarCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos){
  printf("Cadastrar Criptomoeda");
  }

void excluirCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos){
  printf("Excluir Cripto");
}
void consultarSaldo(Investidor *investidores, int numInvestidores){
  printf("Consultar Saldo");
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