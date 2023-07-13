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
    copia(temp, usuario, i, 1);

    printf("Numero de cadastro: %d", i+1);
    usuario[i].num= i+100000;

    //verificação da senha
    while(1){
        printf("Senha numérica: ");
        fgets(temp, 10, stdin);
        senhatmp= atoi(temp); //converte string para inteiro
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
        fwrite(usuario[i].nome, sizeof(usuario[i].nome), 1, Arq); //1
        fwrite(usuario[i].num, sizeof(int), 1, Arq);
        fwrite(usuario[i].senha, sizeof(int), 1, Arq);
        fwrite(usuario[i].data_nasc[0], sizeof(int), 1, Arq);
        fwrite(usuario[i].data_nasc[1], sizeof(int), 1, Arq);
        fwrite(usuario[i].data_nasc[2], sizeof(int), 1, Arq);
        fwrite(usuario[i].rua, sizeof(usuario[i].rua), 1, Arq);
        fwrite(usuario[i].num_casa, sizeof(int), 1, Arq);
        fwrite(usuario[i].complemento, sizeof(usuario[i].complemento), 1, Arq);
        fwrite(usuario[i].bairro, sizeof(usuario[i].bairro), 1, Arq);
        fwrite(usuario[i].cidade, sizeof(usuario[i].cidade), 1, Arq);
        fwrite(usuario[i].estado, sizeof(usuario[i].estado), 1, Arq);
        fwrite(usuario[i].qtd, sizeof(int), 1, Arq);
        fwrite(usuario[i].data_empr[0],sizeof(int), 1, Arq);
        fwrite(usuario[i].data_empr[1],sizeof(int), 1, Arq);
        fwrite(usuario[i].data_empr[2],sizeof(int), 1, Arq);
        fwrite(usuario[i].data_dev[0], sizeof(int), 1, Arq);
        fwrite(usuario[i].data_dev[1], sizeof(int), 1, Arq);
        fwrite(usuario[i].data_dev[2], sizeof(int), 1, Arq);
        fwrite(usuario[i].nome_livro[0], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_livro[1], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_livro[2], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_livro[3], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_livro[4], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_livro[5], sizeof(usuario[i].nome_livro[1]), 1, Arq);
        fwrite(usuario[i].nome_autor); //15
    }
    fclose(Arq);
}

int verifica_cad(t_cadastro *usuario, int i, char *temp){
    Arq=fopen("Arquivo.bin", "rb");
    char s_opcao[3];
    int opcao, cont, qtd;
    printf("1. Nome\n");
    printf("2. Numero de cadastro\n");
    printf("Digite sua opcao: ");
    fgets(opcao, 3, stdin);
    if((s_opcao[0]=='1')||(s_opcao[0] == '2')){
        opcao = atoi(s_opcao);
    }else{
        printf("Numero inválido\n");
        fclose(Arq);
        return -1;
    }

    if(Arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        return -1;
    }

    if(opcao == 1){
        printf("Nome: ");
    }else{
        printf("Numero: ");
    }
    fgets(temp, 50, stdin);
    int aux;
    qtd = fread(aux, (sizeof(char))*(strlen(temp)), i, Arq); //2 elementos de tamanho char * strlen
    //ver se com numero funciona, pq salvamos antes como inteiro e agora estamos procurando c uma string
    for(cont=0; cont<qtd; cont++){ //so o necessario (2 elementos)
        if(strcmp(aux[cont], temp) == 0){
            fclose(Arq);
            return 1; //tem cadastro
        }else{
            fclose(Arq);
            return 0;
        }
    }


}

void altera_cad(t_cadastro *usuario, int i){

}

void emprestimo();

void confirma_senha(char *temp){
    int count =0;
    char aux[50];
    Arq = fopen("Arquivo.bin", "rb");
    printf("Confirme sua senha: ");
    fgets(senha1, 7, stdin);

    while(!(feof(Arq))){
        fgets(aux, 50, Arq);
        count++;
        if(!(strcmp(aux, temp))){ //pensar na posicao if else
            fseek(+x bytes);
            fgets(senha, 7, Arq);
            if(!strcmp(senha1, senha2))
                //
            else
                //senha incorreta
                break

        }
                count++;
                \n
                +x
                count %15 == 0
                fgets da linha toda e comparar com o nome
                rodar o count + 2
                fgets da senha
    }
}


int main(){
    int i = 0, p;
    char *temp = (char*) malloc(50*(sizeof(char)));

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
                p = verifica_cad(usuario, i, temp);//funcao verifica se tem cadastro
                if (p==1){ //tem cadastro
                    //chama outra funcao que pede a senha
                    confirma_senha;

                }else if(p == 0){ //nao tem cadastro
                    cadastro(usuario,i);
                    salva_cadastro(usuario, i);
                    i++;
                }else{

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
