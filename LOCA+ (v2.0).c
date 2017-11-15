#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    char nome[50];
    char diretor[30];
    int ano;
    float preco;
    char sinopse[220];
    char categoria[30];
    int ativo;
    int alugado;
}Filme;

typedef struct{
    char nome[50];
    char cpf[15];
    char endereco[60];
    int status;
    char senha[9];
    int ativo;
    Filme alugados[4];
}Cliente;

typedef struct{
    float qtd_dias;
    int forma_de_pagamento;
    float valor_a_pagar;
}Aluguel;

FILE *filmes;
FILE *clientes;

Cliente cliente[5];
Filme filme[5];
Aluguel aluguel[5];
int i, j;

void abrirArquivoC(FILE *clientes){

	clientes = fopen("clientes.txt", "rb");
	fread(&cliente, sizeof(cliente),1,clientes);
	fclose(clientes);
}

void abrirArquivoF(FILE *filmes){

	filmes = fopen("filmes.txt", "rb");
	fread(&filme, sizeof(filme),1,filmes);
	fclose(filmes);
}

void gravarClientes(FILE *clientes){

	clientes = fopen("clientes.txt", "wb");
	fwrite(&cliente, sizeof(cliente),1,clientes);
	fclose(clientes);
}

void gravarFilmes(FILE *filmes){

	filmes = fopen("filmes.txt", "wb");
	fwrite(&filme, sizeof(filme),1,filmes);
	fclose(filmes);
}

void cadastrarCliente(FILE *clientes){

	abrirArquivoC(filmes);

    for(i=0;i<5;i++){
        if(cliente[i].status == 0){
            printf("ENTRE COM AS INFORMAÇÕES DO CLIENTE: \n");
            printf("(Se você não possui cartão de crédito, apenas insira 0 no campo SENHA)\n");
            printf("\nNOME : ");
            gets(cliente[i].nome);
            printf("\nCPF: ");
            gets(cliente[i].cpf);
            printf("\nENDEREÇO: ");
            gets(cliente[i].endereco);
            printf("\nSENHA (Cartão): ");
            gets(cliente[i].senha);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): ");
            scanf("%d", &cliente[i].status);
            fflush(stdin);
            cliente[i].ativo = 1;
            break;
        	}
    	}

    gravarClientes(clientes);

    system("cls");
    printf("Cadastro finalizado! Pressione ENTER para retornar ao menu.\n");
   	getchar();
}

void catalogarFilme(FILE *filmes){

	abrirArquivoF(filmes);

    for(i=0;i<5;i++){
        if(filme[i].ano == 0){
            printf("ENTRE COM AS INFORMAÇÕES DO FILME: \n");
            printf("\nNOME: ");
            gets(filme[i].nome);
            printf("\nDIRETOR: ");
            gets(filme[i].diretor);
            printf("\nANO: ");
            scanf("%d", &filme[i].ano);
            fflush(stdin);
            printf("\nCATEGORIA: ");
            gets(filme[i].categoria);
            printf("\nSINOPSE: ");
            gets(filme[i].sinopse);
            printf("\nPREÇO EM REAIS: ");
            scanf("%f", &filme[i].preco);
            fflush(stdin);
            filme[i].ativo = 1;
            break;
        }
	}

   	gravarFilmes(filmes);

   	system("cls");
	printf("Cadastro finalizado! Pressione ENTER para retornar ao menu.\n");
    getchar();
}

void atualizar(FILE *clientes){

	abrirArquivoC(clientes);
	char pesquisa[50];

    printf("Digite o CPF do cliente a ser alterado: \n");
    gets(pesquisa);

    for(i=0;i<5;i++){
        if((strcmp(pesquisa,cliente[i].cpf)==0) && (cliente[i].ativo == 1)){
            printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
            printf("\n------------------------------\n");
            printf("\nENTRE COM AS NOVAS INFORMAÇÕES DO CLIENTE: \n");
            printf("\nNOME: ");
            gets(cliente[i].nome);
            printf("\nCPF: ");
            gets(cliente[i].cpf);
            printf("\nENDEREÇO: ");
            gets(cliente[i].endereco);
            printf("\nSENHA (Cartão): ");
            gets(cliente[i].senha);
			printf("\nSTATUS: ");
            scanf("%d", &cliente[i].status);
            fflush(stdin);
            break;
        }
    }

    gravarClientes(clientes);

    printf("Dados atualizados com sucesso!\n");
    printf("Pressione ENTER para retornar ao menu.\n");
    getchar();
}

void buscarFilme(FILE *filmes){
    char pesquisa[50];
	int k = 0;

    abrirArquivoF(filmes);

    printf("Digite o nome do filme que deseja pesquisar: \n");
    gets(pesquisa);

    for(i=0;i<5;i++){
        if((strcmp(pesquisa, filme[i].nome)==0) && (filme[i].ativo == 1)){
            printf("\n------------------------------\n");
            printf("NOME: %s", filme[i].nome);
            printf("\nANO: %d", filme[i].ano);
            printf("\nDIRETOR: %s", filme[i].diretor);
            printf("\nCATEGORIA: %s", filme[i].categoria);
            printf("\nSINOPSE: %s", filme[i].sinopse);
            printf("\nPREÇO: %.2f", filme[i].preco);
            printf("\n------------------------------\n");
			printf("Pressione ENTER para retornar ao menu.\n");
			k = 1;
            break;
        }
	}

	if(k==0){
		printf("\nFilme não encontrado!\n");
	}

    getchar();
}

void buscarCliente(FILE *clientes){

    abrirArquivoC(clientes);

	char pesquisa[50];
	int k = 0;

    printf("Digite o CPF do cliente: \n");
    gets(pesquisa);

    for(i=0;i<5;i++){
        if((strcmp(pesquisa,cliente[i].cpf)==0) && (cliente[i].ativo == 1)){
            k = 1;
			printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
            for(j=0;j<4;j++){
                    if(cliente[i].alugados[j].ano != 0 && (cliente[i].alugados[j].alugado == 1)){
                        printf("\nFILMES ALUGADOS: %s;", cliente[i].alugados[j].nome);
                    }
            }
            printf("\n------------------------------\n");
            printf("Pressione ENTER para retornar ao menu.\n");
            break;
            }
	}

	if(k==0){
		printf("\nCliente não encontrado!\n");
	}

    getchar();
}

void removerCliente(FILE *clientes){
	int decisao;
	char pesquisa[15];

	abrirArquivoC(clientes);

	printf("Digite o CPF do cliente: \n");
	gets(pesquisa);

	for(i=0;i<5;i++){
		if((strcmp(pesquisa,cliente[i].cpf) == 0) && (cliente[i].ativo == 1)){
			printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
            for(j=0;j<4;j++){
                    if(cliente[i].alugados[j].ano != 0 && (cliente[i].alugados[j].alugado == 1)){
                        printf("\nFILMES ALUGADOS: %s;", cliente[i].alugados[j].nome);
                    }
            }
            printf("\n------------------------------\n");

                printf("Tem certeza que deseja remover este cliente? (1 para SIM/2 para NÃO)\n");
                scanf("%d", &decisao);
                fflush(stdin);

                if(decisao == 1){
                    cliente[i].ativo = 0;
                    gravarClientes(clientes);
                    printf("\nCliente removido!\n");
                    printf("Pressione ENTER para retornar ao menu.\n");
                    getchar();
                }
                if(decisao == 2){
                    printf("\nCliente permanece cadastrado!\n");
                    printf("Pressione ENTER para retornar ao menu.\n");
                    getchar();
                }
                break;
            }
		}
	}

void alugar(FILE *filmes, FILE *clientes){

    abrirArquivoF(filmes);

    abrirArquivoC(clientes);

    char pesquisa1[50], pesquisa2[50], pesquisa3[50];
    int decisao, x;

    printf("Digite o CPF do cliente que está alugando: \n");
    gets(pesquisa1);

    for(i=0;i<5;i++){
    	if(strcmp(pesquisa1, cliente[i].cpf) == 0 && (cliente[i].ativo == 1)){

    	    printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
       	    printf("\n------------------------------\n");

			printf("Digite o filme a ser alugado: \n");
			gets(pesquisa2);

			for(j=0;j<5;j++){
                if((strcmp(pesquisa2, filme[j].nome) == 0)){
                    printf("\n------------------------------\n");
                    printf("NOME: %s", filme[j].nome);
                    printf("\nANO: %d", filme[j].ano);
                    printf("\nDIRETOR: %s", filme[j].diretor);
                    printf("\nCATEGORIA: %s", filme[j].categoria);
                    printf("\nSINOPSE: %s", filme[j].sinopse);
                    printf("\nPREÇO: %.2f", filme[j].preco);
                    printf("\n------------------------------\n");
                    break;
                }
			}


			printf("Defina a forma de pagamento: (1 para CARTÃO/2 para DINHEIRO)\n");
			scanf("%d", &aluguel[i].forma_de_pagamento);
			fflush(stdin);

			if(aluguel[i].forma_de_pagamento==1){
				printf("Digite sua senha : \n");
				gets(pesquisa3);

				if(strcmp(pesquisa3, cliente[i].senha) == 0){
					printf("Digite a  quantidade de dias para alugar: \n");
					scanf("%f", &aluguel[i].qtd_dias);
					fflush(stdin);

                        if(cliente[i].status == 1){
                            aluguel[i].valor_a_pagar = ((aluguel[i].qtd_dias * filme[i].preco) - ((aluguel[i].qtd_dias * filme[i].preco) * 0.3));
                            printf("Alugado! O valor a ser pago é %.2f reais", aluguel[i].valor_a_pagar);
                            for(x=0;x<4;x++){
                                 if(cliente[i].alugados[x].ano == 0){
                                    cliente[i].alugados[x] = filme[j];
                                    cliente[i].alugados[x].alugado = 1;
                                    break;
                                 }
                            }
                            getchar();

                        }

                        if(cliente[i].status == 2){
                            aluguel[i].valor_a_pagar = (aluguel[i].qtd_dias * filme[i].preco);
                            printf("Alugado! O valor a ser pago é %.2f reais", aluguel[i].valor_a_pagar);
                            for(x=0;x<4;x++){
                                 if(cliente[i].alugados[x].ano == 0){
                                    cliente[i].alugados[x] = filme[j];
                                    cliente[i].alugados[x].alugado = 1;
                                    break;
                                 }
                            }
                            getchar();
                        }
                    }
                }

                if(aluguel[i].forma_de_pagamento==2){
                    printf("Digite a  quantidade de dias para alugar: \n");
                    scanf("%f", &aluguel[i].qtd_dias);
                    fflush(stdin);

                    if(cliente[i].status == 1){
                        aluguel[i].valor_a_pagar = ((aluguel[i].qtd_dias * filme[i].preco) - ((aluguel[i].qtd_dias * filme[i].preco) * 0.3));
                        printf("Alugado! O valor a ser pago é %.2f reais", aluguel[i].valor_a_pagar);
                        for(x=0;x<4;x++){
                                 if(cliente[i].alugados[x].ano == 0){
                                    cliente[i].alugados[x] = filme[j];
                                    cliente[i].alugados[x].alugado = 1;
                                    break;
                                 }
                            }
                        getchar();
                    }

                    if(cliente[i].status == 2){
                        aluguel[i].valor_a_pagar = (aluguel[i].qtd_dias * filme[i].preco);
                        printf("Alugado! O valor a ser pago é %.2f reais", aluguel[i].valor_a_pagar);
                        for(x=0;x<4;x++){
                                 if(cliente[i].alugados[x].ano == 0){
                                    cliente[i].alugados[x] = filme[j];
                                    cliente[i].alugados[x].alugado = 1;
                                    break;
                                 }
                            }
                        getchar();
                    }
                }
                break;
    	}

    }

    gravarClientes(clientes);

    gravarFilmes(filmes);

	getchar();
}

void devolver(FILE *filmes, FILE *clientes){
    char pesquisa1[50], pesquisa2[50];
    int decisao, x;

    abrirArquivoC(clientes);

    abrirArquivoF(filmes);

    printf("Digite o CPF do cliente que está devolvendo: \n");
    gets(pesquisa2);

    for(i=0;i<5;i++){
        if((strcmp(pesquisa2,cliente[i].cpf) == 0) && (cliente[i].ativo == 1)){
            printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
            printf("\n------------------------------\n");

            printf("Digite o nome do filme a ser devolvido: \n");
            gets(pesquisa1);

                for(j=0;j<5;j++){
                    if((strcmp(pesquisa1,cliente[i].alugados[j].nome) == 0) && (cliente[i].alugados[j].alugado == 1)){
                        printf("\n------------------------------\n");
                        printf("NOME: %s", cliente[i].alugados[j].nome);
                        printf("\nANO: %d", cliente[i].alugados[j].ano);
                        printf("\nDIRETOR: %s", cliente[i].alugados[j].diretor);
                        printf("\nCATEGORIA: %s", cliente[i].alugados[j].categoria);
                        printf("\nSINOPSE: %s", cliente[i].alugados[j].sinopse);
                        printf("\nPREÇO: %.2f", cliente[i].alugados[j].preco);
                        printf("\n------------------------------\n");

                        for(x=0;x<4;x++){
                            if((strcmp(pesquisa1,cliente[i].alugados[x].nome) == 0) && (cliente[i].alugados[x].alugado == 1)){
                                cliente[i].alugados[x].alugado = 0;
                                cliente[i].alugados[x].ano = 0;
                                break;
                                }
                        }

                        printf("Filme devolvido! Obrigado pela preferência!\n");
                        getchar();


                }
            }
            break;
        }
    }
        gravarClientes(clientes);

        gravarFilmes(filmes);
    }
    
void listarFilmes(FILE *filmes){
	
	abrirArquivoF(filmes);
	
	printf("LISTANDO FILMES CATALOGADOS... \n");
	
	for(i=0;i<5;i++){
		if(filme[i].ativo == 1){
			printf("\n------------------------------\n");
            printf("NOME: %s", filme[i].nome);
            printf("\nANO: %d", filme[i].ano);
            printf("\nDIRETOR: %s", filme[i].diretor);
            printf("\nCATEGORIA: %s", filme[i].categoria);
            printf("\nSINOPSE: %s", filme[i].sinopse);
            printf("\nPREÇO: %.2f", filme[i].preco);
            printf("\n------------------------------\n");
		}
	}
	getchar();
}

void listarClientes(FILE *clientes){
	
	abrirArquivoC(clientes);
	
	printf("LISTANDO CLIENTES CADASTRADOS... \n");
	
	for(i=0;i<5;i++){
		if(cliente[i].ativo == 1){
			printf("\n------------------------------\n");
            printf("NOME: %s", cliente[i].nome);
            printf("\nCPF: %s", cliente[i].cpf);
            printf("\nENDEREÇO: %s", cliente[i].endereco);
            printf("\nSTATUS (1 para VIP/2 para NORMAL): %d", cliente[i].status);
            for(j=0;j<4;j++){
                    if(cliente[i].alugados[j].ano != 0 && (cliente[i].alugados[j].alugado == 1)){
                        printf("\nFILMES ALUGADOS: %s;", cliente[i].alugados[j].nome);
                    }
            }
            printf("\n------------------------------\n");
		}
	}
	getchar();
}

int main()
{
    char op;
    FILE *filmes;
    FILE *clientes;

    setlocale(LC_ALL, "Portuguese");
	system("color 4");

    do{
        system("cls");

        printf("\t@@       @@@@@@@@   @@@@@@@    @@@@@@@@          @@      \n");
        printf("\t@@       @@    @@   @@        @@      @@         @@      \n");
        printf("\t@@       @@    @@   @@        @@@@@@@@@@     @@@@@@@@@@  \n");
        printf("\t@@       @@    @@   @@        @@      @@         @@      \n");
        printf("\t@@@@@@@  @@@@@@@@   @@@@@@@   @@      @@         @@      \n");
        printf("\n\n");

        printf("Escolha a operação desejada: \n\n");
        printf("(1)Catalogar filme\n");
        printf("(2)Cadastrar cliente\n");
        printf("(3)Atualizar informações do cliente\n");
        printf("(4)Buscar filme\n");
        printf("(5)Buscar cliente\n");
        printf("(6)Remover cliente\n");
        printf("(7)Alugar\n");
        printf("(8)Devolver\n");
        printf("(9)Listar filmes\n");
    	printf("(10)Listar clientes\n");
        printf("(11)Sair do sistema\n\n");
		scanf("%d", &op);
        fflush(stdin);

        switch(op){

            case 1 :  	system("cls");
                      	catalogarFilme(filmes);
                      	break;

            case 2 :  	system("cls");
                     	cadastrarCliente(clientes);
                      	break;

            case 3 :  	system("cls");
                    	atualizar(clientes);
                        break;

            case 4 :  	system("cls");
                        buscarFilme(filmes);
                        break;

            case 5 :  	system("cls");
                        buscarCliente(clientes);
                        break;

            case 6 :  	system("cls");
                        removerCliente(filmes);
                        break;

			case 7 :  	system("cls");
                        alugar(filmes, clientes);
                        break;

			case 8 :  	system("cls");
						devolver(filmes,clientes);
						break;

			
			case 9 : 	system("cls");
						listarFilmes(filmes);
						break;
						
			case 10: 	system("cls");
						listarClientes(clientes);
						break;
			
            case 11  : 	system("cls");
                        printf("Obrigado por usar nosso sistema!");
                        printf("\n\n\n");
                        printf("Criado por Matheus Cavalcanti Agostinho\nEstudante de Graduação em Ciência da Computação pela Universidade Federal Rural de Pernambuco.");
                        printf("\nIntrodução à Programação I - BC4 2017.1");
                        return 11;

            default  :  printf("Variável inválida!");
                        break;
        	}
        }while(op != 11);
    }
