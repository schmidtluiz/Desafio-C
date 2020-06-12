#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {
            char nome[50];
            char end[100];
            char cidade[50];
            char estado[2];
            char cep[10];
            char data[20];
            };

void inclui();
void lista();
int pesquisa();
int pesquisaInicial();
int pesquisaData();
int pesquisaCEP();
void altera();
void exclui();
void reseta();

int main()
{
        struct dados info;
        struct dados *p;
        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        for(i=0;i<sizeof(info);i++) {   //zera a estrutura de dados
            info.nome[i]=0;
           }
        while(1){
        printf("//////////////////////*MENU DE OPCOES*/////////////////////////\n");
        printf("///          1 -Inclua dados                                ///\n");
        printf("///          2 -Lista dados                                 ///\n");
        printf("///          3 -Pesquisa dados                              ///\n");
        printf("///          4 -Pesquisa dados pela primeira letra          ///\n");
        printf("///          5 -Pesquisa dados pelo mes de nascimento       ///\n");
        printf("///          6 -Pesquisa dados pelo CEP                     ///\n");
        printf("///          7 -Altera dados                                ///\n");
        printf("///          8 -Exclui dados                                ///\n");
        printf("///          9 -Saida                                       ///\n");
        printf("///         10 -Resetar o sistema.                          ///\n");
        printf("///////////////////////////////////////////////////////////////\n");
        printf("Insira a opcao desejada: ");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3: pesquisa(p, tam);
                break;

                case 4: pesquisaInicial(p, tam);
                break;

                case 5: pesquisaData(p, tam);
                break;

                case 6: pesquisaCEP(p, tam);
                break;

                case 7: altera(p, tam);
                break;

                case 8: exclui(p, tam);
                break;

                case 9: exit(0);
                break;

                case 10: reseta();
                break;

                default: printf("\n OPCAO INVALIDA.\n");
                }
    };

}

void inclui(struct dados *ps, int tam)
{

    system("cls");
    printf("INCLUIR UM REGISTRO: ");
    printf("\n------------------\n");

    FILE *p, *p1;
    int cont = 0;
    int i;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    //printf("contador antes %d\n",cont);
    fclose(p1);

    for(i=0;i<tam;i++){ //zera os dados da estrutura
        ps -> nome[i]=0;
    }

    p = fopen("arquivo.txt", "a");

    if( p == NULL){
        printf("\nERRO");
        exit(1);
    }

   //aqui os dados sao recebidos via teclado

    printf("Insira o nome: ");
    gets((*ps).nome);
    printf("Insira o endereco: ");
    gets((*ps).end);
    printf("Insira a cidade: ");
    gets((*ps).cidade);
    printf("Insira o estado: ");
    gets((*ps).estado);
    printf("Insira o cep: ");
    gets((*ps).cep);
    printf("Insira o data de nascimento: ");
    gets((*ps).data);
    printf("\n------------------\n");

    fwrite(ps, tam,1,p);
    fclose(p);

    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    //printf("contador depois %d\n",cont);
    fclose(p1);
}

void lista(struct dados *ps, int tam)
{
    system("cls");
    printf("LISTA DE TODOS OS REGISTROS: ");
    printf("\n------------------\n");
    FILE *p, *p1;
    FILE *a;
    struct dados info;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    //printf("%d\n",cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
    }

    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    for(i=0;i<cont; i++){
        comp = i*tam;   //calcula o n. de bytes para posicionar o ponteiro do arquivo

    fseek(p,comp,0);    //posiciona o ponteiro no inicio do registro dentro do arquivo
    fread(ps,sizeof(info),1,p);   //le o registro
    if(ps -> nome[0] != '*'){     //verifica se esta apagado
        puts((*ps).nome);
        puts((*ps).end);
        puts((*ps).cidade);
        puts((*ps).estado);
        puts((*ps).cep);
        puts((*ps).data);
        printf("\n------------------\n");
        }
    }
        fclose(p);
}

int pesquisa(struct dados *ps, int tam)
{
    system("cls");
    printf("PESQUISAR UM REGISTRO: ");
    printf("\n------------------\n");
    FILE *p;
    FILE *a;

    char nome1[50];
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    //printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        //printf("n. do reg.: %d\n",y);
        puts((*ps).nome);
        puts((*ps).end);
        puts((*ps).cidade);
        puts((*ps).estado);
        puts((*ps).cep);
        puts((*ps).data);
        printf("\n------------------\n");
        return y;
    }
    }
    printf("REGISTRO NAO EXISTE. \n");
    return -1;
}

int pesquisaInicial(struct dados *ps, int tam)
{
    system("cls");

    FILE *p;
    FILE *a;

    char nome1[1];
    int i=0,y, x;
    int cont;

    printf("Informe a inicial do nome para pesquisa: ");
    gets(nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    //printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] == ps -> nome[x]){
                puts((*ps).nome);
                puts((*ps).end);
                puts((*ps).cidade);
                puts((*ps).estado);
                puts((*ps).cep);
                puts((*ps).data);
                printf("\n------------------\n");
            }
        }
    }
    printf("REGISTRO NAO EXISTE. \n");
    return -1;
}

int pesquisaData(struct dados *ps, int tam)
{
    system("cls");

    FILE *p;
    FILE *a;

    char data1[2];
    int i=0,y, x;
    int cont;

    printf("Informe o mes da data de nascimento para pesquisa: ");
    gets(data1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    //printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 3; data1[x] != '/';x++){
            if(data1[0] == ps -> data[3] && data1[1] == ps -> data[4]){
                puts((*ps).nome);
                puts((*ps).end);
                puts((*ps).cidade);
                puts((*ps).estado);
                puts((*ps).cep);
                puts((*ps).data);
                printf("\n------------------\n");
                break;
            }
        }
    }
    printf("REGISTRO NAO EXISTE. \n");
    return -1;
}

int pesquisaCEP(struct dados *ps, int tam)
{
    system("cls");

    FILE *p;
    FILE *a;

    char cep1[10];
    int i=0,y, x;
    int cont;

    printf("Informe um CEP para pesquisa: ");
    gets(cep1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    //printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; cep1[x] != '\0';x++){
            if(cep1[x] != ps -> cep[x]){
                break;
            }
        }

    if(cep1[x] == '\0' && ps -> cep[x] == '\0')
    {
        //printf("n. do reg.: %d\n",y);
        puts((*ps).nome);
        puts((*ps).end);
        puts((*ps).cidade);
        puts((*ps).estado);
        puts((*ps).cep);
        puts((*ps).data);
        printf("\n------------------\n");
        return y;
    }
    }
    printf("REGISTRO NAO EXISTE. \n");
    return -1;
}

void altera(struct dados *ps, int tam)
{
    system("cls");

    FILE *p;
    int n_reg;;
    int n_bytes;

    n_reg = pesquisa(ps, tam);     //pesquisa o registro no arquivo
    //printf("altera reg n.: %d\n",n_reg);
    if(n_reg == -1){
 	     return;
    }
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    printf("INSIRA OS DADOS PARA ALTERACAO: \n");
    //recebe via teclado todos os dados do registro
    printf("Insira o nome: ");
    gets((*ps).nome);
    printf("Insira o endereco: ");
    gets((*ps).end);
    printf("Insira a cidade: ");
    gets((*ps).cidade);
    printf("Insira o estado: ");
    gets((*ps).estado);
    printf("Insira o cep: ");
    gets((*ps).cep);
    printf("Insira o data de nascimento: ");
    gets((*ps).data);
    printf("\n------------------\n");

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    system("cls");

    FILE *p;
    int n_reg;
    int n_bytes;
    n_reg = pesquisa(ps, tam);  //pesquisa o registro no arquivo
    if(n_reg == -1){
 	     return;
    }
    p = fopen("arquivo.txt", "r+");
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p );   //le o registro do arquivo
    //printf("nome para apagar e' %s\n",ps -> nome);
    //apaga o registro do arquivo
    (*ps).nome[0] = '*';
    printf("Contato excluido!\n");
    //printf("nome para apagar e' %s\n",ps -> nome);

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);

}

void reseta()
{
    system("cls");

    char dec;
    FILE *p;
    FILE *a;

    printf("/////////////////////////*ATENCAO*/////////////////////////////\n");
    printf("///VOCE ESTA PRESTES A DELETAR TODOS OS REGISTROS DO SISTEMA///\n");
    printf("///               TEM CERTEZA DISSO? S/N                    ///\n");
    printf("/////////////////////////*ATENCAO*/////////////////////////////\n");
    scanf("%c", &dec);
    if(dec == 'S' || dec == 's'){
        p = fopen("arquivo.txt", "w");
        a = fopen("contador.txt", "w");
        fclose(p);
        fclose(a);

        printf("SISTEMA RESETADO. \n");
    }else{
        printf("SISTEMA NAO FOI RESETADO. \n");
    }
}
