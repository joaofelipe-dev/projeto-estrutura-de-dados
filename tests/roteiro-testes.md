# Roteiro de testes

Todos os casos abaixo estão no arquivo `tests/entrada_teste.txt`, na ordem em que
aparecem. Para reproduzir, execute a partir da raiz do projeto:

```
gcc -std=c11 -Wall -Wextra -Iinclude -o projeto.exe src/main.c src/bst.c src/estrutura.c
projeto.exe < tests/entrada_teste.txt
```

Tema A (equipamentos de rede), estrutura linear: lista encadeada.
Árvore usada nos testes de remoção:

```
            50
           /  \
         30    70
        / \   /  \
       20 40 60  80
              \
              65
```

| # | Caso | Entrada | Resultado esperado | Resultado obtido |
|---|------|---------|--------------------|------------------|
| 1 | Inserir registro válido | `1` / `50` / `Roteador principal` / `Cisco` / `Bloco A` | Registro cadastrado | Registro cadastrado |
| 2 | Inserir os 8 registros da árvore | IDs 50, 30, 70, 20, 40, 60, 80, 65 | 8 cadastros | 8 vezes "Registro cadastrado" |
| 3 | ID duplicado | `1` / `50` / `Roteador repetido` / ... | Rejeita e avisa | `ID 50 ja cadastrado.` |
| 4 | ID zero | `1` / `0` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 5 | ID negativo | `1` / `-5` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 6 | ID não numérico | `1` / `abc` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 7 | ID com texto depois do número | `1` / `12x` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 8 | ID fora do intervalo de int | `1` / `99999999999` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 9 | Nome vazio | `1` / `99` / (linha vazia) | Rejeita | `Nome invalido. Informe de 1 a 79 caracteres.` |
| 10 | Nome só com espaços | `1` / `99` / `   ` | Rejeita | `Nome invalido. Informe de 1 a 79 caracteres.` |
| 11 | Nome com 80 caracteres | `1` / `99` / 80 letras A | Rejeita | `Nome invalido. Informe de 1 a 79 caracteres.` |
| 12 | Nome com 79 caracteres | `1` / `100` / 79 letras A / `Equipamento com nome no limite` / `Sala 3` | Cadastra | Registro cadastrado |
| 13 | Buscar ID existente | `2` / `50` | Mostra os 4 campos | ID 50, Roteador principal, Cisco, Bloco A |
| 14 | Buscar ID inexistente | `2` / `999` | Avisa | `Registro nao encontrado.` |
| 15 | Buscar com ID inválido | `2` / `abc` | Rejeita | `ID invalido. Informe um inteiro positivo.` |
| 16 | Listar em-ordem | `4` | IDs crescentes: 20, 30, 40, 50, 60, 65, 70, 80, 100 | IDs crescentes na ordem esperada |
| 17 | Remover folha | `3` / `20` | Remove | `Registro 20 removido.` |
| 18 | Remover nó com um filho | `3` / `60` (filho 65 sobe) | Remove e mantém 65 | `Registro 60 removido.` |
| 19 | Remover nó com dois filhos | `3` / `70` (sucessor 80) | Remove e mantém 65 e 80 | `Registro 70 removido.` |
| 20 | Remover ID inexistente | `3` / `999` | Avisa | `Registro nao encontrado.` |
| 21 | Listar depois das remoções | `4` | 30, 40, 50, 65, 80, 100 | 30, 40, 50, 65, 80, 100 |
| 22 | Inserir ID na lista | `5` / `50` | Insere no fim | `ID 50 inserido na estrutura linear.` |
| 23 | Inserir ID repetido na lista | `5` / `50` de novo | Aceita | `ID 50 inserido na estrutura linear.` |
| 24 | Inserir ID que não existe na BST | `5` / `7` | Aceita | `ID 7 inserido na estrutura linear.` |
| 25 | Exibir lista | `7` | 50, 50, 7 (início ao fim) | 50, 50, 7 |
| 26 | Remover da lista três vezes | `6` | 50, 50, 7 | 50, 50, 7 removidos nessa ordem |
| 27 | Remover de lista vazia | `6` | Avisa e continua | `Estrutura linear vazia.` |
| 28 | Exibir lista vazia | `7` | Avisa | `Estrutura linear vazia.` |
| 29 | Remover todos os nós da BST | `3` / 30, 40, 65, 80, 50 e 100 | 6 remoções | 6 remoções |
| 30 | Listar árvore vazia | `4` | Avisa | `Arvore vazia.` |
| 31 | Remover de árvore vazia | `3` / `10` | Avisa e continua | `Arvore vazia.` |
| 32 | Opção de menu inválida | `9` e `abc` | Rejeita e volta ao menu | `Opcao invalida.` |
| 33 | Encerrar | `0` | Libera a memória e termina | `Programa encerrado.` |

## Memória

O programa libera a árvore em `bst_liberar` e a lista em `lista_liberar` antes de
encerrar. Na remoção com dois filhos, o registro do sucessor é copiado para o nó
e o nó do sucessor é liberado uma única vez com `free`.

O Valgrind não existe no Windows, onde o projeto foi desenvolvido. A verificação
usada foi a execução repetida do roteiro completo (inserir, remover e encerrar)
sem erros. Em ambiente Linux, a mesma entrada pode ser verificada com:

```
valgrind --leak-check=full ./projeto < tests/entrada_teste.txt
```
