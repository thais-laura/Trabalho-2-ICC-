#include <stdio.h>
#include <stdlib.h>
#define LIM 5

typedef struct{
    char nome[50];
    int num;
    int senha;
    int data_nasc[3];
    char ender[100];
    int qtd;
    int data_empr[LIM][3];
    int data_dev[LIM][3];
    char nome_livro[LIM][40];
    char nome_autor[LIM][40]
} t_cadastro;

int menu(){
    char s_opcao[3];
    int opcao;
    printf("\tBIBLIOTECA\n");
    printf("\t>>Menu<<\n");
    printf("1. Novo cadastro\n");
    printf("2. Empréstimo\n");
    printf("3. Busca\n"); //trocar nome
        //1. levar às verificações -- devolucao, penalidade, cadastro da pessoa
    printf("4. Sair\n");
    while(1){
        printf("Digite sua opção: ");
        fgets(s_opcao, 3, stdin);
        if((s_opcao[0]=='1')||(s_opcao[0] == '2')||(s_opcao[0] == '3')||(s_opcao[0] == '4')){
            opcao = atoi(s_opcao[0]);
            return opcao;
        }
    }
}

int main(){
    //Data do dia
    int data_hoje[3];
    printf("Data de hoje\n");
    printf("Dia: ");
    scanf("%d", &data_hoje[0]);
    printf("Mes: ");
    scanf("%d", &data_hoje[1]);
    printf("Ano: ");
    scanf("%d", &data_hoje[2]);

    //Menu
    int opcao;
    opcao = menu();
    switch(opcao){
        case 1:
           t_cadastro

    }



    return 0;
}
