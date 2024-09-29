#include "funcoes.h"
#include <stdio.h>
#include <string.h>


RESULTADOS login(Usuario usuarios[], int numUsuarios, char cpf[], char senha[]){
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("BEM-VINDO(A)!\n");
            return i; // Retorna o índice do usuário logado
        }
    }
    return -1; // CPF ou senha inválidos
}

RESULTADOS  carregarUsuario(Usuario usuarios[], int *numUsuarios){
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

    //saldos do novo usuario
    novoUsuario.saldoReais = 0.0;
    novoUsuario.saldoBitcoin = 0.0;
    novoUsuario.saldoEthereum = 0.0;
    novoUsuario.saldoRipple = 0.0;

    usuarios[(*numUsuarios)++] = novoUsuario;
    printf("Cadastro realizado com sucesso! Agora faça o login\n");
    salvarUsuario(usuarios, &numUsuarios);// Passando numUsuarios como ponteiro
    return 0;
}

RESULTADOS salvarUsuario(Usuario usuarios[], int *numUsuarios) {
    FILE *file = fopen("usuarios.bin", "wb");
    if (file) {
        fwrite(usuarios, sizeof(Usuario) ,*numUsuarios, file); // Usar *numUsuarios
        fclose(file);
        return OK;
    } else {
        printf("[ERRO] Não foi possível abrir o arquivo.\n");
        return ARQUIVO_NAO_ENCONTRADO;
    }
}


RESULTADOS consultarSaldo(Usuario *usuario){
  printf("Consultar saldo\n");
    printf("Saldo atual:\n");
    printf("Saldo em Reais: %.2f\n", usuario->saldoReais);
    printf("Saldo em Bitcoin: %.2f\n", usuario->saldoBitcoin);
    printf("Saldo em Ethereum: %.2f\n", usuario->saldoEthereum);
    printf("Saldo em Ripple: %.2f\n", usuario->saldoRipple);
    return OK;
}
RESULTADOS consultarExtrato(Usuario *usuario){
  printf("Consultar extrato\n");
    for(int i = 0; i< MAXTRANSACOES; i++){
        if(usuario->extrato[i][0] != '\0'){// verifica se há transações
            printf("%s\n", usuario->extrato[i]);

        }else{
            printf("Não há transações realizadas.\n");
            break;
        }
    }
    return OK;
}
RESULTADOS depositarReais(Usuario *usuario, float valor){
  printf("Depositar reais\n");
}
RESULTADOS sacarReais(Usuario *usuario, float valor, char senha []){
  printf("Sacar reais\n");
}
RESULTADOS comprarCriptomoeda(Usuario *usuario, float valor, char senha [], char nomeCripto[]){
  printf("Comprar criptomoeda\n");
}
RESULTADOS venderCriptomoeda(Usuario *usuario, float valor, char senha [], char nomeCripto[]){
   printf("Vender criptomoeda\n");

}
RESULTADOS atualizarCotacao(){
   printf("Atualizar cotacao\n");
}
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}