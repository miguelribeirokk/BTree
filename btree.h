#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define M 2

typedef long TipoChave;

typedef struct TipoRegistro{
    TipoChave Chave;
    char Nome[100];
    /* outros campos */
}TipoRegistro;

typedef struct TipoPagina *TipoApontador;

typedef struct TipoPagina{
    short n;
    TipoRegistro Vetor_Registro[2*M];
    TipoApontador Vetor_Pagina[2*M+1];
}TipoPagina;

void Inicializa(TipoApontador *Dicionario);
void Insere_Externo(TipoRegistro Registro, TipoApontador *Ap_Pagina);
void Insere_Interno(TipoRegistro Registro, TipoApontador Apontador, short* Cresceu,TipoRegistro *RegRetorno, TipoApontador *ApRetorno);
void InsereNaPagina(TipoApontador Apontador, TipoRegistro Registro, TipoApontador ApDir);
void Pesquisa(TipoRegistro *Registro, TipoApontador No);
void Printar_Ordenado(TipoApontador Apontador);