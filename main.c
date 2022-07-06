
#include "btree.h"

int main(){
    //Inserir 10 chaves
    TipoRegistro Registro;
    TipoApontador Apontador;
    Inicializa(&Apontador);
    int i;
    FILE *fp;
    fp = fopen("nomes.txt", "r");
    while(fscanf(fp, "%s", Registro.Nome) != EOF){
        fscanf(fp, "%ld", &Registro.Chave);
        Insere_Externo(Registro, &Apontador);
    }
    //Pesquisar chaves
    printf("Pesquise por uma chave:\n");
    scanf("%d", &i);
    Registro.Chave = i;
    Pesquisa(&Registro, Apontador);
    printf("Printar ordenado ou encerrar? (0/1): ");
    scanf("%d", &i);
    if(i == 0){
        printf("\n");
        Printar_Ordenado(Apontador);
    }
    else{
        return 0;
    }
    return 0;
}