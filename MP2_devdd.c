#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char raca[50];
    int idade;
    float salario;
    char CPF[12];
} Pessoa;

typedef struct {
    char nome[50];
    int codigo; //código único que identifica cada cidade, INT
    Pessoa* cidadaos;
    int capacidade;
} Cidade;

Cidade* NovaCidade(Cidade* censo, int* tam) {

    Cidade *f_censo_temp=NULL; // "f_" para TODO o codigo eh apenas uma flag que indica que a variavel em questao se limita ao escopo da funcao.
    Cidade f_cidade_nova;

    (*tam)++; // incrementa o valor tam em um, equivale a tam++; na main

    f_censo_temp = censo; // ponteiro temporaio passa a apontar para os dados como o censo, recurso de seguranca caso o realloc retorne NULL
    censo = (Cidade *) realloc(f_censo_temp, (sizeof(Cidade) * (*tam))); // quantidade de cidades * tamanho de uma cidades alloca memoria para a nova cidade a ser adicionada, ajusta a memoria alocada no tamanho necessario de acordo com a quantidade de cidades
    
    if(censo==NULL) { // if de seguranca caso haja problema na alocacao de memoria
        printf("Erro na alocacao de memoria\n");       
        for (int i = 0; i < (*tam); i++) { // passa por todas as cidades
            free(f_censo_temp[i].cidadaos); // libera todos os ponteiros "internos" (*cidadaos)
        }       
        free(f_censo_temp);
        exit(1);
    }

    // com a memoria devidamente alocada, basca receber os dados do usuario e armazena-los
    printf("Digite o nome da nova cidade: "); scanf(" %49[^\n]", f_cidade_nova.nome);
    printf("Agora, digite o codigo dessa cidade: "); scanf("%d", &f_cidade_nova.codigo);
    f_cidade_nova.capacidade = 0; // inicia em zero, nao foram adicionadas pessoas ainda
    f_cidade_nova.cidadaos=NULL; // aponta em NULL inicialmente para evitar problemas com o realloc

    censo[(*tam)-1] = f_cidade_nova; // tam-1 visto que o indice final eh o tamanho do array-1

    return censo;
}

void InserirOuAtualizar(Cidade* censo, int tam) {

    Pessoa *tmp=NULL;
    Pessoa f_pessoa_nova;
    Cidade *TMP_TOTAL=NULL;
    int f_codigo_cidade=0;
    int f_index_cidade=0;
    int f_flag_encontrou=0; // 0 --> pessoa nao encontrada no sistema    1 --> pessoa foi encontrada

    // primeiramente, recebe-se os dados do usuario e eles sao alocados temporariamente em f_pessoa_nova
    printf("\tAbaixo, digite os dados da pessoa a ser adicionada\n");

    printf("Codigo da cidade da nova pessoa: "); scanf("%d", &f_codigo_cidade);

    printf("Nome: "); scanf(" %49[^\n]", f_pessoa_nova.nome);
    printf("Raca: "); scanf(" %49[^\n]", f_pessoa_nova.raca);
    printf("Idade: "); scanf("%d", &f_pessoa_nova.idade);
    printf("Salario: "); scanf("%f", &f_pessoa_nova.salario);
    printf("CPF (sem espacos entre os numeros): "); scanf(" %s", f_pessoa_nova.CPF);

    for (int i = 0; i < tam; i++) { // passa por todas as cidades, procura o indice da cidade
        if(f_codigo_cidade == censo[i].codigo) f_index_cidade = i;
    }
    
    for (int i = 0; i < (censo[f_index_cidade].capacidade); i++) { // (censo[f_index_cidade].capacidade) faz o for passar por todas as pessoas da cidade em questao
        
        if(!strcmp(f_pessoa_nova.CPF, (censo[f_index_cidade].cidadaos[i].CPF))) { // se o cpf for encontrado

            f_flag_encontrou++;

            strcpy(censo[f_index_cidade].cidadaos[i].nome, f_pessoa_nova.nome); // nome
            strcpy(censo[f_index_cidade].cidadaos[i].raca, f_pessoa_nova.raca); // raca
            censo[f_index_cidade].cidadaos[i].idade = f_pessoa_nova.idade; // idade
            censo[f_index_cidade].cidadaos[i].salario = f_pessoa_nova.salario; // salario
            strcpy(censo[f_index_cidade].cidadaos[i].CPF, f_pessoa_nova.CPF); // CPF

        }
    }
    
    if(f_flag_encontrou == 0) {
        
        TMP_TOTAL = censo;
        tmp = censo[f_index_cidade].cidadaos;
        censo[f_index_cidade].cidadaos = (Pessoa *) realloc(tmp, ((censo[f_index_cidade].capacidade+1) * sizeof(Pessoa)));
        
        if(censo[f_index_cidade].cidadaos == NULL) {
            printf("Erro de alocacao de memoria\n");
            for (int i = 0; i < tam; i++) { // passa por todas as cidades
                free(TMP_TOTAL[i].cidadaos); // libera memoria de todos os ponteiros cidadaos
            }
            free(TMP_TOTAL);
            // nao eh necessario dar free em tmp pois free(TMP_TOTAL[i].cidadaos) ja inclui isso
            exit(1);
        }

        // censo[f_index_cidade].capacidade visto que o a variavel censo[f_index_cidade].capacidade esta desatializada. censo[f_index_cidade].capacidade == (censo[f_index_cidade].capacidade-1)+1
        strcpy(censo[f_index_cidade].cidadaos[(censo[f_index_cidade].capacidade)].nome, f_pessoa_nova.nome); // nome
        strcpy(censo[f_index_cidade].cidadaos[(censo[f_index_cidade].capacidade)].raca, f_pessoa_nova.raca); // raca
        censo[f_index_cidade].cidadaos[(censo[f_index_cidade].capacidade)].idade = f_pessoa_nova.idade; // idade
        censo[f_index_cidade].cidadaos[(censo[f_index_cidade].capacidade)].salario = f_pessoa_nova.salario; // salario
        strcpy(censo[f_index_cidade].cidadaos[(censo[f_index_cidade].capacidade)].CPF, f_pessoa_nova.CPF); // CPF


        censo[f_index_cidade].capacidade++;

    }

}

void Procura(Cidade* censo, int tam) {

    char f_cpf_procurado[12] = "a"; // inicializacao de seguranca
    int f_cidade_procurada=0;
    int f_index_cidade_procurada=0;
    int f_flag_encointrou=0; // 0 --> n econtrou    1 --> encontrou

    printf("Digite o codigo da cidade da pessoa em questao: "); scanf("%d", &f_cidade_procurada);
    printf("Agora, digite o CPF dessa pessoa (apenas numeros, sem espaco): "); scanf(" %11[^\n]", f_cpf_procurado);

    for (int i = 0; i < tam; i++) { // passa por todas as cidades
        
        if(f_cidade_procurada == censo[i].codigo) { // encontra a cidade procurada, armazena seu indide
            f_index_cidade_procurada = i;
        }
    }
    
    for (int i = 0; i < (censo[f_index_cidade_procurada].capacidade); i++) { // passa por todos os cidadaos da cidade procurada

        if(!strcmp(f_cpf_procurado, censo[f_index_cidade_procurada].cidadaos[i].CPF)) { // encontra a pessoa correta
            
            f_flag_encointrou++;

            printf("Aqui estao os dados da pessoa procurada:\n\n");
            
            printf("Nome: %s\n", censo[f_index_cidade_procurada].cidadaos[i].nome);
            printf("Raca: %s\n", censo[f_index_cidade_procurada].cidadaos[i].raca);
            printf("Idade: %d\n", censo[f_index_cidade_procurada].cidadaos[i].idade);
            printf("Salario: %.2f\n", censo[f_index_cidade_procurada].cidadaos[i].salario);
            printf("CPF: %s\n", censo[f_index_cidade_procurada].cidadaos[i].CPF);

        }

    }

    if(f_flag_encointrou == 0) {

        printf("Desculpe, mas esse CPF nao esta cadastrado no sistema, tente realizar um novo cadastro ou veirifique se o CPF foi inserido corretamente.\n");

    }

}

void ViewTable(Cidade* censo, int tam) {

    printf("\n\tExibindo dados de todas as pessoas: \n\n");

    for (int i = 0; i < tam; i++) { // passa por todas as cidades

        printf("\tCidade: %s\n", censo[i].nome);

        for (int j = 0; j < (censo[i].capacidade); j++) { // passa por todas as pessoas da cidade
        
            printf("Nome: %s\n", censo[i].cidadaos[j].nome);
            printf("  Raca: %s\n", censo[i].cidadaos[j].raca);
            printf("  Idade: %d\n", censo[i].cidadaos[j].idade);
            printf("  Salario: %.2f\n", censo[i].cidadaos[j].salario);
            printf("  CPF: %s\n", censo[i].cidadaos[j].CPF);

            printf("\n");
        }
        printf("\n");
    }

    printf("\tDados de todas as pessoas exibidos com sucesso!\n");
}

void Desaloca(Cidade* censo, int tam) {

    for (int i = 0; i < tam; i++) { // passa por todas as cidades
        free(censo[i].cidadaos); // da free em todos os ponteiros **DO** censo
    }
    free(censo);

}

void Remover(Cidade* censo, int tam) {

    Cidade *TMP_TOTAL=NULL; // servira caso necessario abortar (exit(1)) no meio da funcao. Esse ponteiro permitira dar free em todas as memorias alocadas
    
    // _procurado se referem ao procurado pelo usuario
    char f_CPF_procurado[12] = "a";
    int f_cidade_procurada=0;

    // index_procurada se refere ao indice do conteudo procurado pelo usuario 
    int f_index_cidade_procurada=0;
    int f_index_pessoa_procurada=0;
    Pessoa *tmp=NULL;

    printf("Digite o codigo da cidade da pessoa a ser removida: "); scanf("%d", &f_cidade_procurada);
    printf("Agora, digite o CPF dessa pessoa (apenas numeros, sem espacos): "); scanf(" %11[^\n]", f_CPF_procurado);

    for (int i = 0; i < tam; i++) { // passa por todas as cidades

        if(censo[i].codigo == f_cidade_procurada) { // verifica o codigo de cada cidade
            f_index_cidade_procurada = i; // armazena o indice da cidade procurada
        }
    }

    for (int i = 0; i < censo[f_index_cidade_procurada].capacidade; i++) { // passa por todas as pessoas da cidade
        
        if(!strcmp(censo[f_index_cidade_procurada].cidadaos[i].CPF, f_CPF_procurado)) {
            f_index_pessoa_procurada = i; // armazena o indice da pessoa procurada
        }
    }

    // com os indices da cidade e pessoa em questao ja armazenados, basta modificar a memoria alocada de forma a remover a pessoa escolhida

    for (int i = f_index_pessoa_procurada; i < (censo[f_index_cidade_procurada].capacidade -1); i++) { // comeca na pessoa procurada e passa por todas menos a ultima que sera acessada com o i+1. (i+1)-1 == i
        
        censo[f_index_cidade_procurada].cidadaos[i] = censo[f_index_cidade_procurada].cidadaos[i+1]; // o atual recebe proximo e assim por diante

    } // apos esse for podemos realocar a memoria com uma pessoa a menos, realloc funcionara corretamente

    TMP_TOTAL = censo; // servira apenas em caso de erro de alocacao de memoria, onde todos os ponteiros "cidadaos" precisarao ter sua memoria liberada
    tmp = censo[f_index_cidade_procurada].cidadaos;
    censo[f_index_cidade_procurada].cidadaos = (Pessoa *) realloc(tmp, (sizeof(Pessoa) * (censo[f_index_cidade_procurada].capacidade-1))); // diminui em uma pessoa a memoria alocada
    
    //                                       se a capacidade for 1 (sera decrementada para 0), nao se trata de um erro de alocacao de memoria
    if((censo[f_index_cidade_procurada].cidadaos == NULL) && (TMP_TOTAL[f_index_cidade_procurada].capacidade!=1)) { // caso de erro
        printf("Erro de alocacao de memoria\n");
        for (int i = 0; i < tam; i++) { // passa por todas as cidades
            free(TMP_TOTAL[i].cidadaos);
        }
        free(censo); // o mesmo de free(TMP_TOTAL);
        exit(1);
    }

    censo[f_index_cidade_procurada].capacidade--; // diminui em um a quantidade de pessoas da cidade
    printf("Pessoa removida com sucesso!\n");
}

int main() {

    int escolha=0; // inicia em 0 para entrar no while do menu

    Cidade *censo=NULL; // comeca em NULL para que a primeira alocacao, caso vinda de um realloc, nao cause problemas
    int tam=0; // tam == qtdCidades. Inicia em zero pois inicialmente nao ha cidades cadastradas

    while (escolha!=6) { // loop menu
        
        printf("\n\t\t\t------ Censo Demografico - Menu Inicial ------\n\n\tEscolha uma opcao (digite apenas o numero dela):\n1. Cadastrar cidade\n2. Procurar informacoes de um CPF\n3. Exibir todos os dados registados\n4. Adicionar/Atualizar dados de uma pessoa\n5. Remover pessoa\n6. Sair\n :. ");
        scanf("%d", &escolha);

        if(escolha!=6) { // se a escolha foi sair, nao entrara em nenhuma das outras opcoes

            if(escolha==1) { // 1. Cadastrar cidade

                censo = NovaCidade(censo, &tam); // "censo" ja eh um ponteiro e tam "se torna" um com o "&"
                printf("Nova cidade cadastrada com sucesso!\n");

            }
            else if(escolha==2) { // 2. Procurar informacoes de um CPF

                Procura(censo, tam);

            }
            else if(escolha==3) { // 3. Exibir todos os dados registados
            
                ViewTable(censo, tam);

            }
            else if(escolha==4) { // 4. Adicionar/Atualizar dados de uma pessoa
            
                InserirOuAtualizar(censo, tam);
                printf("Dados adicionados/atualizados com sucesso!\n");

            }
            else if(escolha==5) { // 5. Remover pessoa
            
                Remover(censo, tam);

            }
            else {
                printf("Digite um valor valido.\n");
                // visto que o valor 6 (sair) nao vai entrar nesse else, somente valores nao disponiveis no menu

            }
        }
    }

    // libera memoria alocada
    Desaloca(censo, tam);

    printf("\nSaindo...\n\n");
    
    return 0;
}