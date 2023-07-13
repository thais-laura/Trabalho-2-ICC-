//alloc a partir da contagem de caracteres de nome e dps strcpy

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define LIM 5

FILE *Arq;

typedef struct{
    char nome[50];
    int num;
    int senha;
    int data_nasc[3];
    char rua[40];
    int num_casa;
    char complementO[20];
    char bairro[40];
    char cidade[30];
    char estadO[20];
} t_cadastro;

typedef struct{
    char *nome;
    int num;
    int qtd; // ver se precisa mesmo dessa variavel
    char *nome;
    int num;
    int qtd; // ver se precisa mesmo dessa variavel
    int dia_empr[LIM];
    int mes_empr[LIM];
    int ano_empr[LIM];
    int dia_dev[LIM];
    int mes_dev[LIM];
    int ano_dev[LIM];
    char nome_livro[LIM][50];
    char nome_autor[LIM][50];
}t_emprestimo;

int menu(){
    char s_opcao[3];
    int opcao;
    printf("\tBIBLIOTECA\n");
    printf("\t>>Menu<<\n");
    printf("1. Novo cadastro\n");
    printf("2. Empréstimo\n");
    printf("3. Busca de histórico\n"); //trocar nome -- busca de histórico
        //1. levar às verificações -- devolucao, penalidade, cadastro da pessoa
    printf("4. Sair\n");
    while(1){
        printf("Digite sua opção: ");
        fgets(s_opcao, 3, stdin);
        if((s_opcao[0]=='1')||(s_opcao[0] == '2')||(s_opcao[0] == '3')||(s_opcao[0] == '4')){
            opcao = atoi(s_opcao);
            return opcao;
        }
    }
}

void cadastro(t_cadastro *usuario, int i){
    char temp[50];
    int senhatemp;

    printf("Nome: ");
    fgets(temp, 50, stdin);
    strcpy(usuario.nome,temp);

    printf("Numero de cadastro: %d", i+1);
    usuario.num= i+100000;

    //verificação da senha
    while(1){
        printf("Senha numérica: ");
        fgets(temp, 10, stdin);
        senhatemp = atoi(temp);
        //converte string para inteiro
        while(senhatemp < 1000){
            printf("Digite uma senha de pelo menos 4 algarismos\n");
            printf("Senha numérica: ");
            fgets(temp, 10, stdin);
            senhatemp = atoi(temp);
        }
        printf("Digite a senha novamente: ");
        fgets(temp, 10, stdin);
        usuario.senha= atoi(temp);
        if(senhatemp == usuario.senha)
            break;
    }

    printf("Data de nascimento:\n");
    printf("Dia: ");
    fgets(temp, 5, stdin);
    usuario.data_nasc[0] = atoi(temp);
    printf("Mes: ");
    fgets(temp, 5, stdin);
    usuario.data_nasc[1] = atoi(temp);
    printf("Ano: ");
    fgets(temp, 5, stdin);
    usuario.data_nasc[2] = atoi(temp);

    printf("Endereco:\n");
    printf("Rua: ");
    fgets(temp, 50, stdin);
    strcpy(usuario.rua,temp);

    printf("Numero: ");
    fgets(temp, 5, stdin);
    usuario.num_casa=atoi(temp);

    printf("Complemento: ");
    fgets(temp, 50, stdin);
    strcpy(usuario.complementO,temp);

    printf("Bairro: ");
    fgets(temp, 50, stdin);
    strcpy(usuario.bairro,temp);

    printf("Cidade: ");
    fgets(temp, 50, stdin);
    strcpy(usuario.cidade,temp);
}

void salva_cadastro(t_cadastro *usuario, int *tam_total, int *tam_nome){
    int tamanho;
    Arq=fopen("Cadastro.bin", "ab");
    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        *tam_total = sizeof(usuario);
        fwrite(tam_total, sizeof(int), 1, Arq); //quantidade de bytes para cada struct de usuario
        *tam_nome = sizeof(usuario.nome);
        fwrite(tam_nome, sizeof(int), 1, Arq); //quantidade de bytes para nome do usuario

        fwrite(usuario.nome, sizeof(usuario.nome), 1, Arq); //1
        fwrite(usuario.num, sizeof(int), 1, Arq);
        fwrite(usuario.senha, sizeof(int), 1, Arq);
        fwrite(usuario.data_nasc[0], sizeof(int), 1, Arq);
        fwrite(usuario.data_nasc[1], sizeof(int), 1, Arq);
        fwrite(usuario.data_nasc[2], sizeof(int), 1, Arq);
        fwrite(usuario.rua, sizeof(usuario.rua), 1, Arq);
        fwrite(usuario.num_casa, sizeof(int), 1, Arq);
        fwrite(usuario.complemento, sizeof(usuario.complemento), 1, Arq);
        fwrite(usuario.bairro, sizeof(usuario.bairro), 1, Arq);
        fwrite(usuario.cidade, sizeof(usuario.cidade), 1, Arq);
        fwrite(usuario.estado, sizeof(usuario.estado), 1, Arq);
    }
    fclose(Arq);
}

int verifica_cad(t_cadastro *usuario, int i, int *tam_total, int *tam_nome){
    int a, b, endereco;
    Arq=fopen("Cadastro.bin", "rb");
    int cont;
    char temp[50], aux[50];

    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        return -1;
    }

    printf("Nome: ");
    fgets(temp, 50, stdin);

    for(cont=0; cont<i; cont++) {
        fread(tam_total, sizeof(int), 1, Arq);
        a = ftell(Arq);
        fread(tam_nome, sizeof(int), 1, Arq);
        b = ftell(Arq);
        if(a == b)
            printf("NAO DESLOCOUUUUU\n");
        fread(aux, sizeof(temp), 1, Arq);
        if(strcmp(aux, temp)==0){
            endereco = ftell(Arq);
            fclose(Arq);
            return endereco;
        }else{
            fseek(Arq, (*tam_total - *tam_nome), SEEK_CUR);
        }
    }
    fclose(Arq);
    return 0;

}

void altera_cad(t_cadastro *usuario, int i){

}

void emprestimo(t_cadastro *usuario, int endereco, int tam_nome, int dia, int mes, int ano){
    int tam_emprestimo, tam_livro[LIM], cont;
    Arq = fopen("Cadastro.bin", "rb");

    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        fseek(Arq, endereco - tam_nome, SEEK_SET);
        fread(emprestimo.nome, tam_nome, 1, Arq);
        fread(emprestimo.num, sizeof(int), 1, Arq);
    }
    fclose(Arq);

    Arq = fopen("Emprestimo.bin", "ab");
    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        printf("Digite a quantidade de livros a serem emprestados: ");
        scanf("%d", &emprestimo.qtd);
        while(emprestimo.qtd > LIM){
            printf("Erro: quantidade de livros acima da permitida\n");
            printf("Digite a quantidade de livros a serem emprestados: ");
            scanf("%d", &emprestimo.qtd);
        }
        for(cont = 0; cont < emprestimo.qtd; cont++){
            printf("Digite o nome do livro %d: ", cont+1);
            fgets(emprestimo.livro[cont], 50, stdin);
            printf("Digite o nome do autor: ");
            fgets(emprestimo.autor[cont], 50, stdin);
        }

        //salvar no arquivo tamanhos e a propria struct
        tam_emprestimo = sizeof(emprestimo);
        fwrite(&tam_emprestimo, sizeof(int), 1, Arq); //quantidade de bytes para cada struct de emprestimo
        fwrite(&tam_nome, sizeof(int), 1, Arq);
        fwrite(&emprestimo.nome, sizeof(emprestimo.nome), 1, Arq);
        fwrite(&emprestimo.num, sizeof(int), 1, Arq);
        fwrite(&emprestimo.qtd, sizeof(int), 1, Arq);

        fwrite(data_hoje[0], sizeof(int), 1, Arq);
        fwrite(data_hoje[1], sizeof(int), 1, Arq);
        fwrite(data_hoje[2], sizeof(int), 1, Arq);

        //saber o dia da devolucao
        devolucao(dia, mes, ano, &emprestimo.dia_dev, &emprestimo.mes_dev, &emprestimo.ano_dev);
        fwrite(&emprestimo.dia_dev, sizeof(int), 1, Arq);
        fwrite(&emprestimo.mes_dev, sizeof(int), 1, Arq);
        fwrite(&emprestimo.ano_dev, sizeof(int), 1, Arq);

        for(cont=0; cont < emprestimo.qtd; cont++){
            tam_livro[cont] = sizeof(emprestimo.livro[cont]);
            fwrite(&tam_livro[cont], sizeof(int), 1, Arq); //quantidade de bytes para nome do livro
            fwrite(&emprestimo.livro[cont], sizeof(emprestimo.livro[cont]), 1, Arq);
        }
    }
    fclose(Arq);
}
endereco == posicao depois do nome -- está no id do cadastro
no confirma senha -- pula um inteiro
emprestimo == voltar pro nome
volta um nome

int confirma_senha(int endereco){
    char aux[10];
    int senha1, senha2;
    Arq = fopen("Cadastro.bin", "rb");

    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fseek(Arq, endereco + sizeof(int), SEEK_SET);
        fread(senha1, sizeof(int),1, Arq);
        while(1){
            printf("Confirme sua senha (digite 0 para sair): ");
            fgets(aux, 10, stdin);
            senha2 = atoi(aux);
            if(senha1 == senha2){
                fclose(Arq);
                return 1;
            }else if (senha2 == 0){
                fclose(Arq);
                return 0;
            }else{
                printf("Senha incorreta\n");
            }
        }
    }
    fclose(Arq);
    return 0;

}


int main(){
    int i = 0, endereco, tam_total, tam_nome; //se fechar o programa e rodar de novo, i volta a ser zero e atrapalha o for de verifica cadastro --
    //pensar em outra solucao para isso
    int dia, mes, ano;

    t_cadastro usuario;

    //Data do dia

    printf("Data de hoje\n");
    printf("Dia: ");
    scanf("%d", &dia);
    printf("Mes: ");
    scanf("%d", &mes);
    printf("Ano: ");
    scanf("%d", &ano);
    int opcao;

    //Menu
    while(1){
        opcao = menu();
        switch(opcao){
            case 1:
               cadastro(&usuario, i);
               salva_cadastro(&usuario, i, &tam_total, &tam_nome);
               i++;
               break;
            case 2:
                endereco = verifica_cad(&usuario, i, &tam_total, &tam_nome);//funcao verifica se tem cadastro
                if(endereco !=0 && endereco !=(-1)){ //tem cadastro
                    //chama outra funcao que pede a senha
                    if(confirma_senha(endereco)){ //tem cadastro e confirmou a senha -- pode fazer o emprestimo
                        emprestimo(&usuario, endereco, tam_nome, dia, mes, ano);
                        break;
                    }else{
                        break;
                    }
                }else if(p == 0){ //nao tem cadastro
                    printf("Nao existe cadastro\n");
                    break;
                }
            case 3: //busca historico --
                //Funcao: percorre_arq
                // Funcao: printa na tela
                //arquivos -- printar na tela todas as informacoes da pessoa
                //ver como procurar nome ou numero da cadastro da pessoa no arquivo unico
            case 4:
                return 0;
        }

    }

    return 0;





    acha o nome q quer modificar
    fwrite ""
    fseek -1

}
