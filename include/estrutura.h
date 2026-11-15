#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef struct NoLista {
    int id;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *no_inicio;
    NoLista *no_fim;
} Lista;

void lista_inserir(Lista *lista, int id);
int lista_remover(Lista *lista, int *id_removido);
void lista_exibir(const Lista *lista);
void lista_liberar(Lista *lista);

#endif
