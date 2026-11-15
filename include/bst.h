#ifndef BST_H
#define BST_H

#define TAMANHO_TEXTO 80

typedef struct {
    int id;
    char nome_equipamento[TAMANHO_TEXTO];
    char tipo_equipamento[TAMANHO_TEXTO];
    char localizacao[TAMANHO_TEXTO];
} Registro;

typedef struct NoBST {
    Registro registro;
    struct NoBST *filho_esquerdo;
    struct NoBST *filho_direito;
} NoBST;

enum {
    BST_INSERCAO_SEM_MEMORIA = -1,
    BST_INSERCAO_DUPLICADA = 0,
    BST_INSERCAO_OK = 1
};

NoBST *bst_inserir(NoBST *raiz, Registro registro, int *status_insercao);
NoBST *bst_buscar(NoBST *raiz, int id);
NoBST *bst_remover(NoBST *raiz, int id);
void bst_listar(const NoBST *raiz);
void bst_liberar(NoBST *raiz);

#endif
