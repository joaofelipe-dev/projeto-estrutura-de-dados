#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

static NoBST *criar_no(Registro registro)
{
    NoBST *no_novo = malloc(sizeof(NoBST));

    if (no_novo == NULL) {
        return NULL;
    }
    no_novo->registro = registro;
    no_novo->filho_esquerdo = NULL;
    no_novo->filho_direito = NULL;
    return no_novo;
}

NoBST *bst_inserir(NoBST *raiz, Registro registro, int *status_insercao)
{
    if (raiz == NULL) {
        NoBST *no_novo = criar_no(registro);

        if (no_novo == NULL) {
            *status_insercao = BST_INSERCAO_SEM_MEMORIA;
            return NULL;
        }
        *status_insercao = BST_INSERCAO_OK;
        return no_novo;
    }
    if (registro.id == raiz->registro.id) {
        *status_insercao = BST_INSERCAO_DUPLICADA;
        return raiz;
    }
    if (registro.id < raiz->registro.id) {
        raiz->filho_esquerdo = bst_inserir(raiz->filho_esquerdo, registro, status_insercao);
    } else {
        raiz->filho_direito = bst_inserir(raiz->filho_direito, registro, status_insercao);
    }
    return raiz;
}

NoBST *bst_buscar(NoBST *raiz, int id)
{
    NoBST *no_atual = raiz;

    while (no_atual != NULL) {
        if (id == no_atual->registro.id) {
            return no_atual;
        }
        if (id < no_atual->registro.id) {
            no_atual = no_atual->filho_esquerdo;
        } else {
            no_atual = no_atual->filho_direito;
        }
    }
    return NULL;
}

static NoBST *menor_no_da_subarvore(NoBST *raiz)
{
    NoBST *no_atual = raiz;

    while (no_atual->filho_esquerdo != NULL) {
        no_atual = no_atual->filho_esquerdo;
    }
    return no_atual;
}

NoBST *bst_remover(NoBST *raiz, int id)
{
    NoBST *no_sucessor;

    if (raiz == NULL) {
        return NULL;
    }
    if (id < raiz->registro.id) {
        raiz->filho_esquerdo = bst_remover(raiz->filho_esquerdo, id);
        return raiz;
    }
    if (id > raiz->registro.id) {
        raiz->filho_direito = bst_remover(raiz->filho_direito, id);
        return raiz;
    }
    if (raiz->filho_esquerdo == NULL) {
        no_sucessor = raiz->filho_direito;
        free(raiz);
        return no_sucessor;
    }
    if (raiz->filho_direito == NULL) {
        no_sucessor = raiz->filho_esquerdo;
        free(raiz);
        return no_sucessor;
    }
    no_sucessor = menor_no_da_subarvore(raiz->filho_direito);
    raiz->registro = no_sucessor->registro;
    raiz->filho_direito = bst_remover(raiz->filho_direito, no_sucessor->registro.id);
    return raiz;
}

void bst_listar(const NoBST *raiz)
{
    if (raiz == NULL) {
        return;
    }
    bst_listar(raiz->filho_esquerdo);
    printf("%d | %s | %s | %s\n",
           raiz->registro.id,
           raiz->registro.nome_equipamento,
           raiz->registro.tipo_equipamento,
           raiz->registro.localizacao);
    bst_listar(raiz->filho_direito);
}

void bst_liberar(NoBST *raiz)
{
    if (raiz == NULL) {
        return;
    }
    bst_liberar(raiz->filho_esquerdo);
    bst_liberar(raiz->filho_direito);
    free(raiz);
}
