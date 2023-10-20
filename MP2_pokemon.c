#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    int ataque, defesa;
} Pokemon;

typedef struct{
    char nome[30];
    Pokemon *pokebola;
    int nPokemons, pontuacao;
} Treinador;

Treinador *addTreinador(Treinador *treinadores, int *qtdCompetidores) {

    Treinador *treinadores_tmp=NULL;
    Treinador f_treinador_novo;

    (*qtdCompetidores)++;

    treinadores_tmp = treinadores;
    treinadores = (Treinador *) realloc(treinadores_tmp, (*qtdCompetidores)*(sizeof(Treinador)));
    if(treinadores==NULL && (*qtdCompetidores)!=0) { printf("Erro de alocacao de memoria\n"); for (int i = 0; i < (*qtdCompetidores); i++){free(treinadores_tmp[i].pokebola);} free(treinadores_tmp); exit(1); }
    // tudo numa linha pois, apesar de nao ser uma boa pratica, a linha acima so sera utilizada em raros casos em que ocorrera problema na alocacao de memoria

    printf("Digite o nome do Treinador que sera adicionado ao festival: ");
    scanf(" %29[^\n]", f_treinador_novo.nome);
    f_treinador_novo.nPokemons = 0;
    f_treinador_novo.pontuacao = 0;
    f_treinador_novo.pokebola = NULL;

    treinadores[(*qtdCompetidores)-1] = f_treinador_novo;

    return treinadores;
}

Treinador *removeTreinador(Treinador *treinadores, int *qtdCompetidores, int indexTreinador) {

    Treinador *treinadores_tmp=NULL;

    // remocao do treinadores[indexTreinador] e passa todos os depois dele um para "tras" para o realloc funcionar corretamente
    for (int i = indexTreinador; i < ((*qtdCompetidores)-1); i++) { // passa por todos os competidores, treinadores
        treinadores[i] = treinadores[i+1];  
    }
    (*qtdCompetidores)--;

    treinadores_tmp = treinadores;
    treinadores = (Treinador *) realloc(treinadores_tmp, (*qtdCompetidores)*(sizeof(Treinador)));
    if(treinadores==NULL && (*qtdCompetidores)!=0) { printf("Erro de alocacao de memoria\n"); for (int i = 0; i < (*qtdCompetidores); i++){free(treinadores_tmp[i].pokebola);} free(treinadores_tmp); exit(1); }

    return treinadores;
} // nao sera usado na main

Treinador *addPokemon(Treinador *treinadores, char *nomeTreinador, Pokemon pokemon, int qtdCompetidores) {

    Pokemon *f_treinadoresPokebola_tmp=NULL;
    int f_index_treinador=-1; // valor inicial servira como flag para caso o nome do jogador nao seja encontrado

    // primeiro, eh necessario encontrar o indice do treinador em questao, o f_index_treinador

    for (int i = 0; i < qtdCompetidores; i++) { // passa por todos os jogadores
        
        if(!strcmp(nomeTreinador, treinadores[i].nome)) {
            f_index_treinador = i;
        }
    }

    if(f_index_treinador>=0) {
        (treinadores[f_index_treinador].nPokemons)++; // incrementa o numero de pokemons do treinador

        // aloca a memoria para o pokemon novo
        f_treinadoresPokebola_tmp = treinadores[f_index_treinador].pokebola;
        treinadores[f_index_treinador].pokebola = (Pokemon *) realloc(f_treinadoresPokebola_tmp, (sizeof(Pokemon) * (treinadores[f_index_treinador].nPokemons)));
        if((treinadores[f_index_treinador].pokebola)==NULL && treinadores[f_index_treinador].nPokemons!=0) { printf("Erro de alocacao de memoria\n"); free(f_treinadoresPokebola_tmp); exit(1); }

        // atribui os dados do novo pokemon no vetor de pokemon do treinador na posicao correta
        treinadores[f_index_treinador].pokebola[(treinadores[f_index_treinador].nPokemons)-1] = pokemon;

        printf("Pokemon adicionado com sucesso!\n");
    }
    else {
        // ocorrera caso o nome do treinador digitado pelo usuario nao estiver adicionado no programa
        printf("Erro no cadastro do pokemon. Verifique se o nome do treinador foi escrito corretamente.\n");
    }

    return treinadores;
}

// vence o pokemon que (seu_ataque - defesa_oponente) for maior
// se o treinador tem -5 pontos eh desclassificado

char *batalha(Treinador **treinadores, char *nomeCompetidor1, char *nomeCompetidor2, int indexPokemon1, int indexPokemon2,int *qtdCompetidores) {

    int f_index_campeao=-1, f_index_perdedor=-1;
    int f_index_P1=-1, f_index_P2=-1; // incide dos jogadores 1 e 2
    int coef_bat_1=0, coef_bat_2=0; // coeficientes de batalha (seu_ataque - defesa_oponente)

    // primeiramente, encontra-se os indices de cada um dos competidores
    for (int i = 0; i < (*qtdCompetidores); i++) {
        if(!strcmp((*treinadores)[i].nome, nomeCompetidor1)) f_index_P1 = i;
        if(!strcmp((*treinadores)[i].nome, nomeCompetidor2)) f_index_P2 = i;
    }
    
    // considera-se que os coeficientes de batalha podem assumir valores negativos sem problemas
    coef_bat_1 = ((*treinadores)[f_index_P1].pokebola[indexPokemon1].ataque) - ((*treinadores)[f_index_P2].pokebola[indexPokemon2].defesa);
    coef_bat_2 = ((*treinadores)[f_index_P2].pokebola[indexPokemon2].ataque) - ((*treinadores)[f_index_P1].pokebola[indexPokemon1].defesa);

    // quem tiver o maior coeficiente, sera o campeao. considera-se que nao havera empates, como descrito no enunciado da questao
    if(coef_bat_1 > coef_bat_2) {
        f_index_campeao = f_index_P1; 
        f_index_perdedor = f_index_P2;
    }
    else {
        f_index_campeao = f_index_P2;
        f_index_perdedor = f_index_P1;
    }

    // atualizacao das pontuacoes
    (*treinadores)[f_index_campeao].pontuacao++;
    (*treinadores)[f_index_perdedor].pontuacao--;

    if(((*treinadores)[f_index_perdedor].pontuacao) == (-5)) { // em caso de desclassificacao

        *treinadores = removeTreinador((*treinadores), qtdCompetidores, f_index_perdedor);
    }

    return (*treinadores)[f_index_campeao].nome;
}

int main() {

    int escolha=0;
    Treinador *treinadores=NULL;
    int qtdCompetidores=0;
    char nomeTreinador[30] = "a";
    Pokemon pokemon;

    char nome_campeao[30] = "a", nomeCompetidor1[30] = "a", nomeCompetidor2[30] = "a";
    int indexPokemon1=-1, indexPokemon2=-1;

    while (escolha!=4) { // loop menu
        
        printf("\n\t\t\t------ Festival de Batalha - Menu Inicial ------\n\n\tEscolha uma opcao (digite apenas o numero dela):\n1. Adicionar Competidor\n2. Adicionar Pokemon\n3. Batalhar\n4. Sair do programa\n :. ");
        scanf("%d", &escolha);

        if(escolha!=4) {

            if(escolha==1) { // adicionar competidor

                treinadores = addTreinador(treinadores, &qtdCompetidores);
                printf("Competidor adicionado com sucesso!\n");

            }
            else if(escolha==2) { // adicionar pokemon
                
                printf("Digite o nome do nome do treinador em que esse pokemon sera adicionado: ");
                scanf(" %29[^\n]", nomeTreinador);
                printf("Certo! Agora, digite o nome do pokemon que sera adicionado: ");
                scanf(" %29[^\n]", pokemon.nome);
                printf("Beleza! Agora, digite, repsectivamente e separados por um espaco, os valores de ataque e defesa dele: ");
                scanf("%d %d", &pokemon.ataque, &pokemon.defesa);

                treinadores = addPokemon(treinadores, nomeTreinador, pokemon, qtdCompetidores);
            }
            else if(escolha==3) { // batalhar
                
                printf("Certo! Para comecar a batalha, digite o nome do primeiro competidor: "); scanf(" %29[^\n]", nomeCompetidor1);
                printf("Escolha o pokemon desse competidor para a batalha (digite seu indice): "); scanf("%d", &indexPokemon1);

                printf("Beleza! Agora, digite o nome do segundo competidor: "); scanf(" %29[^\n]", nomeCompetidor2);
                printf("Escolha o pokemon desse competidor para a batalha (digite seu indice): "); scanf("%d", &indexPokemon2);

                strcpy(nome_campeao, (batalha(&treinadores, nomeCompetidor1, nomeCompetidor2, indexPokemon1, indexPokemon2, &qtdCompetidores)));
                printf("A batalha foi acirrada mas o vencedor foi %s!!!!\n\n", nome_campeao);

            }
            else {
                printf("Digite um valor valido.\n");
                // visto que nesse ponto, nunca sera 4.
            }
        }
    }

    // liberando memoria alocada
    for (int i = 0; i < qtdCompetidores; i++) { // passa por todos os treinadores/competidores       
        free(treinadores[i].pokebola);   
    }
    free(treinadores);

    printf("Saindo...\n");
    
    return 0;
}