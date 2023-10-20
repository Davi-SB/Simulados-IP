#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int linha; // linha da localizacao do medicamento no coliseu
    int coluna; // coluna da localizacao do medicamento medicamento no coliseu
    char medic[50]; // nome do medicamento
} LocalM;

typedef struct {
    char medic[50]; // nome do medicamento
    int qtdM; // qtd de medicamentos no tal pedido
} TMed;

typedef struct {
    int qtd; // qtd de medicamentos diferentes
    TMed *tMed; // vetor de medicamentos diferentes de cada pedido
} Pedido;

LocalM *carregaConfig(int *tamC) {

    FILE *arq=NULL;
    LocalM *locMed_f=NULL, *locMed_tmp_f=NULL; // todas as variaveis declaradas com o sufixo "_f" ou "f_" apenas sinalizam que a variavel se limita ao escopo da funcao
    LocalM med_atual;

    arq = fopen("locMed.txt", "rt"); // r --> read; t --> txt
    if(arq==NULL) {
        printf("Erro em abrir arquivo\n");
        exit(1);
    }

    //formato considerado: "linha,coluna,nome"
    while (!feof(arq)) { // executa ate que seja o final do arquivo
        
        // escaneia dados de uma linha do arquivo
        fscanf(arq, "%d,%d,%49[^\n]\n", &med_atual.linha, &med_atual.coluna, med_atual.medic);
        (*tamC)++; // incrementa o tamC, que eh declarado inicialmente como 0, seu valor comeca em 0

        // aloca memoria para tais dados serem inseridos
        locMed_tmp_f = locMed_f;
        locMed_f = (LocalM *) realloc(locMed_tmp_f, (*tamC)*sizeof(LocalM));
        if(locMed_f == NULL) { // caso de seguranca de verificacao de erro de alocacao de memoria
            printf("Erro de alocacao de memoria\n");
            free(locMed_tmp_f); 
            fclose(arq);
            exit(1);
        }

        // inserere os dados no ultimo espaco alocado no vetor dinamico
        locMed_f[(*tamC)-1] = med_atual;
    }
    
    fclose(arq); // fecha o arquivo
    return locMed_f; // retorna o ponteiro com os medicamentos e suas devidas localizacoes
}

Pedido *carregaPedidos(int *tamP) {

    Pedido *pedidos_f=NULL, *pedidos_tmp_f=NULL;
    Pedido pedido_atual;
    FILE *arq=NULL;
    int tam=0; // auxiliador de leitor 

    arq = fopen("pedidos.bin", "rb"); // abre o arquivo para ser lido em binario
    if(arq==NULL) {
        printf("Erro em abrir arquivo\n");
        exit(1);
    }

    while (!feof(arq)) { // executa enquanto nao for o final do arq
        
        // tam corresponde ao numero de medicamentos DIFERENTES num pedido 
        fread(&tam, 1, sizeof(int), arq); // atribui o valor necessario para tam
        (*tamP)++; // incrementa o numero de pedidos

        // alocacao de memoria para mais esse pedido
        pedidos_tmp_f = pedidos_f;
        pedidos_f = (Pedido *) realloc(pedidos_tmp_f, (*tamP)*sizeof(Pedido));
        if(pedidos_f == NULL) {
            printf("Problema de alocacao de memoria\n");
            //                         -1 visto que nao eh necessario liberar a memoria alocada no ultimo pedido.tMed, visto que nao foi alocada memoria nele
            for (int i = 0; i < (*tamP)-1; i++) { free(pedidos_tmp_f[i].tMed); }
            free(pedidos_tmp_f);
            fclose(arq);
            exit(1);
        }

        // aloca espaco no vetor de medicamentos DESSE pedido, do pedido atual
        pedidos_f[(*tamP)-1].tMed = (TMed *) malloc( tam * sizeof(TMed)); // sera alocado apenas uma vez. por isso, malloc
        if(pedidos_f[(*tamP)-1].tMed == NULL) {
            printf("Problema de alocacao de memoria\n");
            for (int i = 0; i < (*tamP)-1; i++) { free(pedidos_tmp_f[i].tMed); }
            free(pedidos_tmp_f);
            fclose(arq);
            exit(1);
        }

        // ler os medicamenos DESSE pedido, do pedido atual e atribui ao tMed dele
        fread(pedidos_f[(*tamP)-1].tMed, tam, sizeof(TMed), arq);
    }
    
    fclose(arq);
    return pedidos_f;
}

void inicializa() {

    // OBSERVACAO IMPORTANTE: primeiramente, os monitores haviam dito que toda a main() deveria conter apenas a funcao
    // inicializa() e toda a manipulacao restante dos dados deveria ser feito nessa funcao, como feito abaixo.
    //
    // Apos um tempo, Marcela disse que tal uso da main() era opcional e a que ela poderia conter outras manipulacoes.
    //
    // Por isso, escolhi a primeira opcao e resolvi usar a funcao inicializa() para toda a manipulacao dos dados
    // e recebi a autorizadao da monitora Marcela para alterar o tipo da funcao para "void", como feito abaixo.

    TMed **coliseu_f=NULL, **coliseu_tpm_f=NULL;
    int tam_linha=20; // o tamanho da linha inicial eh 20
    int i_linha=0, i_coluna=0; // indice das linhas e colunas

    LocalM *locMed=NULL; // localizacao dos medicamentos
    Pedido *todosPedidos=NULL;
    int tamC=0, tamP=0; // tamanhos de locMed e pedidos

    // aloca as 20 linhas de altura
    coliseu_f = (TMed **) malloc(20 * sizeof(TMed *)); // aloca espaco para os 20
    if(coliseu_f == NULL) {
        printf("Problema de alocacao de memoria\n");
        // nao ha memoria alocada para ser liberada nesse caso, nao no escopo da funcao atual
        exit(1);
    }

    // aloca cada uma das 20 linhas do coliseu_f
    for (int i = 0; i < 20; i++) {
        
        // aloca a memoria devida para a linha atual
        coliseu_tpm_f = coliseu_f;
        coliseu_f[i] = (TMed *) malloc(tam_linha * sizeof(TMed));
        if(coliseu_f[i] == NULL) {
            printf("Problema de alocacao de memoria\n");
            for (int j = 0; j < i; j++) { // passa por todos os ponteiros de coliseu ja alocados
                free(coliseu_tpm_f[j]);
            }
            free(coliseu_tpm_f);
            exit(1);
        }

        // define a quantidade de medicamentos para 20, como dito no enunciado da funcao
        for (int w = 0; w < tam_linha; w++) { // passa por todos os medicamentos da linha atual
            coliseu_f[i][w].qtdM = 20;  
        }
    
        tam_linha += 2; // tam linha aumenta em 2 para a proxima alocacao de memoria
    }

    // carrega os vetores dinamicos com os dados com o uso das funcoes
    locMed = carregaConfig(&(tamC));
    todosPedidos = carregaPedidos(&(tamP));

    for (int i = 0; i < tamC; i++) { // passa por todos os medicamentos e atribui cada um de seus devidos nomes   
        strcpy((coliseu_f[locMed[i].linha][locMed[i].coluna].medic), locMed[i].medic);
    }
    
    processaPedidos(todosPedidos, tamP, coliseu_f, locMed, tamC);
    
}

void processaPedido(Pedido meuPedido, TMed **estoque, LocalM *config, int tamC) {

    FILE *arq=NULL;
    int i_linha=0, i_coluna=0;

    arq = fopen("pedidos.txt", "at");
    if(arq==NULL) {
        printf("Erro em abrir arquivo\n");
        for (int i = 0; i < 20; i++) { // passa por todas as linhas do coliseu, estoque
        free(estoque[i]);
        }
        free(estoque);
        free(config);
        exit(1);
    }

    for (int i = 0; i < meuPedido.qtd; i++) { // passa por todos os elementos de tMed desse pedido
        
        // encontra a posicao do medicamento no estoque, coliseu
        for (int j = 0; j < tamC; j++) { //passa por todos os elementos de config
            if(!strcmp(meuPedido.tMed[i].medic, config[j].medic)) { // se o nome do medicamento for correspondente
                i_linha = config[j].linha;
                i_coluna = config[j].coluna;
            }
        }
        
        // checa se a quantidade no estoque eh suficiente para suprir o pedido
        if((estoque[i_linha][i_coluna].qtdM) - (meuPedido.tMed[i].qtdM) >= 0) {
            // se sim, registra a separacao desse medicamento e decrementa essa valor a quantidade dele no estoque, coliseu
            fprintf(arq, "separei %d unidades do medicamento %s\n", meuPedido.tMed[i].qtdM, meuPedido.tMed[i].medic);  
            estoque[i_linha][i_coluna].qtdM -= meuPedido.tMed[i].qtdM;  
        }
        else {
            // se nao, informa que tal pedido nao pode ser atendido
            fprintf(arq, "Pedido correspondente a %d medicamentos %s nao pode ser atendido pois o estoque nao conta com uma quantidade suficiente para isso. Favor comunique um de nossos funcionarios\n", meuPedido.tMed[i].qtdM, meuPedido.tMed[i].medic);
        }
    }
    
    fclose(arq);
}

void processaPedidos(Pedido *todosPedidos, int tamP, TMed **estoque, LocalM *config, int tamC) {

    FILE *arq=NULL;

    arq = fopen("pedidos.txt", "wt");
    if(arq==NULL) {
        printf("Erro em abrir arquivo\n");
        for (int i = 0; i < tamP; i++) { // passa por todos os pedidos
            free(todosPedidos[i].tMed);
        }
        free(todosPedidos);
        for (int i = 0; i < 20; i++) { // passa por todas as linhas do coliseu, estoque
            free(estoque[i]);
        }
        free(estoque);
        free(config);
        exit(1);
    }
    fclose(arq); // abre e fecha apenas para criar o arquivo, garantir que ele existe

    for (int i = 0; i < tamP; i++) { // passa por todos os pedidos
        
        arq = fopen("pedidos.txt", "at"); // eh necessario 
        if(arq==NULL) {
            printf("Erro em abrir arquivo\n");
            for (int i = 0; i < tamP; i++) { // passa por todos os pedidos
                free(todosPedidos[i].tMed);
            }
            free(todosPedidos);
            for (int i = 0; i < 20; i++) { // passa por todas as linhas do coliseu, estoque
                free(estoque[i]);
            }
            free(estoque);
            free(config);
            exit(1);
            }
        
        for (int j = 0; j < 70; j++) { // imprime 70 vezes o caractere '+'
            fprintf(arq, "+");
        }
        fprintf(arq, "\n");
        fclose(arq); // foi necessario ficar abrindo e fechando o arquivo repetidas vezes pois arq nao eh argumento da funcao processaPedido, ou seja, nao esta no escopo dela

        processaPedido(todosPedidos[i], estoque, config, tamC);
    }
    
    // frees
    for (int i = 0; i < tamP; i++) { // passa por todos os pedidos
        free(todosPedidos[i].tMed);
    }
    free(todosPedidos);

    for (int i = 0; i < 20; i++) { // passa por todas as linhas do coliseu, estoque
        free(estoque[i]);
    }
    free(estoque);

    free(config);
}

int main() {

    inicializa();

    return 0;
}