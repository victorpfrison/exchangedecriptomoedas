#include <stdio.h>
#include <string.h>
#include "funcoes.h"


    
int main() {
    Investidor investidores[MAXINVESTIDORES];
    Criptomoeda criptomoedas[MAXCRIPTOS];
    int numInvestidores = 0;
    int numCriptos = 0;

    char cpfAdministrador[12], senhaAdministrador[50];
    int opcao;

    printf("Digite o CPF do Administrador: ");
    scanf("%s", cpfAdministrador);
    printf("Digite a senha do Administrador: ");
    scanf("%s", senhaAdministrador);

    if (verificarAdministrador(cpfAdministrador, senhaAdministrador) == 0) {
        printf("Administrador não encontrado. Deseja cadastrar um novo administrador? (sim /não): ");
        char escolha;
        scanf(" %c", &escolha);
        if (escolha == 's' || escolha == 'S') {
            cadastrarAdministrador(cpfAdministrador, senhaAdministrador);
            printf("Faça login.\n");
            return 0;
        } else {
            printf("Até mais!\n");
            return 0;
        }
    } else {
        printf("Login do Administrador realizado\n");
    }
    
   

    // Menu do Administrador
    while (1) {
        printf("\n\tMENU PRINCIPAL - ADMINISTRADOR\n\t\n");
        printf("\t1 - Cadastrar Investidor\n\t");
        printf("2 - Excluir Investidor\n\t");
        printf("3 - Cadastrar Criptomoeda\n\t");
        printf("4 - Excluir Criptomoeda\n\t");
        printf("5 - Consultar Saldo de Investidor\n\t");
        printf("6 - Consultar Extrato de Investidor\n\t");
        printf("7 - Atualizar Cotação de Criptomoeda\n\t");
        printf("8 - Sair\n\t");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        //loop
        switch(opcao) {
            case 1:
                cadastrarInvestidor(investidores, &numInvestidores);
                break;
            case 2:
                excluirInvestidor(investidores, &numInvestidores);
                break;
            case 3:
                cadastrarCriptomoeda(criptomoedas, &numCriptos);
                break;
            case 4:
                excluirCriptomoeda(criptomoedas, &numCriptos);
                break;
            case 5:
                consultarSaldo(investidores, numInvestidores);
                break;
            case 6:
                consultarExtrato(investidores, numInvestidores);
                break;
            case 7:
                atualizarCotacao(criptomoedas, numCriptos);
                break;
            case 8:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}
