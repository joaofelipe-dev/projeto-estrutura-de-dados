#include <stdio.h>
#include <stdlib.h>

#include "estrutura.h"

void lista_inserir(Lista *lista, int id)
{
    NoLista *no_novo = malloc(sizeof(NoLista));

    if (no_novo == NULL) {
        printf("Sem memoria disponivel.\n");
        return;
    }
    no_novo->id = id;
    no_novo->proximo = NULL;
    if (lista->no_fim == NULL) {
        lista->no_inicio = no_novo;
    } else {
        lista->no_fim->proximo = no_novo;
    }
    lista->no_fim = no_novo;
}

int lista_remover(Lista *lista, int *id_removido)
{
    NoLista *no_inicio = lista->no_inicio;

    if (no_inicio == NULL) {
        return 0;
    }
    lista->no_inicio = no_inicio->proximo;
    if (lista->no_inicio == NULL) {
        lista->no_fim = NULL;
    }
    *id_removido = no_inicio->id;
    free(no_inicio);
    return 1;
}

void lista_exibir(const Lista *lista)
{
    const NoLista *no_atual = lista->no_inicio;

    if (no_atual == NULL) {
        printf("Estrutura linear vazia.\n");
        return;
    }
    while (no_atual != NULL) {
        printf("%d\n", no_atual->id);
        no_atual = no_atual->proximo;
    }
}

void lista_liberar(Lista *lista)
{
    NoLista *no_atual = lista->no_inicio;
    NoLista *no_proximo;

    while (no_atual != NULL) {
        no_proximo = no_atual->proximo;
        free(no_atual);
        no_atual = no_proximo;
    }
    lista->no_inicio = NULL;
    lista->no_fim = NULL;
}
