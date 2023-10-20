#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome_c[101]; // nome do candidato
    int num_c; // numero do candidato
} Candidato;

typedef struct {
    Candidato *dep_fed_0; // deputado federal
    Candidato *dep_est_1; // deputado estadual
    Candidato *senador_2;
    Candidato *governador_3;
    Candidato *presidente_4;
    int qtdCandidatos[5];
} listaCandidatos;

typedef struct {
    char nome_e[101]; // nome eleitor
    char CPF_e[12]; // voto eleitor
} Eleitor;

typedef struct {
    Candidato *dono_votos;
    int n_votos
} TotalVoto;

listaCandidatos carregarCandidatos(char *nomeArq) {

    listaCandidatos listaC_f, *lista_tmp=NULL; // por padrao, todas as variaveis declaradas e existentes restritamente ao escopo da funcao receberao a marca "_f" ao final
    FILE *f_arq;
    char cargo_f[101]="a"; // inicializacao arbitraria de seguranca
    Candidato candidato_atual_f, *c_tmp=NULL;
    int i=-1;

    // antes de qualquer coisa, eh necessario garantir que os valores do vetor qtdCandidatos comece em zero
    for (int j = 0; j < 5; j++) {
        listaC_f.qtdCandidatos[i]=0;
    }
    
    // inicio da manipulacao do arquivo
    f_arq = fopen(nomeArq, "rt"); // nomeArq se refere ao nome do arquivo e "rt" indica que sera feita a leitura de um arquivo de texto
    if(f_arq==NULL) {printf("Problema em abrir arquivo\n"); exit(1);}

    while (!feof(f_arq)) { // enquanto nao for o final do arquivo, continua no loop
        
        // na ordem: cargo, nome, numero
        fscanf(f_arq, " %100[^','],%100[^,],%d\n", cargo_f, candidato_atual_f.nome_c, candidato_atual_f.num_c);

        // classificacao do cargo
        if(!strcmp(cargo_f, "deputada federal")) {
            i=0;
            (listaC_f.qtdCandidatos[i])++;

            // ajusta o tamanho para caber mais um candidato
            c_tmp = listaC_f.dep_fed_0;
            listaC_f.dep_fed_0 = (Candidato *) realloc(c_tmp, ((listaC_f.qtdCandidatos[i]) * sizeof(Candidato)));
            if(listaC_f.dep_fed_0 == NULL) { // verificacao de seguranca para caso de erro na alocacao da memoria
                printf("Erro na alocacao de memoria\n");
                free(c_tmp);
                //free(listaC_f.dep_fed_0);
                free(listaC_f.dep_est_1);
                free(listaC_f.senador_2);
                free(listaC_f.governador_3);
                free(listaC_f.presidente_4);
                exit(1);
            }

            // atribuicao do novo candidato no devido vetor dinamico
            listaC_f.dep_fed_0[(listaC_f.qtdCandidatos[i])-1] = candidato_atual_f;
        }

        else if (!strcmp(cargo_f, "deputada estadual")) {
            i=1;
            (listaC_f.qtdCandidatos[i])++;

            // ajusta o tamanho para caber mais um candidato
            c_tmp = listaC_f.dep_est_1;
            listaC_f.dep_est_1 = (Candidato *) realloc(c_tmp, ((listaC_f.qtdCandidatos[i]) * sizeof(Candidato)));
            if(listaC_f.dep_est_1 == NULL) { // verificacao de seguranca para caso de erro na alocacao da memoria
                printf("Erro na alocacao de memoria\n");
                free(c_tmp);
                free(listaC_f.dep_fed_0);
                //free(listaC_f.dep_est_1);
                free(listaC_f.senador_2);
                free(listaC_f.governador_3);
                free(listaC_f.presidente_4);
                exit(1);
            }

            // atribuicao do novo candidato no devido vetor dinamico
            listaC_f.dep_est_1[(listaC_f.qtdCandidatos[i])-1] = candidato_atual_f;

        }

        else if (!strcmp(cargo_f, "senador")) {
            i=2;
            (listaC_f.qtdCandidatos[i])++;

            // ajusta o tamanho para caber mais um candidato
            c_tmp = listaC_f.senador_2;
            listaC_f.senador_2 = (Candidato *) realloc(c_tmp, ((listaC_f.qtdCandidatos[i]) * sizeof(Candidato)));
            if(listaC_f.senador_2 == NULL) { // verificacao de seguranca para caso de erro na alocacao da memoria
                printf("Erro na alocacao de memoria\n");
                free(c_tmp);
                free(listaC_f.dep_fed_0);
                free(listaC_f.dep_est_1);
                //free(listaC_f.senador_2);
                free(listaC_f.governador_3);
                free(listaC_f.presidente_4);
                exit(1);
            }
            // atribuicao do novo candidato no devido vetor dinamico
            listaC_f.senador_2[(listaC_f.qtdCandidatos[i])-1] = candidato_atual_f;

        }

        else if (!strcmp(cargo_f, "governador")) {
            i=3;
            (listaC_f.qtdCandidatos[i])++;

            // ajusta o tamanho para caber mais um candidato
            c_tmp = listaC_f.governador_3;
            listaC_f.governador_3 = (Candidato *) realloc(c_tmp, ((listaC_f.qtdCandidatos[i]) * sizeof(Candidato)));
            if(listaC_f.governador_3 == NULL) { // verificacao de seguranca para caso de erro na alocacao da memoria
                printf("Erro na alocacao de memoria\n");
                free(c_tmp);
                free(listaC_f.dep_fed_0);
                free(listaC_f.dep_est_1);
                free(listaC_f.senador_2);
                //free(listaC_f.governador_3);
                free(listaC_f.presidente_4);
                exit(1);
            }
            // atribuicao do novo candidato no devido vetor dinamico
            listaC_f.governador_3[(listaC_f.qtdCandidatos[i])-1] = candidato_atual_f;

        }

        else if (!strcmp(cargo_f, "presidente")) {
            i=4;
            (listaC_f.qtdCandidatos[i])++;

            // ajusta o tamanho para caber mais um candidato
            c_tmp = listaC_f.presidente_4;
            listaC_f.presidente_4 = (Candidato *) realloc(c_tmp, ((listaC_f.qtdCandidatos[i]) * sizeof(Candidato)));
            if(listaC_f.presidente_4 == NULL) { // verificacao de seguranca para caso de erro na alocacao da memoria
                printf("Erro na alocacao de memoria\n");
                free(c_tmp);
                free(listaC_f.dep_fed_0);
                free(listaC_f.dep_est_1);
                free(listaC_f.senador_2);
                free(listaC_f.governador_3);
                //free(listaC_f.presidente_4);
                exit(1);
            }
            // atribuicao do novo candidato no devido vetor dinamico
            listaC_f.presidente_4[(listaC_f.qtdCandidatos[i])-1] = candidato_atual_f;
        }

    }

    fclose(f_arq); // fecha o arquivo
    return listaC_f;
}

Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores) {

    FILE *f_arq=NULL;
    Eleitor eleitor_atual_f, *listaE_f=NULL, *e_tmp=NULL;

    // inicio da manipulacao do arquivo
    f_arq = fopen(nomeArq, "rt"); // nomeArq se refere ao nome do arquivo e "rt" indica que sera feita a leitura de um arquivo de texto
    if(f_arq==NULL) {printf("Problema em abrir arquivo\n"); exit(1);}

    while (!feof(f_arq)){ // enquanto nao for o final do arquivo, continua no loop

        fscanf(f_arq, " %11[^','],%100[^\n]\n", eleitor_atual_f.CPF_e, eleitor_atual_f.nome_e);
        (*qtdEleitores)++;

        // ajusta o tamanho da memoria alocada
        e_tmp = listaE_f;
        listaE_f = (Eleitor *) realloc(e_tmp, ((*qtdEleitores) * sizeof(Eleitor)));
        if(listaE_f==NULL) {
            printf("Problema na alocacao de memoria\n");
            free(e_tmp);
            exit(1);
        }

        // atribui o novo eleitor ao vetor de eleitores no ultimo espaco, indice (tam-1)
        listaE_f[(*qtdEleitores)-1] = eleitor_atual_f;
    } 

    fclose(f_arq);
    return listaE_f;
}

int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt) {

    int retorno_f=0;
    int flag_saida=1; // permite o programa sair do loop assim que encontra o candidato procurado

    for (int i = 0; (i < 5) && flag_saida; i++) { // passa por todos os cargos dos candidatos
        for (int j = 0; j < (listaC.qtdCandidatos[i]) && flag_saida; j++) { // passa por todos os canditados do cargo
            if (i==0) { // dep_fed
                // se o nome e numero forem iguais
                if ((!strcmp(candidatoAt.nome_c, listaC.dep_fed_0[j].nome_c)) && (candidatoAt.num_c == listaC.dep_fed_0[j].num_c)) {
                    retorno_f=1;
                    flag_saida=0;
                }
            }
            else if(i==1) { // dep_est
                if ((!strcmp(candidatoAt.nome_c, listaC.dep_est_1[j].nome_c)) && (candidatoAt.num_c == listaC.dep_est_1[j].num_c)) {
                    retorno_f=1;
                    flag_saida=0;
                }
            }
            else if(i==2) { // senador
                if ((!strcmp(candidatoAt.nome_c, listaC.senador_2[j].nome_c)) && (candidatoAt.num_c == listaC.senador_2[j].num_c)) {
                    retorno_f=1;
                    flag_saida=0;
                }
            }
            else if(i==3) { // governador
                if ((!strcmp(candidatoAt.nome_c, listaC.governador_3[j].nome_c)) && (candidatoAt.num_c == listaC.governador_3[j].num_c)) {
                    retorno_f=1;
                    flag_saida=0;
                }
            }
            else if(i==4) { // presidente
                if ((!strcmp(candidatoAt.nome_c, listaC.presidente_4[j].nome_c)) && (candidatoAt.num_c == listaC.presidente_4[j].num_c)) {
                    retorno_f=1;
                    flag_saida=0;
                }
            } 
        }
    }
    
    return retorno_f;
}

int verificaEleitor(Eleitor *listaE, int qtdEleitores, Eleitor eleitorAt) {

    int retorno_f=0;

    for (int i = 0; i < qtdEleitores; i++) { // passa por todos os eleitores

        // se o CPF e nome forem iguais
        if(!strcmp(listaE[i].CPF_e, eleitorAt.CPF_e) && !strcmp(listaE[i].nome_e, eleitorAt.nome_e)) {
            retorno_f=1;
        }
    }

    return retorno_f;
}

Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo) {

    int i=-1;
    Candidato *c_procurado_f=NULL;

    // define o indice do cargo no vetor qtdCandidatos
    if(!strcmp(cargo, "deputada federal"))       i=0; 
    else if(!strcmp(cargo, "deputada estadual")) i=1;
    else if(!strcmp(cargo, "senador"))           i=2;
    else if(!strcmp(cargo, "governador"))        i=3;
    else if(!strcmp(cargo, "presidente"))        i=4;

    if (i==0) {
        for (int j = 0; j < (listaC.qtdCandidatos[i]); j++) { // passa por todos os candidatos do cargo            
            if((!strcmp(candidatoAt.nome_c, listaC.dep_fed_0[j].nome_c)) && (candidatoAt.num_c == listaC.dep_fed_0[j].num_c)) {
                c_procurado_f = &(listaC.dep_fed_0[j]);
            }
        }
    }
    else if(i==1) {
        for (int j = 0; j < (listaC.qtdCandidatos[i]); j++) { // passa por todos os candidatos do cargo            
            if((!strcmp(candidatoAt.nome_c, listaC.dep_est_1[j].nome_c)) && (candidatoAt.num_c == listaC.dep_est_1[j].num_c)) {
                c_procurado_f = &(listaC.dep_est_1[j]);
            }
        }
    }
    else if(i==2) {
        for (int j = 0; j < (listaC.qtdCandidatos[i]); j++) { // passa por todos os candidatos do cargo            
            if((!strcmp(candidatoAt.nome_c, listaC.senador_2[j].nome_c)) && (candidatoAt.num_c == listaC.senador_2[j].num_c)) {
                c_procurado_f = &(listaC.senador_2[j]);
            }
        }
    }
    else if(i==3) {
        for (int j = 0; j < (listaC.qtdCandidatos[i]); j++) { // passa por todos os candidatos do cargo
            if((!strcmp(candidatoAt.nome_c, listaC.governador_3[j].nome_c)) && (candidatoAt.num_c == listaC.governador_3[j].num_c)) {
                c_procurado_f = &(listaC.governador_3[j]);
            }
        }
    }
    else if(i==4) {
        for (int j = 0; j < (listaC.qtdCandidatos[i]); j++) { // passa por todos os candidatos do cargo            
            if((!strcmp(candidatoAt.nome_c, listaC.presidente_4[j].nome_c)) && (candidatoAt.num_c == listaC.presidente_4[j].num_c)) {
                c_procurado_f = &(listaC.presidente_4[j]);
            }
        }
    }
    
    return c_procurado_f;
}

void apresentaResultado(TotalVoto *votos, int qtdCandidatos) {

}

int main() {

    listaCandidatos listaC;     
    Eleitor *listaE=NULL;// ponteiros, sempre que declarados pontando para NULL, visam evitar problemas caso a primeira alocacao de memoria seja por meio de um realloc
    int qtdEleitores=0; // inicialmente, a quantidade eh zero

    FILE *nomeArq=NULL;

    TotalVoto *votos=NULL;

    char CPF_buffer[12]="0"; // CPF digitado pelo usuario, comeca como 0 para entrar no laco (while)
    int escolha=0;

    // uma string, logo, char*, argumento esperado pela funcao
    listaC = carregarCandidatos("candidatos.txt");

    listaE = carregarEleitores("eleitores.txt", &qtdEleitores);

    while (escolha!=3) {
        
        printf("\n\t\t---------- Menu eleitoral ----------\n\n\tEscolha uma opcao (digite apenas o numero dela)\n1. Votar\n2. Apresentar votacao atual\n3. Sair\n :. ");
        scanf("%d", &escolha);

        if(escolha==1) { // votar



        }
        else if(escolha==2) { // apresentar
            for (int w = 0; w < 5; w++) {
                apresentaResultado(votos, listaC.qtdCandidatos[w]);
            }
        }
        else if(escolha==3) {
            printf("Saindo...");
        }
        else {
            printf("Digite uma opcao valida\n");
        }
    }
    

    // obs: considera-se que strcmp("0", "01") retorna true
    while (scanf(" %11[^\n]", CPF_buffer) && strcmp(CPF_buffer, "-1")) { // quando CPF_buffer for "-1", sai do laco pois strcmp vai retornar 0, ou seja, false
        
        

    }
    
    // libera a memoria alocada

    return 0;
}
