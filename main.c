//alloc a partir da contagem de caracteres de nome e dps strcpy

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define LIM 5

FILE *Arq;

typedef struct{
    char *nome; //[50]
    int num;
    int senha;
    int data_nasc[3];
    char *rua;//[20];
    int num_casa;
    char *complemento;//[20];
    char *bairro;//[20];
    char *cidade;//[30];
    char *estado;//[20];
    int qtd;
    int **data_empr; //[LIM][3]
    int **data_dev; // [LIM][3]
    char **nome_livro; //[LIM][40]
    char **nome_autor; //[LIM][50]
} t_cadastro;

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

void copia(char *temp, t_cadastro *usuario, int i, int opcao){
    int comprimento;
    comprimento = strlen(temp);
    switch(opcao){
        case 1:
           usuario[i].nome=(char*)malloc(comprimento*sizeof(char));
           strcpy(usuario[i].rua,temp);
            break;
        case 2:
            usuario[i].rua=(char*)malloc(comprimento*sizeof(char));
            strcpy(usuario[i].rua,temp);
            break;
        case 3:
            usuario[i].complemento=(char*)malloc(comprimento*sizeof(char));
            strcpy(usuario[i].complemento,temp);
            break;
        case 4:
            usuario[i].bairro=(char*)malloc(comprimento*sizeof(char));
            strcpy(usuario[i].bairro,temp);
            break;
        case 5:
            usuario[i].cidade=(char*)malloc(comprimento*sizeof(char));
            strcpy(usuario[i].cidade,temp);
            break;
        default:
            printf("Erro!\n");
            break;
    }
}

void cadastro(t_cadastro *usuario, int i){
    char temp[50];
    int senhatmp;
    if(i != 0)
        usuario = (t_cadastro*) realloc(usuario,(i+1)*sizeof(t_cadastro));

    printf("Nome: ");
    fgets(temp, 50, stdin);
    //chama funcao
    copia(temp, usuario, i, 1);

    printf("Numero de cadastro: %d", i+1);
    usuario[i].num= i+1;

    while(1){
        printf("Senha numérica: ");
        fgets(temp, 10, stdin);
        senhatmp= atoi(temp);
        printf("Digite a senha novamente: ");
        fgets(temp, 10, stdin);
        usuario[i].senha= atoi(temp);
        if(senhatmp == usuario[i].senha)
            break;
    }

    printf("Data de nascimento:\n");
    printf("Dia: ");
    fgets(temp, 5, stdin);
    usuario[i].data_nasc[0] = atoi(temp);
    printf("Mes: ");
    fgets(temp, 5, stdin);
    usuario[i].data_nasc[1] = atoi(temp);
    printf("Ano: ");
    fgets(temp, 5, stdin);
    usuario[i].data_nasc[2] = atoi(temp);

    printf("Endereco:\n");
    printf("Rua: ");
    fgets(temp, 50, stdin);
    copia(temp, usuario, i, 2);

    printf("Numero: ");
    fgets(temp, 5, stdin);
    usuario[i].num_casa=atoi(temp);

    printf("Complemento: ");
    fgets(temp, 50, stdin);
    copia(temp, usuario, i, 3);

    printf("Bairro: ");
    fgets(temp, 50, stdin);
    copia(temp, usuario, i, 4);

    printf("Cidade: ");
    fgets(temp, 50, stdin);
    copia(temp, usuario, i, 5);
}

void salva_cadastro(t_cadastro *usuario, int i){
    Arq=fopen("Arquivo.bin", "ab");
    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fprintf(Arq, "%s\n", usuario[i].nome);
        fprintf(Arq, "%d\n", usuario[i].num);
        fprintf(Arq, "%d\n", usuario[i].senha);
        fprintf(Arq, "%d/%d/%d\n", usuario[i].data_nasc[0],usuario[i].data_nasc[1],usuario[i].data_nasc[2]);
        fprintf(Arq, "%s\n", usuario[i].rua);
        fprintf(Arq, "%d\n", usuario[i].num_casa);
        fprintf(Arq, "%s\n", usuario[i].complemento);
        fprintf(Arq, "%s\n", usuario[i].bairro);
        fprintf(Arq, "%s\n", usuario[i].cidade);
        fprintf(Arq, "%s\n", usuario[i].estado);
        fprintf(Arq, "%d\n", usuario[i].qtd);
        fprintf(Arq, "%d\n", usuario[i].data_empr);
        fprintf(Arq, "%d\n", usuario[i].data_dev);
        fprintf(Arq, "%s\n", usuario[i].nome_livro);
        fprintf(Arq, "%s\n", usuario[i].nome_autor);
    }
    fclose(Arq);
}
void altera_cad(t_cadastro *usuario, int i){}

int verifica_cad(t_cadastro *usuario, int i){}
    //return 1 se tem cadastro

void emprestimo();

void confirma_senha();


int main(){
    int i = 0, p;
    Arq = fopen("Arquivo.dat","wb");
    t_cadastro *usuario;
    usuario = (t_cadastro*)malloc((i+1)*sizeof(t_cadastro));

    //Data do dia
    int data_hoje[3];
    printf("Data de hoje\n");
    printf("Dia: ");
    scanf("%d", &data_hoje[0]);
    printf("Mes: ");
    scanf("%d", &data_hoje[1]);
    printf("Ano: ");
    scanf("%d", &data_hoje[2]);
    int opcao;
    int j;
    //Menu
    while(1){
        opcao = menu();
        switch(opcao){
            case 1:
               cadastro(usuario, i);
               salva_cadastro(usuario, i);
               i++;
               break;
            case 2:
                p = verifica_cad(usuario, i);//funcao verifica se tem cadastro
                if (p==1){ //tem cadastro
                    //chama outra funcao que pede a senha

                }else{ //nao tem cadastro
                    cadastro(usuario,i);
                    salva_cadastro(usuario, i);
                    i++;
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
}
