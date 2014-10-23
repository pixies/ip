#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contaCorrente {
    char nome[40];
    int agencia;
    double saldo;
    double manutencao;
} ContaCorrente;

typedef struct contaEspecial{
    char nome[40];
    int agencia;
    double saldo;
    double limiteEspecial;
} ContaEspecial;

typedef union contaGeral{
    ContaCorrente cc;
    ContaEspecial ce;
} ContaGeral;

typedef enum tipo {CC,CE} TIPO;

typedef struct conta {
    TIPO tipo;
    ContaGeral cg;
} Conta;

Conta* criaConta(TIPO tipo,char* nome, int agencia) {
    Conta* conta = (Conta*) malloc(sizeof(Conta));
    conta->cg.cc.agencia = agencia;
    strcpy(conta->cg.cc.nome,nome);
    conta->cg.cc.saldo = 0;
    conta->tipo = tipo;
    if (tipo == CE) {
        conta->cg.ce.limiteEspecial = 1000;
    } else {
        conta->cg.cc.manutencao = 10;
    }
    return conta;
}

void debito(Conta* conta, double valor) {
    printf("\nTentativa de debito de  %.2lf\n",valor);
    double saldo = conta->cg.cc.saldo;
    if (conta->tipo == CC) {
            saldo = saldo - conta->cg.cc.manutencao;
    }
    if (saldo >= valor) {
        conta->cg.cc.saldo = conta->cg.cc.saldo - valor;
    } else if(conta->tipo == CE && (saldo + conta->cg.ce.limiteEspecial) > valor ) {
       //Calcula o quanto vai ficar devendo
        saldo = conta->cg.ce.saldo - valor;
       // Zera o saldo
        conta->cg.ce.saldo = 0;
       // Atualiza limite com o que ficou devendo
        conta->cg.ce.limiteEspecial = conta->cg.ce.limiteEspecial + saldo;
    } else {
        printf("Saldo Insuficiente para esta operacao\n\n");
    }
}
void credito(Conta* conta, double valor) {
     printf("\nCredito de  %.2lf\n",valor);
    // Verifica se é especial e estah devendo
    if(conta->tipo == CE && conta->cg.ce.limiteEspecial < 1000 ) {
        //Atualiza limiteEspecial
        conta->cg.ce.limiteEspecial = conta->cg.ce.limiteEspecial + valor;
       // Se valor maior do que o que estah devendo, atualiza limite e saldo
        if (conta->cg.ce.limiteEspecial > 1000) {
            conta->cg.ce.saldo = conta->cg.ce.limiteEspecial - 1000;
            conta->cg.ce.limiteEspecial = 1000;
        }
    } else {
        conta->cg.cc.saldo = conta->cg.cc.saldo + valor;
    }


}


void imprimeSaldo(Conta* conta) {
    double saldo = conta->cg.cc.saldo;
    if (conta->tipo == CC) {
        saldo = saldo - conta->cg.cc.manutencao;
    }
    printf("Cliente = %s\n", conta->cg.cc.nome);
    printf("Agencia = %d\n", conta->cg.cc.agencia);
    printf("Saldo = %.2lf\n", saldo);
    if (conta->tipo == CE) {
        printf("Limite = %.2lf\n\n", conta->cg.ce.limiteEspecial);
    }
}

int main()
{
 /*   Conta* conta1 = criaConta(CC,"Jose",123);
    credito(conta1,300);
    imprimeSaldo(conta1);
    debito(conta1,200);
    imprimeSaldo(conta1);
    debito(conta1,200);
*/
    Conta* conta2 = criaConta(CE,"Julia",124);
    imprimeSaldo(conta2);
    credito(conta2,300);
    imprimeSaldo(conta2);
    debito(conta2,200);
    imprimeSaldo(conta2);
    debito(conta2,200);
    imprimeSaldo(conta2);
    credito(conta2,50);
    imprimeSaldo(conta2);
    credito(conta2,100);
    imprimeSaldo(conta2);

    return 0;
}
