#ifndef FUNCOES_H
#define FUNCOES_H

#define MAXTRANSACOES 100
#define MAXCRIPTOS 50
#define MAXINVESTIDORES 10


typedef struct {
    char nome[100];
    char cpf[12];  
    char senha[50];
    float saldoReais;
    float saldoBitcoin;
    float saldoEthereum;
    float saldoRipple;
    char extrato[MAXTRANSACOES][100];
} Investidor;


typedef struct {
    char nome[50];
    float cotacao;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;


typedef enum{
    OK,
    LIMITEUSUARIOS,
    ARQUIVO_NAO_ENCONTRADO,
    ABRIR,
    ESCREVER,
    FECHAR,
    LER
}RESULTADOS;

//funcoes
int loginAdministrador(char cpf[12], char senha[50]);
void carregarInvestidor(Investidor investidores[], int *numInvestidores);
void salvarInvestidor(Investidor investidores[], int *numInvestidores);
void cadastrarInvestidor(Investidor *investidores, int *numInvestidores);
void excluirInvestidor(Investidor *investidores, int *numInvestidores);
void cadastrarCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos);
void excluirCriptomoeda(Criptomoeda *criptomoedas, int *numCriptos);
void consultarSaldo(Investidor *investidores, int numInvestidores);
void consultarExtrato(Investidor *investidores, int numInvestidores);
void atualizarCotacao(Criptomoeda *criptomoedas, int numCriptos);
void clearBuffer();

#endif  
