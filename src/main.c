#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "estrutura.h"

#define TAMANHO_ENTRADA 256
#define ID_MINIMO 1
#define OPCAO_MINIMA 0
#define OPCAO_MAXIMA 7

static void exibir_menu(void)
{
    printf("\n");
    printf("==========================================\n");
    printf("      SISTEMA DE ESTRUTURA DE DADOS\n");
    printf("==========================================\n");
    printf("1 - Cadastrar registro na BST\n");
    printf("2 - Buscar registro por ID na BST\n");
    printf("3 - Remover registro da BST\n");
    printf("4 - Listar registros em-ordem\n");
    printf("5 - Inserir ID na estrutura linear\n");
    printf("6 - Remover da estrutura linear\n");
    printf("7 - Exibir estrutura linear\n");
    printf("0 - Encerrar\n");
    printf("==========================================\n");
}

static int ler_linha(char *linha_entrada, int tamanho_entrada)
{
    int caractere_lido;

    if (fgets(linha_entrada, tamanho_entrada, stdin) == NULL) {
        return -1;
    }
    if (strchr(linha_entrada, '\n') != NULL) {
        return 1;
    }
    while ((caractere_lido = getchar()) != '\n' && caractere_lido != EOF) {
    }
    return 0;
}

static int ler_inteiro_no_intervalo(int valor_minimo, int valor_maximo, int *valor_lido)
{
    char linha_entrada[TAMANHO_ENTRADA];
    char *fim_conversao;
    long valor_convertido;
    int resultado_leitura;

    resultado_leitura = ler_linha(linha_entrada, TAMANHO_ENTRADA);
    if (resultado_leitura != 1) {
        return resultado_leitura;
    }
    errno = 0;
    valor_convertido = strtol(linha_entrada, &fim_conversao, 10);
    if (fim_conversao == linha_entrada) {
        return 0;
    }
    while (*fim_conversao == ' ' || *fim_conversao == '\t' ||
           *fim_conversao == '\r' || *fim_conversao == '\n') {
        fim_conversao++;
    }
    if (*fim_conversao != '\0' || errno == ERANGE) {
        return 0;
    }
    if (valor_convertido < valor_minimo || valor_convertido > valor_maximo) {
        return 0;
    }
    *valor_lido = (int)valor_convertido;
    return 1;
}

static void remover_espacos_das_pontas(char *texto)
{
    int tamanho_texto = (int)strlen(texto);
    int posicao_inicio = 0;
    int posicao_fim = tamanho_texto;

    while (posicao_inicio < tamanho_texto &&
           (texto[posicao_inicio] == ' ' || texto[posicao_inicio] == '\t' ||
            texto[posicao_inicio] == '\r' || texto[posicao_inicio] == '\n')) {
        posicao_inicio++;
    }
    while (posicao_fim > posicao_inicio &&
           (texto[posicao_fim - 1] == ' ' || texto[posicao_fim - 1] == '\t' ||
            texto[posicao_fim - 1] == '\r' || texto[posicao_fim - 1] == '\n')) {
        posicao_fim--;
    }
    memmove(texto, texto + posicao_inicio, (size_t)(posicao_fim - posicao_inicio));
    texto[posicao_fim - posicao_inicio] = '\0';
}

static int ler_texto_valido(char *texto_lido)
{
    char linha_entrada[TAMANHO_ENTRADA];
    int tamanho_texto;
    int resultado_leitura;

    resultado_leitura = ler_linha(linha_entrada, TAMANHO_ENTRADA);
    if (resultado_leitura != 1) {
        return resultado_leitura;
    }
    remover_espacos_das_pontas(linha_entrada);
    tamanho_texto = (int)strlen(linha_entrada);
    if (tamanho_texto == 0 || tamanho_texto >= TAMANHO_TEXTO) {
        return 0;
    }
    strcpy(texto_lido, linha_entrada);
    return 1;
}

static void exibir_registro(const Registro *registro)
{
    printf("ID: %d\n", registro->id);
    printf("Nome do equipamento: %s\n", registro->nome_equipamento);
    printf("Tipo: %s\n", registro->tipo_equipamento);
    printf("Localizacao: %s\n", registro->localizacao);
}

static NoBST *cadastrar_registro(NoBST *raiz)
{
    Registro registro;
    int status_insercao;

    printf("ID: ");
    if (ler_inteiro_no_intervalo(ID_MINIMO, INT_MAX, &registro.id) != 1) {
        printf("ID invalido. Informe um inteiro positivo.\n");
        return raiz;
    }
    printf("Nome do equipamento: ");
    if (ler_texto_valido(registro.nome_equipamento) != 1) {
        printf("Nome invalido. Informe de 1 a 79 caracteres.\n");
        return raiz;
    }
    printf("Tipo: ");
    if (ler_texto_valido(registro.tipo_equipamento) != 1) {
        printf("Tipo invalido. Informe de 1 a 79 caracteres.\n");
        return raiz;
    }
    printf("Localizacao: ");
    if (ler_texto_valido(registro.localizacao) != 1) {
        printf("Localizacao invalida. Informe de 1 a 79 caracteres.\n");
        return raiz;
    }
    raiz = bst_inserir(raiz, registro, &status_insercao);
    if (status_insercao == BST_INSERCAO_OK) {
        printf("Registro cadastrado.\n");
    } else if (status_insercao == BST_INSERCAO_DUPLICADA) {
        printf("ID %d ja cadastrado.\n", registro.id);
    } else {
        printf("Sem memoria disponivel.\n");
    }
    return raiz;
}

static void buscar_registro(NoBST *raiz)
{
    NoBST *no_encontrado;
    int id_lido;

    printf("ID para busca: ");
    if (ler_inteiro_no_intervalo(ID_MINIMO, INT_MAX, &id_lido) != 1) {
        printf("ID invalido. Informe um inteiro positivo.\n");
        return;
    }
    no_encontrado = bst_buscar(raiz, id_lido);
    if (no_encontrado == NULL) {
        printf("Registro nao encontrado.\n");
        return;
    }
    exibir_registro(&no_encontrado->registro);
}

static NoBST *remover_registro(NoBST *raiz)
{
    int id_lido;

    printf("ID para remocao: ");
    if (ler_inteiro_no_intervalo(ID_MINIMO, INT_MAX, &id_lido) != 1) {
        printf("ID invalido. Informe um inteiro positivo.\n");
        return raiz;
    }
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return raiz;
    }
    if (bst_buscar(raiz, id_lido) == NULL) {
        printf("Registro nao encontrado.\n");
        return raiz;
    }
    raiz = bst_remover(raiz, id_lido);
    printf("Registro %d removido.\n", id_lido);
    return raiz;
}

int main(void)
{
    NoBST *raiz = NULL;
    Lista lista;
    int opcao;
    int id_lido;
    int id_removido;
    int resultado_leitura;
    int programa_em_execucao = 1;

    lista.no_inicio = NULL;
    lista.no_fim = NULL;
    while (programa_em_execucao) {
        exibir_menu();
        printf("Escolha uma opcao: ");
        resultado_leitura = ler_inteiro_no_intervalo(OPCAO_MINIMA, OPCAO_MAXIMA, &opcao);
        if (resultado_leitura == -1) {
            break;
        }
        if (resultado_leitura != 1) {
            printf("Opcao invalida.\n");
            continue;
        }
        switch (opcao) {
        case 1:
            raiz = cadastrar_registro(raiz);
            break;
        case 2:
            buscar_registro(raiz);
            break;
        case 3:
            raiz = remover_registro(raiz);
            break;
        case 4:
            if (raiz == NULL) {
                printf("Arvore vazia.\n");
            } else {
                printf("ID | Nome | Tipo | Localizacao\n");
                bst_listar(raiz);
            }
            break;
        case 5:
            printf("ID para inserir na estrutura linear: ");
            if (ler_inteiro_no_intervalo(ID_MINIMO, INT_MAX, &id_lido) != 1) {
                printf("ID invalido. Informe um inteiro positivo.\n");
                break;
            }
            lista_inserir(&lista, id_lido);
            printf("ID %d inserido na estrutura linear.\n", id_lido);
            break;
        case 6:
            if (lista_remover(&lista, &id_removido)) {
                printf("ID %d removido da estrutura linear.\n", id_removido);
            } else {
                printf("Estrutura linear vazia.\n");
            }
            break;
        case 7:
            lista_exibir(&lista);
            break;
        case 0:
            programa_em_execucao = 0;
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    }
    bst_liberar(raiz);
    lista_liberar(&lista);
    printf("Programa encerrado.\n");
    return 0;
}
