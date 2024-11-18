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


void cadastrarCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos) {
  if (*numCriptos >= MAXCRIPTOS) {
        printf("Limite máximo de criptomoedas atingido.\n");
        return;
    }

    Criptomoeda novaCripto;

    printf("\n\nCadastro de nova Criptomoeda\n\n");
    printf("Digite o nome da criptomoeda: ");
    scanf("%s", novaCripto.nome);
    clearBuffer();

    printf("Digite a cotação inicial: ");
    scanf("%f", &novaCripto.cotacao);
    clearBuffer();

    printf("Digite a taxa de compra (em %%): ");
    scanf("%f", &novaCripto.taxaCompra);
    clearBuffer();

    printf("Digite a taxa de venda (em %%): ");
    scanf("%f", &novaCripto.taxaVenda);
    clearBuffer();

    criptomoedas[(*numCriptos)++] = novaCripto;
// criando um arquivo para guardar as criptomoedas cadastradas
    FILE *file = fopen("cripto.txt", "a"); 
    if (file) {
        fprintf(file, 
                "\nNome: %s\n"
                "Cotação: %.2f\n"
                "Taxa de Compra: %.2f%%\n"
                "Taxa de Venda: %.2f%%\n"
                "--------------------------\n",
                novaCripto.nome,
                novaCripto.cotacao,
                novaCripto.taxaCompra,
                novaCripto.taxaVenda);
        fclose(file);
        printf("Criptomoeda cadastrada com sucesso!\n");
    } else {
        printf("[ERRO] Não foi cadastrar criptomoeda.\n");
    }
}


void excluirCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos) {
    char nome[50];
    printf("\n\tDigite o nome da criptomoeda a ser excluída: ");
    scanf("%s", nome);

    for (int i = 0; i < *numCriptos; i++) {
        if (strcmp(criptomoedas[i].nome, nome) == 0) {
            printf("\n\tCriptomoeda encontrada: %s\n", criptomoedas[i].nome);
            printf("\tTem certeza que deseja excluir? (S/N): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 'S' || confirmacao == 's') {
                for (int j = i; j < *numCriptos - 1; j++) {
                    criptomoedas[j] = criptomoedas[j + 1];
                }
                (*numCriptos)--;
               
                FILE *file = fopen("cripto.txt", "w"); 
                if (file) {
                    for (int k = 0; k < *numCriptos; k++) {
                        fprintf(file, 
                                "Nome: %s\n"
                                "Cotação: %.2f\n"
                                "Taxa de Compra: %.2f%%\n"
                                "Taxa de Venda: %.2f%%\n"
                                "--------------------------\n",
                                criptomoedas[k].nome,
                                criptomoedas[k].cotacao,
                                criptomoedas[k].taxaCompra,
                                criptomoedas[k].taxaVenda);
                    }
                    fclose(file);
                    printf("\nCriptomoeda excluída e arquivo atualizado com sucesso.\n");
                } else {
                    printf("[ERRO] Não foi possível atualizar o arquivo admin.txt após a exclusão.\n");
                }
                return;
            } else {
                printf("\nExclusão cancelada.\n");
                return;
            }
        }
    }
    printf("Criptomoeda não encontrada.\n");
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
            printf("\nSaldo Investidor com CPF %s:\n", cpf);
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