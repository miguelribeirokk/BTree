#include "btree.h"


void Inicializa(TipoApontador *Dicionario){
    *Dicionario = NULL;
}


void Insere_Externo(TipoRegistro Registro, TipoApontador *Ap_Pagina){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApAux;
    Insere_Interno(Registro, *Ap_Pagina, &Cresceu, &RegRetorno, &ApRetorno);
    if(Cresceu){ // Arvore cresce na altura pela raiz
        ApAux = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApAux->n = 1;
        ApAux->Vetor_Registro[0] = RegRetorno;
        ApAux->Vetor_Pagina[1] = ApRetorno;  //Nova pagina criada torna-se filha à direita
        ApAux->Vetor_Pagina[0] = *Ap_Pagina; //Antiga pagina raiz torna-se filha à esquerda
        *Ap_Pagina = ApAux; //Nova pagina raiz
    }
}

void Insere_Interno(TipoRegistro Registro, TipoApontador Apontador, short *Cresceu,
                    TipoRegistro *RegRetorno, TipoApontador *ApRetorno){;
    long i = 1; long j;
    TipoApontador ApAux;
    if(Apontador == NULL){ //Nova página criada, arvore cresce
        *Cresceu = true;
        (*RegRetorno) = Registro;
        (*ApRetorno) = NULL;
        return;
    }
    while(i < Apontador->n && Registro.Chave > Apontador->Vetor_Registro[i-1].Chave){
        /*Percorre os registros da página até encontrar o intervalo de
        inserção ou não haver mais registros*/
        i++;
    }
    if(Registro.Chave == Apontador->Vetor_Registro[i-1].Chave){
        printf("Erro: Registro ja existe\n");
        *Cresceu = false;
        return;
    }
    if(Registro.Chave < Apontador->Vetor_Registro[i-1].Chave){
        //Localiza a página filha ideal para inserção
        i--;
    }
    Insere_Interno(Registro, Apontador->Vetor_Pagina[i], Cresceu, RegRetorno, ApRetorno);
    if(!*Cresceu){
        return;
    }
    if(Apontador->n < 2*M){
        //Página tem espaço para inserção
        InsereNaPagina(Apontador, *RegRetorno, *ApRetorno);
        *Cresceu = false;
        return;
    }
    /*Overflow: Página tem que ser dividida*/
    ApAux = (TipoApontador)malloc(sizeof(TipoPagina));
    ApAux->n = 0;
    ApAux->Vetor_Pagina[0] = NULL;
    if(i < M+1){
        InsereNaPagina(ApAux, Apontador->Vetor_Registro[2*M-1], Apontador->Vetor_Pagina[2*M]);
        Apontador->n--;
        InsereNaPagina(Apontador, *RegRetorno, *ApRetorno);
    }
    else{
        InsereNaPagina(ApAux, *RegRetorno, *ApRetorno);
    }
    for(j = M+2; j <= 2*M ; j++){
        InsereNaPagina(ApAux, Apontador->Vetor_Registro[j-1], Apontador->Vetor_Pagina[j]);
    }
    Apontador->n = M;
    ApAux->Vetor_Pagina[0] = Apontador->Vetor_Pagina[M+1];
    *RegRetorno = Apontador->Vetor_Registro[M];
    *ApRetorno = ApAux;
}

void InsereNaPagina(TipoApontador Apontador, TipoRegistro Registro, TipoApontador ApDir){
    short NaoAchouPosicao;
    int k;
    k = Apontador->n;
    NaoAchouPosicao = (k>0);
    while(NaoAchouPosicao){
        if(Registro.Chave >= Apontador->Vetor_Registro[k-1].Chave){
            NaoAchouPosicao = false;
            break;
        }
        Apontador->Vetor_Registro[k] = Apontador->Vetor_Registro[k-1];
        Apontador->Vetor_Pagina[k+1] = Apontador->Vetor_Pagina[k];
        k--;
        if(k < 1){
            NaoAchouPosicao = false;
            break;
        }
    }
    Apontador->Vetor_Registro[k] = Registro;
    Apontador->Vetor_Pagina[k+1] = ApDir;
    Apontador->n++;
}

void Pesquisa(TipoRegistro *Registro, TipoApontador No){
    long i = 1;
    if(No == NULL){
        printf("Erro: Registro nao encontrado\n");
        return;
    }
    while(i < No->n && Registro->Chave > No->Vetor_Registro[i-1].Chave){
        i++;
    }
    if(Registro->Chave == No->Vetor_Registro[i-1].Chave){
        *Registro = No->Vetor_Registro[i-1];
        printf("Registro encontrado\n");
        printf("Nome: %s\n", Registro->Nome);
        printf("Matricula: %ld\n", Registro->Chave);
        return;
    }
    if (Registro->Chave < No->Vetor_Registro[i-1].Chave){
        Pesquisa(Registro, No->Vetor_Pagina[i-1]);
    }
    else{
        Pesquisa(Registro, No->Vetor_Pagina[i]);
    }
}

void Printar_Ordenado(TipoApontador Apontador){
    int i;
    if(Apontador == NULL){
        return;
    }
    for(i = 0; i < Apontador->n; i++){
        Printar_Ordenado(Apontador->Vetor_Pagina[i]);
        printf ("%s ", Apontador->Vetor_Registro[i].Nome);
        printf("%ld\n", Apontador->Vetor_Registro[i].Chave);
        
    }
    Printar_Ordenado(Apontador->Vetor_Pagina[i]);
}