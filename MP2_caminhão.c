#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// dsb

typedef struct {
    char Placa[6];
} Caminhao;

typedef struct {
    int codigo;
    float loc_x, loc_y;
    Caminhao *caminhao;
    int n_caminhao;
} Filial;

typedef struct {
    float origem_x, origem_y;
    float destino_x, destino_y;
} Produto;

Filial *cadastrar_filial(Filial *filiais, int *n_filiais) {

    Filial f_filial; // sera temporaria para preenchimento dos dados na funcao

    Filial *filiais_temp=NULL;
    
    (*n_filiais)++;

    filiais_temp = filiais;
    filiais = (Filial *) realloc(filiais_temp, ((*n_filiais) * sizeof(Filial))); 
    if(filiais==NULL) { printf("Erro de alocacao de memoria\n"); free(filiais_temp); exit(1); } // como dar free no resto dos ponteiros que essa funcao nem tem acesso?
    // espaco alocado n_filiais atualizado, abaixo comeca o preenchimento de informacoes

    printf("Digite a locaizacao em x e y, respectivamente, da nova filial separados por um espaco!\n :. ");
    scanf("%f %f", &f_filial.loc_x, &f_filial.loc_y);

    f_filial.codigo = ((*n_filiais)-1); // indice no vetor de filiais 
    // o codigo da filial sera igual ao indice dela no vetor de filiais 
    // Assim, como nenhuma sera removida, os codigos das filiais ficarao no tipo 0, 1, 2, 3, 4...
    
    f_filial.n_caminhao = 0; // inicialmente, o num de caminhoes eh zero
    f_filial.caminhao = NULL; // inicialmente NULL para evitar problemas com a primeira alocacao de memoria em caso de ser um realloc e nao malloc

    filiais[(*n_filiais)-1] = f_filial;
    
    for (int i = 0; i < n_filiais; i++) {free(filiais_temp[i].caminhao);}
    free(filiais_temp);

    return filiais;
}

 void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial) {

    Caminhao f_caminhao;
    strcpy(f_caminhao.Placa, caminhao.Placa);

    Caminhao *caminhao_tmp=NULL;
    caminhao_tmp = filiais[codigo_filial].caminhao;

    filiais[codigo_filial].caminhao = (Caminhao *) realloc(caminhao_tmp, ((sizeof(Caminhao)) * ((filiais[codigo_filial].n_caminhao)+1) ));
    // realloc em tamanho atual + tamanho de mais um caminhao
    if(filiais[codigo_filial].caminhao==NULL) { printf("Erro de alocacao de memoria\n"); free(caminhao_tmp); exit(1);}

    filiais[codigo_filial].caminhao[filiais[codigo_filial].n_caminhao - 1] = f_caminhao;
    // -1 importante pois o indice eh o tamanho-1


    free(caminhao_tmp);
}

void imprimir_filiais(Filial *filiais, int n_filiais) {

    int n_caminhoes=0;

    printf("\n\n\t\t- RELATORIO DE FILIAIS E SEUS CAMINHOES -\n");

    for (int i = 0; i < n_filiais; i++) { // passa por todas as filiais
        
        n_caminhoes = filiais[i].n_caminhao;
        printf("\t\tFilial %d:\n\tCodigo: %d\n", i+1, filiais[i].codigo);

        for (int j = 0; j < n_caminhoes; j++) {
            
            printf("Placa caminhao %d: %s\n", j+1, filiais[i].caminhao[j].Placa);

        }
        printf("\n");
    }
}

void remover_caminhao(Filial *filiais, int codigo_filial) {

    Caminhao *caminhao_tmp = NULL;

    caminhao_tmp = filiais[codigo_filial].caminhao;
    filiais[codigo_filial].caminhao = (Caminhao * ) realloc(caminhao_tmp, (filiais[codigo_filial].n_caminhao - 1) * sizeof(Caminhao));

    if(filiais[codigo_filial].caminhao==NULL) { printf("Erro de alocacao de memoria\n"); free(caminhao_tmp); exit(1); }

    free(caminhao_tmp);
}

void realizar_entrega(Filial *filiais, Produto produto, int n_filiais) {

    float dist_filial_origem=0.0, dist_filial_origem_ganhando=999.9; // valor para entrar no if pela primeira vez
    int codigo_ganhando=0, n_caminhoes_ganhador=0;
    Caminhao caminhao_aux;
    char placa_aux[6] = "a";

    // escolha da filial mais proxima da orgigem do produto
    for (int i = 0; i < n_filiais; i++) { // passa por todas as filiais
        
        dist_filial_origem = sqrt(pow(fabs(filiais[i].loc_x - produto.origem_x), 2) + pow(fabs(filiais[i].loc_y - produto.origem_y), 2));
        // raiz quadrada do modulo ao quadrado da dist em x + dist em y

        if(dist_filial_origem < dist_filial_origem_ganhando) {

            dist_filial_origem_ganhando = dist_filial_origem;
            codigo_ganhando = filiais[i].codigo;
            n_caminhoes_ganhador = filiais[i].n_caminhao;
            strcpy(placa_aux, filiais[i].caminhao[n_caminhoes_ganhador-1].Placa);
        }
    } // ao final desse for, codigo_ganhando é o codigo da filial mais perto da origem
    //  placa_aux eh a placa do caminhao que sera cadastrado na filial mais proxida do destino apos a entrega

    remover_caminhao(filiais, codigo_ganhando);

    float dist_destino_filial=0.0, dist_destino_filial_ganhando=999.9; // valor para entrar no if pela primeira vez
    int codigo_ganhando_2=0;

    //escolha da filial mais proxima do destino do produto
    for (int i = 0; i < n_filiais; i++) { // passa por todas as filiais
        
        dist_filial_origem = sqrt(pow(fabs(filiais[i].loc_x - produto.destino_x), 2) + pow(fabs(filiais[i].loc_y - produto.destino_y), 2));
        // raiz quadrada do modulo ao quadrado da dist em x + dist em y

        if(dist_destino_filial < dist_destino_filial_ganhando) {

            dist_destino_filial_ganhando = dist_destino_filial;
            codigo_ganhando_2 = filiais[i].codigo;
        }
    } // ao final desse for, codigo_ganhando_2 é o codigo da filial mais perto do destino

    strcpy(caminhao_aux.Placa, placa_aux);
    cadastrar_caminhao(filiais, caminhao_aux, codigo_ganhando_2);
}

int main() {

    int escolha_menu=0;
    int n_filiais=0;
    Filial *filiais=NULL;

    Caminhao caminhao;
    int codigo_filial=0;
    Produto produto;

    while (escolha_menu!=5){

        printf("\n\t\t\tMENU INICIAL\n\n\tEscolha uma opcao (digite apenas o numero dela):\n1. Cadastrar filial\n2. Cadastrar caminhao\n3. Realizar entrega\n4. Imprimir filiais\n5. Sair\n :. ");
        scanf("%d", &escolha_menu);

        if(escolha_menu!=5) {
            if(escolha_menu==1) { // cadastrar filial

                filiais = cadastrar_filial(filiais, &n_filiais);

                printf("Filial cadastrada com sucesso!\n");

            }
            else if(escolha_menu==2) { // cadastrar caminhao

                printf("Para o cadastro de um novo caminhao, digite sua placa (maximo de 5 caracteres) e o codigo da filial em que ele pertence separados por um espaco\n :. ");
                scanf(" %5[^' '] %d", caminhao.Placa, &codigo_filial);

                cadastrar_caminhao(filiais, caminhao, codigo_filial);

                printf("Caminhao cadastrado com sucesso!\n");

            }
            else if (escolha_menu==3) { // realizar entrega
                
                printf("\tPara realizar uma entrega, insira os seguintes dados:\n");

                printf("Origem x e y, respectivamente, separados por um espaco: ");
                scanf("%f %f", &produto.origem_x, &produto.origem_y);
                printf("Agora, o destino x e y, respectivamente, separados por um espaco: ");
                scanf("%f %f", &produto.destino_x, &produto.destino_y);

                realizar_entrega(filiais, produto, n_filiais);

                printf("Entrega realizada com sucesso!\n");

            }
            else if(escolha_menu==4) { // imprimir filiais

                imprimir_filiais(filiais, n_filiais);

            }
            else {
                printf("Escolha um valor valido\n");
            }
        }
    }
    
    //frees
    for (int i = 0; i < n_filiais; i++) {free(filiais[i].caminhao);}
    free(filiais);
    
    return 0;
}