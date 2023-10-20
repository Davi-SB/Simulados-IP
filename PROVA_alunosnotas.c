#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[101];
    char CPF[12];
    int qtdNotas;
    float *notas;
    float media;
} Aluno;

Aluno *carregaAlunos (int *qtdAlunos) {

    Aluno *f_alunos=NULL, *f_alunos_tmp=NULL;  
    FILE *arq_alunos;
    Aluno f_aluno_atual;

    arq_alunos = fopen("D:\\Estudos\\Faculdade\\IP\\codes\\.vscode\\Simulados\\alunos.txt", "r");
    if(arq_alunos==NULL) { printf("Problema em abrir o arquivo\n"); exit(1); }
    
    while (!feof(arq_alunos)) {
        
        // armazena uma lihna temporariamente nas strings f_aluno_atual.nome e f_aluno_atual.CPF
        fscanf(arq_alunos, "%100[^','], %11[^\n]\n", f_aluno_atual.nome, f_aluno_atual.CPF); // feito para arquivos no formato "Nome Completo, 123456\n..."
        f_aluno_atual.notas=NULL; // inicializacao inicial para todo aluno
        f_aluno_atual.qtdNotas=0; // inicializacao inicial para todo aluno

        // alocacao de memoria
        (*qtdAlunos)++; // incrementa a quantidade de alunos

        f_alunos_tmp = f_alunos;
        f_alunos = (Aluno *) realloc(f_alunos_tmp, (sizeof(Aluno) * (*qtdAlunos)));
        if(f_alunos==NULL) { printf("Problema na alocacao de memoria\n"); for(int i=0; i<(*qtdAlunos); i++){ free(f_alunos_tmp[i].nome); free(f_alunos_tmp); exit(1); } }
    
        f_alunos[(*qtdAlunos)-1] = f_aluno_atual;
    }
    fclose(arq_alunos);
    
    return f_alunos;
}

float *leNotas(int *qtdNotas) {

    float f_nota_atual=99.99; // valor arbitrario apenas para entrar no while
    int n=1;
    float *f_notas_x=NULL; // representa o vetor de notas do aluno x
    float *f_notas_tmp=NULL;

    while (f_nota_atual>=0) { // >=0 --> nao ser negativo
        // armazenando a entrada do usuario
        printf("Nota %d: ", n); n++;
        scanf("%f", &f_nota_atual);
        (*qtdNotas)++;

        // alocando memoria
        f_notas_tmp = f_notas_x;
        f_notas_x = (float *) realloc(f_notas_tmp, ((*qtdNotas) * sizeof(float)));
        if(f_notas_x == NULL) { printf("Problema em alocar a memoria\n"); free(f_notas_tmp); exit(1); }

        // atribuindo os novos dados
        f_notas_x[(*qtdNotas)-1] = f_nota_atual;
    }

    return f_notas_x;
}

float media(float *notas, int qtdNotas) {

    float media=0.00, soma=0.00;

    for (int i = 0; i < qtdNotas; i++) {
        soma += notas[i];
    }
    media = (soma/qtdNotas);

    return media;
}

void ordena(Aluno *alunos, int qtdAlunos) {

    Aluno f_aluno_aux;

    for (int i = 0; i < qtdAlunos; i++) {
        for (int j = 0; j < qtdAlunos; j++) {
            if(alunos[i].media > alunos[j].media) { // swap
                f_aluno_aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = f_aluno_aux;
            }
        }
    }
    // crescente --> <rescente
    // decrescente --> >ecrescente
}

void salvaAlunos(Aluno *alunos, int qtdAlunos) {

    FILE *arq_final;

    arq_final = fopen("D:\\Estudos\\Faculdade\\IP\\codes\\.vscode\\Simulados\\resposta.bin", "w");
    if(arq_final==NULL) { printf("Erro na geracao de arquivo .bin"); exit(1); }

    for (int i = 0; i < qtdAlunos; i++) {
        fwrite(&(alunos[i]), sizeof(Aluno), 1, arq_final);
    }
    
    fclose(arq_final);
}

int main() {

    Aluno *alunos=NULL; // aponta inicialmente para NULL para evitar que haja problemas com a primeira alocacao de memoria por meio da funcao realloc(), caso haja
    int qtdAlunos=0; // inicialmente, a quantidade de alunos registrados eh zero
    int qtdNotas=0; // valor conta a quantidade de notas de cada aluno

    alunos = carregaAlunos(&qtdAlunos); // retorna o conteudo do arquivo alunos.txt para o vetor dinamico alunos, carrega o vet dinamico alunos

    /*
    for (int i = 0; i < qtdAlunos; i++) { // break point
        printf("Aluno %d: -%s- -%s-\n\n", i+1, alunos[i].nome, alunos[i].CPF);
    }
    */

    for (int i = 0; i < qtdAlunos; i++) { // armazena as notas
        printf("insira as notas do aluno %s abaixo\n", alunos[i].nome);

        qtdNotas=0; // reinicia o contador para entrar na funcao com seu valor inicial correto, ou seja, zero
        alunos[i].notas = leNotas(&qtdNotas); // le as notas
        alunos[i].qtdNotas = qtdNotas; // apos a leitura das notas, armazena esse dado na struct do aluno em questao
    }
    
    for (int i = 0; i < qtdAlunos; i++) {
        alunos[i].media = media(alunos[i].notas, alunos[i].qtdNotas);  
    }
    
    // bubble sort para ordenar o vetor alunos em ordem >ecrescende de media de notas de cada aluno
    ordena(alunos, qtdAlunos);

    // armazenamento desse vetor num arquivo binário
    salvaAlunos(alunos, qtdAlunos);
    
    // libera memoria alocada
    for (int i = 0; i < qtdAlunos; i++) {
        free(alunos[i].notas);
    }
    free(alunos);

    return 0;
}