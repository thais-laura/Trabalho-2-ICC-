#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define LIM 5
#define TAM_CAD 224
#define TAM_EMPR 670

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
    int qtd;
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
    char aux[3];
    int opcao;
    printf("\n\tBIBLIOTECA\n");
    printf("\t>>Menu<<\n");
    printf("1. Novo cadastro\n");
    printf("2. Emprestimo\n");
    printf("3. Busca de historico\n");
    printf("4. Sair\n");
    while(1){
        fflush(stdin);
        printf("Digite sua opcao: ");
        fgets(aux, 3, stdin);
        if((aux[0]=='1')||(aux[0] == '2')||(aux[0] == '3')||(aux[0] == '4')){
            opcao = atoi(aux);
            return opcao;
        }
    }
}

int verifica_cad(t_cadastro *usuario, int i, char temp[50], char *url_cad){
    int endereco, flag;
   	FILE *Arq = fopen(url_cad, "r+b");

    if (Arq == NULL) {
       // Arq = fopen(url_cad, "w+b");
        //if (Arq == NULL) {
            printf("Erro, nao foi possivel abrir o arquivo\n");
            return -1;
       // }
    }
    while(1){
        fread(usuario->nome, 50, 1, Arq);
        if(strcmp(temp, usuario->nome)==0){ //ou seja, sao iguais
            endereco = ftell(Arq); //indica onde está o nome no arquivo
            fclose(Arq);
            return endereco;
        }else{
            fseek(Arq, TAM_CAD-50, SEEK_CUR); //pula para o proximo cadastro -- ja estava no nome da pessoa de antes
            if(fread(&flag, 1, 1, Arq) == 0) //ver se o arquivo ja chegou ao fim
                break;
            else
                fseek(Arq, -1, SEEK_CUR); //volta 1 bytE
        }
    }
    fclose(Arq);
    return 0;

}

int cadastro(t_cadastro *usuario, int i, char *url_cad){
    char temp[50];
    int senhatemp;
    printf("Nome: ");
    fgets(temp, 50, stdin);
    int flag = verifica_cad(usuario, i, temp, url_cad);

    if(flag != 0){
        if(flag == -1){
            return -1; //arquivo nao aberto
        }else{
            printf("Ja existe um cadastro nesse nome\n"); //nao é necessario fazer cadastro
            return 1;
        }
    }else{ //não existe cadastro
        strcpy(usuario->nome,temp);

		usuario->num= i+100000;
        printf("Numero de cadastro: %d\n", usuario->num);

        //verifica senha
        while(1){
            printf("Senha numerica [pelo menos 4 algarismos]: ");
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
        fflush(stdin);
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

        printf("Estado: ");
        fgets(temp, 50, stdin);
        strcpy(usuario->estado,temp);
        return 0;
    }
}

void salva_cadastro(t_cadastro *usuario, char *url_cad){
    FILE *Arq=fopen(url_cad, "ab");
    int a;

    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        printf("nome: %s\nnumero: %d\nsenha: %d\n", usuario->nome, usuario->num, usuario->senha);

        a = fwrite(&usuario->nome, sizeof(char), 50, Arq);
        printf("devia sair 50 mas sai: %d\n", a);
        a = fwrite(&usuario->num, sizeof(int), 1, Arq);
        printf("devia sair 1 mas sai: %d\n", a);
        fwrite(&usuario->senha, sizeof(int), 1, Arq);
        fwrite(&usuario->data_nasc[0], sizeof(int), 1, Arq);
        fwrite(&usuario->data_nasc[1], sizeof(int), 1, Arq);
        fwrite(&usuario->data_nasc[2], sizeof(int), 1, Arq);
        fwrite(&usuario->rua, sizeof(usuario->rua), 1, Arq);
        fwrite(&usuario->num_casa, sizeof(int), 1, Arq);
        fwrite(&usuario->complemento, sizeof(usuario->complemento), 1, Arq);
        fwrite(&usuario->bairro, sizeof(usuario->bairro), 1, Arq);
        fwrite(&usuario->cidade, sizeof(usuario->cidade), 1, Arq);
        fwrite(&usuario->estado, sizeof(usuario->estado), 1, Arq);

    }
    fclose(Arq);
}

int confirma_senha(int endereco, char *url_cad){
    char aux[10];
    int senha1, senha2;
    FILE *Arq = fopen(url_cad, "rb");

    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fseek(Arq, endereco + sizeof(int), SEEK_SET);
        fread(&senha1, sizeof(int),1, Arq);
        while(1){
            printf("Confirme sua senha (digite 0 para sair): ");
            fgets(aux, 10, stdin);
            senha2 = atoi(aux);
            if(senha1 == senha2){
                fclose(Arq);
                return 1;
            }else if (senha2 == 0){ //sair da funcao
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

void devolucao(int dia, int mes, int ano, int *dia_dev, int *mes_dev, int *ano_dev){
    //limite de devolução vale 14 dias
    int dia_mes = 31;
    switch (mes){
        case 2: //fevereiro -- 28 dias
            dia_mes = dia_mes - 3;
            break;
        case 4: //abril
        case 6: //junho
        case 9: //setembro
        case 11: //novembro
            dia_mes--; //30 dias
            break;
    }
    if(dia +14 > dia_mes){ //se há mudanca de mes
        if(mes == 12){
            *ano_dev = ano++;
            *mes_dev = 1;
            *dia_dev = dia + 14 - dia_mes;
        }else{
            *ano_dev = ano;
            *mes_dev = mes++;
            *dia_dev = dia + 14 - dia_mes;
        }
    }else{ //continua no mesmo mês
        *ano_dev = ano;
        *mes_dev = mes;
        *dia_dev = dia + 14;
    }
}


int verifica_emprestimo(char nome[50], char *url_empr){
    t_emprestimo emprestimo;
    int flag;

    FILE *Arq = fopen(url_empr, "rb");

    if (Arq == NULL){
        printf("Erro ao abrir o arquivo de emprestimo\n");
        return -1;
    }else{
        while (1){
            fread(&emprestimo.nome, sizeof(char), 50, Arq);
            if (strcmp(nome, emprestimo.nome) == 0){
                fclose(Arq);
                return 1; //ja tem emprestimo, chama o altera emprestimo
            }else{
                fseek(Arq, TAM_EMPR - 50, SEEK_CUR); //le ate o proximo emprestimo
                if(fread(&flag, sizeof(char), 1, Arq) == 0) //ver se o arquivo ja chegou ao fim
                    return 0; //nao tem emprestimo
                else
                    fseek(Arq, -1, SEEK_CUR);
            }
        }
    }

    fclose(Arq);
    return 0;
}
void novo_emprestimo(t_cadastro usuario, int endereco, int dia, int mes, int ano, char *url_cad, char *url_empr){
    t_emprestimo emprestimo;
    int cont, dia_dev, mes_dev, ano_dev;
    FILE *Arq = fopen(url_cad, "rb");

    if(Arq == NULL){
        printf("Erro ao abrir o arquivo de cad\n");
    }else{
        fseek(Arq, endereco - 50, SEEK_SET); //vai até o fim do nome da pessoa e volta novamente para lê-lo
        fread(&emprestimo.nome, 50, 1, Arq);
        fread(&emprestimo.num, sizeof(int), 1, Arq);
    }
    fclose(Arq);


    Arq = fopen(url_empr, "ab");
    if(Arq == NULL){
        printf("Erro ao abrir o arquivo de empr\n");
    }else{
        printf("Digite a quantidade de livros a serem emprestados: ");
        scanf("%d", &emprestimo.qtd);
        while(emprestimo.qtd > LIM){
            printf("Erro: quantidade de livros acima da permitida\n");
            printf("Digite a quantidade de livros a serem emprestados: ");
            scanf("%d", &emprestimo.qtd);
        }
        for(cont = 0; cont < emprestimo.qtd; cont++){
            fflush(stdin);
            printf("Digite o nome do livro %d: ", cont+1);
            fgets(emprestimo.nome_livro[cont], 50, stdin);
            printf("Digite o nome do autor: ");
            fgets(emprestimo.nome_autor[cont], 50, stdin);
        }
        //salvar no arquivo nome, num de id e quantidade de livros
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
        for(cont=0; cont<LIM; cont++){
            fwrite(&dia, sizeof(int), 1, Arq);
            fwrite(&mes, sizeof(int), 1, Arq);
            fwrite(&ano, sizeof(int), 1, Arq);
            fwrite(&emprestimo.dia_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.mes_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.ano_dev[cont], sizeof(int), 1, Arq);
            fwrite(&emprestimo.nome_livro[cont], sizeof(emprestimo.nome_livro[cont]), 1, Arq);
            fwrite(&emprestimo.nome_autor[cont], sizeof(emprestimo.nome_autor[cont]), 1, Arq);
        }
    }
    fclose(Arq);
}

//adiciona os livros novos e altera a quantidade
void altera_emprestimo(int dia, int mes, int ano, char *url_empr){
    t_emprestimo emprestimo;
    int qtd, cont, dia_dev, mes_dev, ano_dev, flag;
    char livro[LIM-1][50],autor[LIM-1][50], nome[50];
    FILE *Arq = fopen(url_empr, "r+b");

    if(Arq == NULL ){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        printf("Digite o nome: ");
        fgets(nome, 50, stdin);
        printf("Digite a quantidade de livros: ");
        scanf("%d", &qtd);
        while(1){
            fread(emprestimo.nome, 50, 1, Arq);
            if(strcmp(nome, emprestimo.nome)==0){ //verifica se encontrou o nome
                fread(&emprestimo.num, sizeof(int), 1, Arq);
                fread(&emprestimo.qtd, sizeof(int), 1, Arq);

                //verfica multa
                flag=0;
                for (cont=0; cont < emprestimo.qtd; cont++){
                    fseek(Arq, 3*sizeof(int), SEEK_CUR);
                    fread(&emprestimo.dia_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.mes_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.ano_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.nome_livro[cont], sizeof(char), 50, Arq);
                    if(emprestimo.ano_dev[cont] < ano){
                        printf("%s esta atrasado\n", emprestimo.nome_livro[cont]);
                        flag++;
                    }else{
                        if(emprestimo.mes_dev[cont] < mes){
                            printf("%s esta atrasado\n ", emprestimo.nome_livro[cont]);
                            flag++;
                        }else{
                            if(emprestimo.dia_dev[cont] < dia){
                                printf("%s esta atrasado\n", emprestimo.nome_livro[cont]);
                                flag++;
                            }
                        }
                    }
                    fseek(Arq, 50*sizeof(char), SEEK_CUR);
                }
                if(flag != 0){
                    printf("Nao pode realizar emprestimos devido aos atrasos\n");
                    break;
                }

                while(qtd + emprestimo.qtd > LIM){
                    printf("Erro: quantidade acima da permitida\n");
                    printf("Digite a quantidade de livros (até %d): ",(LIM-emprestimo.qtd));
                    scanf("%d", &qtd);
                }
                for(cont=0;cont<qtd;cont++){ //nomes dos novos livros a serem adicionados
                    fflush(stdin);
                    printf("Digite o nome do livro %d: ",cont+1);
                    fgets(livro[cont],50,stdin);
                    printf("Digite o nome do autor do livro %d: ",cont+1);
                    fgets(autor[cont],50,stdin);
                }

                devolucao(dia, mes, ano, &dia_dev, &mes_dev, &ano_dev);//saber os dias finais dos livros novos
                for(cont=emprestimo.qtd; cont < LIM; cont++){
                    emprestimo.dia_dev[cont]=dia_dev;
                    emprestimo.mes_dev[cont]=mes_dev;
                    emprestimo.ano_dev[cont]=ano_dev;
                }

                for(cont=0; cont < qtd; cont++){
                    fwrite(&dia, sizeof(int), 1, Arq);
                    fwrite(&mes, sizeof(int), 1, Arq);
                    fwrite(&ano, sizeof(int), 1, Arq);
                    fwrite(&emprestimo.dia_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(&emprestimo.mes_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(&emprestimo.ano_dev[cont+emprestimo.qtd], sizeof(int), 1, Arq);
                    fwrite(&livro[cont], 50*sizeof(char), 1, Arq);
                    fwrite(&autor[cont], 50*sizeof(char), 1, Arq);
                }
                //mudança na quantidade de livros
                emprestimo.qtd += qtd;
                fseek(Arq, -1*emprestimo.qtd*(6*sizeof(int)+sizeof(emprestimo.nome_livro)+sizeof(emprestimo.nome_autor)), SEEK_CUR);
                fseek(Arq, -(long)sizeof(int), SEEK_CUR);
                fwrite(&emprestimo.qtd, sizeof(int), 1, Arq);

            }else{ //nao achou o nome
                fseek(Arq, TAM_CAD - 50, SEEK_CUR); //le ate o proximo emprestimo
                if(fread(&flag, 1, 1, Arq) == 0) //ver se o arquivo ja chegou ao fim
                    break;
                else
                    fseek(Arq, -1, SEEK_CUR);
            }
        }
    fclose(Arq);
    }
}

void imprimir_emprestimo(char nome[50], char *url_empr){
    t_emprestimo emprestimo;
    char flag;
    int cont;
    FILE *Arq = fopen(url_empr, "r+b");

    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        while(1){
            fread(&emprestimo.nome, 50, 1, Arq);
            if(strcmp(nome, emprestimo.nome)==0){ //iguais
                //ler arquivo
                fread(&emprestimo.num, sizeof(int), 1, Arq);
                fread(&emprestimo.qtd, sizeof(int), 1, Arq);
                for(cont=0; cont < emprestimo.qtd; cont++){ //nao le o lixo (se tiver)
                    fread(&emprestimo.dia_empr[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.mes_empr[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.ano_empr[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.dia_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.mes_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.ano_dev[cont], sizeof(int), 1, Arq);
                    fread(&emprestimo.nome_livro[cont], 50, 1, Arq);
                    fread(&emprestimo.nome_autor[cont], 50, 1, Arq);
                }

                //printa na tela
                printf("Quantidade de livros: %d\n", emprestimo.qtd);
                for(cont=0; cont < emprestimo.qtd; cont++){
                    printf("Livro %d:Data de emprestimo: %d/%d/%d\n",cont+1, emprestimo.dia_empr[cont], emprestimo.mes_empr[cont], emprestimo.ano_empr[cont]);
                    printf("Livro %d:Data de devolucao: %d/%d/%d\n",cont+1, emprestimo.dia_dev[cont], emprestimo.mes_dev[cont], emprestimo.ano_dev[cont]);
                    printf("Livro %d: %s, %s\n", cont+1, emprestimo.nome_livro[cont], emprestimo.nome_autor[cont]);
                }
                break;
            }else{ //nao achou o nome
                fseek(Arq, TAM_CAD - 50, SEEK_CUR); //le ate o proximo emprestimo
                if(fread(&flag, 1, 1, Arq) == 0){ //ver se o arquivo ja chegou ao fim
                    fclose(Arq);
                    break;
                }else
                    fseek(Arq, -1, SEEK_CUR);
            }
        }
    }
}

void imprimir_cadastro(char *url_cad, char *url_empr){
    t_cadastro usuario;
    char nome[50], flag;

    FILE *Arq = fopen(url_cad, "rb");
    if(Arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{
        printf("Digite o nome a ser procurado: ");
        fgets(nome, 50, stdin);

        while(1){
            fread(usuario.nome, 50, 1, Arq);
            if(strcmp(nome, usuario.nome)==0){ //ou seja, sao iguais
                    //le a struct
                fread(&usuario.num, sizeof(int), 1, Arq);
                fseek(Arq, sizeof(int), SEEK_CUR);
                fread(&usuario.data_nasc[0], sizeof(int), 1, Arq);
                fread(&usuario.data_nasc[1], sizeof(int), 1, Arq);
                fread(&usuario.data_nasc[2], sizeof(int), 1, Arq);
                fread(&usuario.rua, 40, 1, Arq);
                fread(&usuario.num_casa, sizeof(int), 1, Arq);
                fread(&usuario.complemento, 20, 1, Arq);
                fread(&usuario.bairro, 40, 1, Arq);
                fread(&usuario.cidade, 30, 1, Arq);
                fread(&usuario.estado, 20, 1, Arq);
                    //printa na tela
                printf("Nome: %s\n", usuario.nome);
                printf("Numero de cadastro: %d\n", usuario.num);
                printf("Data de nascimento: %d/%d/%d\n", usuario.data_nasc[0], usuario.data_nasc[1], usuario.data_nasc[2]);
                printf("Rua %s numero %d, %s", usuario.rua, usuario.num_casa, usuario.complemento);
                printf("Bairro: %s\n", usuario.bairro);
                printf("Cidade: %s\n", usuario.cidade);
                printf("Estado: %s\n", usuario.estado);
                fclose(Arq);

                imprimir_emprestimo(usuario.nome, url_empr);
                break;
            }else{
                fseek(Arq, TAM_CAD-50, SEEK_CUR); //pula para o proximo cadastro -- ja estava no nome da pessoa de antes
                if(fread(&flag, 1, 1, Arq) == 0) //ver se o arquivo ja chegou ao fim
                    break;
                else
                    fseek(Arq, -1, SEEK_CUR); //volta 1 byte
            }
        }
    }
}



int main(){
	char *url_cad = "Cadastro.bin";
	char *url_empr = "Emprestimo.bin";
	char nome[50];
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

    FILE *Arq = fopen(url_cad, "rb");
    if (Arq == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo de cadastro\n");
        return -1;
    }
    fclose(Arq);

    Arq = fopen(url_empr, "rb");
    if (Arq == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo de emprestimo\n");
        return -1;
    }
    fclose(Arq);


    while(1){
        opcao = menu();
        switch(opcao){
            case 1: //cadastro
                flag = cadastro(&usuario, i, url_cad);
                if(flag == 0){ //nao tinha cadastro mas fez
                    salva_cadastro(&usuario, url_cad);
                    i++;
                }
                break;

            case 2: //emprestimo
                fflush(stdin);
                printf("Nome: ");
                fgets(nome, 50, stdin);
                endereco = verifica_cad(&usuario, i, nome, url_cad);//funcao verifica se tem cadastro
                if(endereco !=0 && endereco !=(-1)){ //tem cadastro
                    //chama outra funcao que pede a senha
                    printf("a pessoa tem cadastro!!\n");
                    if(confirma_senha(endereco, url_cad)){ //tem cadastro e confirmou a senha -- pode fazer o emprestimo
                    //verificar se ja tem nome no arquivo de emprestimo
                        printf("Confirmou senha!!!\n");
                        if(verifica_emprestimo(nome, url_empr)==0){//nao tem emprestimo
                            printf("ainda n tem emprestimo...\n");
                            novo_emprestimo(usuario, endereco, dia, mes, ano, url_cad, url_empr);
                            break;
                        }else if(verifica_emprestimo(nome, url_empr)==1){ //se nome existir, chama o altera_emprestimo
                            printf("tem emprestimo!\n");
                            altera_emprestimo(dia, mes, ano, url_empr);
                            break;
                        }
                        break;
                    }else//saiu sem preencher a senha
                        break;
                }else if(endereco == 0){ //nao tem cadastro
                    printf("Nao existe cadastro\n");
                    break;
                }

            case 3: //busca historico --
                imprimir_cadastro(url_cad, url_empr);
                break;
            case 4:
                return 0;
        }

    }

    return 0;
}
