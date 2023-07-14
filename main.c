#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define LIM 5
#define TAM_CAD 224
#define TAM_EMP 670

FILE *Arq;

typedef struct{
    char nome[50];
    int num;
    int senha;
    int data_nasc[3];
    char rua[40];
    int num_casa;
    char complemento[20];
    char bairro[40];
    char cidade[30];
    char estado[20];
} t_cadastro;

typedef struct{
    char nome[50];
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
    printf("2. Empr stimo\n");
    printf("3. Busca de hist rico\n"); //trocar nome -- busca de hist rico
        //1. levar  s verifica  es -- devolucao, penalidade, cadastro da pessoa
    printf("4. Sair\n");
    while(1){
        printf("Digite sua op  o: ");
        fgets(s_opcao, 3, stdin);
        if((s_opcao[0]=='1')||(s_opcao[0] == '2')||(s_opcao[0] == '3')||(s_opcao[0] == '4')){
            opcao = atoi(s_opcao);
            return opcao;
        }
    }
}

int verifica_cad(t_cadastro *usuario, int i){
    int endereco;
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
        fread(aux, sizeof(temp), 1, Arq);
        if(strcmp(aux, temp)== 0){ //quer dizer que achamos o nome de cadastro
            endereco = ftell(Arq);
            fclose(Arq);
            return endereco;
        }else{
            fseek(Arq,TAM_CAD-50,SEEK_CUR);
        }
    }
    fclose(Arq);
    return 0;

}

int cadastro(t_cadastro *usuario, int i){
    char temp[50];
    int senhatemp;
    int flag = verifica_cad(usuario, i);
    // 1. se der 0 -- nao tem cadastro -- pode continuar a funcao de cadastro
    // 2. se der -1 -- arquivo nao abriu -- sair de qualquer jeito
    // 3. se der diferente dos dois -- tem cadastro -- mensagem -- sai
    if(flag != 0){
        if(flag == -1){
            return -1;
        }else{
            printf("Ja existe um cadastro nesse nome\n");
            return 1;
        }
    }else{
        printf("Nome: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->nome,temp);

        printf("Numero de cadastro: %d", i+1);
        usuario->num= i+100000;

        //verifica  o da senha
        while(1){
            printf("Senha num rica: ");
            fgets(temp, 10, stdin);
            senhatemp = atoi(temp);
            //converte string para inteiro
            while(senhatemp < 1000){
                printf("Digite uma senha de pelo menos 4 algarismos\n");
                printf("Senha numerica: ");
                fgets(temp, 10, stdin);
                senhatemp = atoi(temp);
            }
            printf("Digite a senha novamente: ");
            fgets(temp, 10, stdin);
            usuario->senha= atoi(temp);
            if(senhatemp == usuario->senha)
                break;
        }

        printf("Data de nascimento:\n");
        printf("Dia: ");
        fgets(temp, 5, stdin);
        usuario->data_nasc[0] = atoi(temp);
        printf("Mes: ");
        fgets(temp, 5, stdin);
        usuario->data_nasc[1] = atoi(temp);
        printf("Ano: ");
        fgets(temp, 5, stdin);
        usuario->data_nasc[2] = atoi(temp);

        printf("Endereco:\n");
        printf("Rua: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->rua,temp);

        printf("Numero: ");
        fgets(temp, 5, stdin);
        usuario->num_casa=atoi(temp);

        printf("Complemento: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->complemento,temp);

        printf("Bairro: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->bairro,temp);

        printf("Cidade: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->cidade,temp);
        return 0;
    }
}

void salva_cadastro(t_cadastro *usuario){
    int tamanho,tam_total;
    Arq=fopen("Cadastro.bin", "ab");
    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fwrite(usuario->nome, sizeof(usuario->nome), 1, Arq);
        fwrite(usuario->num, sizeof(int), 1, Arq);
        fwrite(usuario->senha, sizeof(int), 1, Arq);
        fwrite(usuario->data_nasc[0], sizeof(int), 1, Arq);
        fwrite(usuario->data_nasc[1], sizeof(int), 1, Arq);
        fwrite(usuario->data_nasc[2], sizeof(int), 1, Arq);
        fwrite(usuario->rua, sizeof(usuario->rua), 1, Arq);
        fwrite(usuario->num_casa, sizeof(int), 1, Arq);
        fwrite(usuario->complemento, sizeof(usuario->complemento), 1, Arq);
        fwrite(usuario->bairro, sizeof(usuario->bairro), 1, Arq);
        fwrite(usuario->cidade, sizeof(usuario->cidade), 1, Arq);
        fwrite(usuario->estado, sizeof(usuario->estado), 1, Arq);

    }
    fclose(Arq);
}
void devolucao(int dia, int mes, int ano, int *dia_dev, int *mes_dev, int *ano_dev){
    int dias;
    dias = 31;
    switch (mes){
        case 2:
            dias = dias - 3;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            dias--;
            break;

    }
}

void altera_emprestimo(t_emprestimo emprestimo, int i, int dia, int mes, int ano){
    int qtd, cont=0, tam_total, tam_nome, dia_dev, mes_dev, ano_dev;
    char livro[4][50],autor[4][50], nome[50];
    Arq = fopen("Emprestimo.bin", "r+b");

     if(Arq == NULL ){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        printf("Digite o nome: ");
        fgets(nome, 50, stdin);
        printf("Digite a quantidade de livros: ");
        scanf("%d", &qtd);
        while(1){
            fread(emprestimo.nome, 50, 1, Arq);
            if(strcmp(nome, emprestimo.nome)==0){ //adiciona os livros novos e altera a quantidade
                fread(&emprestimo.num, sizeof(int), 1, Arq);
                fread(&emprestimo.qtd, sizeof(int), 1, Arq);
                while(qtd + emprestimo.qtd > LIM){
                    printf("Erro: quantidade acima da permitida\n");
                    printf("Digite a quantidade de livros:(até %d):",(LIM-emprestimo.qtd));
                    scanf("%d", &qtd);
                }
                for(cont=0;cont<qtd;cont++){
                    printf("Digite o nome do livro %d: ",cont);
                    fgets(nome[cont],50,stdin);
                    printf("Digite o nome do autor do livro %d: ",cont);
                    fgets(autor[cont],50,stdin);
                }
                devolucao(dia,mes,ano,dia_dev,mes_dev,ano_dev);//saber os dias finais dos livros novos
                for(cont=emprestimo.qtd;cont < LIM; cont++){
                    emprestimo.dia_dev[cont]=dia_dev;
                    emprestimo.mes_dev[cont]=mes_dev;
                    emprestimo.ano_dev[cont]=ano_dev;
                }
                //deslocar até os slots de livros não preenchidos
                fseek(Arq,emprestimo.qtd*(6*sizeof(int)+sizeof(emprestimo.nome_livro)+sizeof(emprestimo.nome_autor)),SEEK_CUR);
                for(cont=0; cont < qtd; cont++){
                    fwrite(&dia, sizeof(int), 1, Arq);
                    fwrite(&mes, sizeof(int), 1, Arq);
                    fwrite(&ano, sizeof(int), 1, Arq);
                    fwrite(&emprestimo.dia_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(&emprestimo.mes_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(&emprestimo.ano_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(nome[cont], 50*sizeof(char), 1, Arq);
                    fwrite(autor[cont], 50*sizeof(char), 1, Arq);
                }
            }
        }
    fclose(Arq);
    }
}


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


void novo_emprestimo(t_cadastro usuario, int endereco, int dia, int mes, int ano){
    t_emprestimo emprestimo;
    int tam_emprestimo, tam_livro[LIM], cont, dia_dev,mes_dev,ano_dev;
    Arq = fopen("Cadastro.bin", "rb");

    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        fseek(Arq, endereco - 50, SEEK_SET);
        fread(emprestimo.nome, 50, 1, Arq);
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
            fgets(emprestimo.nome_livro[cont], 50, stdin);
            printf("Digite o nome do autor: ");
            fgets(emprestimo.nome_autor[cont], 50, stdin);
        }
        //salvar no arquivo tamanhos e a propria struct
        fwrite(&emprestimo.nome, sizeof(emprestimo.nome), 1, Arq);
        fwrite(&emprestimo.num, sizeof(int), 1, Arq);
        fwrite(&emprestimo.qtd, sizeof(int), 1,Arq);

        //saber o dia da devolucao
        devolucao(dia, mes, ano, &dia_dev, &mes_dev, &ano_dev);
        for(cont = 0; cont < emprestimo.qtd; cont++){
            emprestimo.dia_dev[cont]=dia_dev;
            emprestimo.mes_dev[cont]=mes_dev;
            emprestimo.ano_dev[cont]=ano_dev;
        }
        //reservar o espaço no binario de uma vez para LIM*livros
        for(cont=0;cont<LIM;cont++){
            fwrite(dia, sizeof(int), 1, Arq);
            fwrite(mes, sizeof(int), 1, Arq);
            fwrite(ano, sizeof(int), 1, Arq);
            fwrite(&emprestimo.dia_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.mes_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.ano_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.nome_livro[cont], sizeof(emprestimo.nome_livro[cont]), 1, Arq);
            fwrite(&emprestimo.nome_autor[cont], sizeof(emprestimo.nome_autor[cont]), 1, Arq);
        }
    }
    fclose(Arq);
}

void ler_cadastro(){
    t_cadastro usuario;
    char nome[50], flag;

    Arq = fopen("Cadastro.bin", "rb");
    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        printf("Digite o nome a ser procurado: ");
        fgets(nome, 50, stdin);
        while(1){

            fread(usuario.nome, 50, 1, Arq);
            if(strcmp(nome, usuario.nome)==0){ //ou seja, sao iguais
                    //le a struct
                fread(usuario.num, sizeof(int), 1, Arq);
                fseek(Arq, sizeof(int), SEEK_CUR);
                fread(usuario.data_nasc[0], sizeof(int), 1, Arq);
                fread(usuario.data_nasc[1], sizeof(int), 1, Arq);
                fread(usuario.data_nasc[2], sizeof(int), 1, Arq);
                fread(usuario.rua, 40, 1, Arq);
                fread(usuario.num_casa, sizeof(int), 1, Arq);
                fread(usuario.complemento, 20, 1, Arq);
                fread(usuario.bairro, 40, 1, Arq);
                fread(usuario.cidade, 30, 1, Arq);
                fread(usuario.estado, 20, 1, Arq);
                    //printa na tela
                printf("Nome: %s\n", usuario.nome);
                printf("Numero de cadastro: %d\n", usuario.num);
                printf("Data de nascimento: %d/%d/%d\n", usuario.data_nasc[0], usuario.data_nasc[1], usuario.data_nasc[2]);
                printf("Rua %s,%d, %s", usuario.rua, usuario.num_casa, usuario.complemento);
                printf("Bairro: %s\n", usuario.bairro);
                printf("Cidade: %s\n", usuario.cidade);
                printf("Estado: %s\n", usuario.estado);
                fclose(Arq);
                ler_emprestimo(nome);
                break;
            }else{
                fseek(Arq, TAM_CAD-50, SEEK_CUR);
                if(fread(flag, 1, 1, Arq) == 0) //ver se o arquivo j  chegou ao fim
                    break;
                else
                    fseek(Arq, -1, SEEK_CUR);
            }
        }
    }
}

void ler_emprestimo(char nome){
    t_emprestimo emprestimo;
    char flag;
    int cont;
    Arq = fopen("Emprestimo.bin", "rb");
    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        while(1){
            fread(emprestimo.nome, 50, 1, Arq);
            if(strcmp(nome, emprestimo.nome)==0){ //iguais
                //ler arquivo
                fread(emprestimo.qtd, sizeof(int), 1, Arq);
                for(cont=0; cont < emprestimo.qtd; cont++){
                    fread(emprestimo.dia_empr[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.mes_empr[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.ano_empr[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.dia_dev[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.mes_dev[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.ano_dev[cont], sizeof(int), 1, Arq);
                    fread(emprestimo.nome_livro[cont], 50, 1, Arq);
                    fread(emprestimo.nome_autor[cont], 50, 1, Arq);
                }

                //printa na tela
                printf("Quantidade de livros: %d\n", emprestimo.qtd);
                for(cont=0; cont < emprestimo.qtd; cont++){
                    printf("Livro %d:Data de emprestimo: %d/%d/%d\n",cont+1, emprestimo.dia_empr[cont], emprestimo.mes_empr[cont], emprestimo.ano_empr[cont]);
                    printf("Livro %d:Data de devolucao: %d/%d/%d\n",cont+1, emprestimo.dia_dev[cont], emprestimo.mes_dev[cont], emprestimo.ano_dev[cont]);
                    printf("Livro %d: %s, %s\n", cont+1, emprestimo.nome_livro[cont], emprestimo.nome_autor[cont]);
                }
                break;
            }else{
                fseek(Arq, TAM_CAD - 50, SEEK_CUR);
                if(fread(flag, 1, 1, Arq) == 0) //ver se o arquivo j  chegou ao fim
                    break;
                else
                    fseek(Arq, -1, SEEK_CUR);
            }
        }
    }
}


int main(){
    int i = 0, endereco, flag; //se fechar o programa e rodar de novo, i volta a ser zero e atrapalha o for de verifica cadastro --
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

    while(1){
        opcao = menu();
        switch(opcao){
            case 1: //cadastro
                flag = cadastro(&usuario, i);
                if(flag == 0){ //nao tinha cadastro mas fez
                    salva_cadastro(&usuario);
                    i++;
                }
                break;

            case 2: //emprestimo
                endereco = verifica_cad(&usuario, i);//funcao verifica se tem cadastro
                if(endereco !=0 && endereco !=(-1)){ //tem cadastro
                    //chama outra funcao que pede a senha
                    if(confirma_senha(endereco)){ //tem cadastro e confirmou a senha -- pode fazer o emprestimo
                        novo_emprestimo(usuario, endereco, dia, mes, ano);
                        break;
                    }else{
                        break;
                    }
                }else if(endereco == 0){ //nao tem cadastro
                    printf("Nao existe cadastro\n");
                    break;
                }

            case 3: //busca historico --
                ler_cadastro();
            case 4:
                return 0;
        }

    }

    return 0;
}
