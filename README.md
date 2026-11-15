# Projeto prático de Estrutura de Dados — BST e lista encadeada

Projeto individual da disciplina de Estrutura de Dados (ADS, 3º semestre, FATEC
Ribeirão Preto).

- Tema A: equipamentos de rede (ID, nome do equipamento, tipo e localização).
- Estrutura linear: lista encadeada (inserção no fim, remoção no início,
  exibição do início ao fim).
- Linguagem: C11.

## Organização

```
include/bst.h          estrutura do registro e da árvore binária de busca
include/estrutura.h    estrutura da lista encadeada
src/bst.c              inserção, busca, remoção, listagem e liberação da BST
src/estrutura.c        inserção, remoção, exibição e liberação da lista
src/main.c             menu, leitura de entrada, validações e fluxo do programa
tests/entrada_teste.txt  entrada usada no roteiro de testes
tests/roteiro-testes.md  casos, resultado esperado e resultado obtido
```

## Como compilar

Ambiente usado: Windows 11, compilador GCC 16.1.0 (MinGW-W64, UCRT) e C11.

No PowerShell, a partir da raiz do projeto:

```
gcc -std=c11 -Wall -Wextra -Iinclude -o projeto.exe src/main.c src/bst.c src/estrutura.c
```

Em Linux ou macOS, o mesmo comando funciona trocando o nome do executável:

```
gcc -std=c11 -Wall -Wextra -Iinclude -o projeto src/main.c src/bst.c src/estrutura.c
```

## Como executar

```
projeto.exe
```

O menu tem as opções 1 a 7 e a opção 0 para encerrar. Todo valor digitado é lido
como texto e convertido com `strtol`, então letras, números com texto depois do
número e valores fora do intervalo de `int` são rejeitados sem travar o programa.

## Como reproduzir os testes

Todos os casos do roteiro estão em `tests/entrada_teste.txt`:

```
projeto.exe < tests/entrada_teste.txt
```

Os 33 casos, com entrada, passos, resultado esperado e resultado obtido, estão em
`tests/roteiro-testes.md`. O programa encerra liberando toda a memória alocada na
árvore e na lista.

O Valgrind não está disponível no Windows. Em uma máquina Linux, a verificação de
memória pode ser feita com:

```
valgrind --leak-check=full ./projeto < tests/entrada_teste.txt
```

## Validações

- ID: inteiro positivo e único na BST, com rejeição de zero, negativo, texto não
  numérico, texto depois do número e valor fora do intervalo de `int`.
- Nome, tipo e localização: de 1 a 79 caracteres depois de remover os espaços das
  pontas, sem aceitar texto vazio ou só com espaços.
- A lista aceita IDs repetidos e IDs que não existem na árvore, conforme o
  enunciado.
- Remoção em árvore ou lista vazia apenas informa o usuário e o programa continua.
- Opção de menu inválida volta ao menu.

## Complexidade das operações

| Operação | Estrutura | Complexidade |
|---|---|---|
| Inserir | BST | O(h), sendo h a altura |
| Buscar | BST | O(h) |
| Remover | BST | O(h) |
| Listar em-ordem | BST | O(n) |
| Inserir no fim | Lista | O(1) |
| Remover do início | Lista | O(1) |
| Exibir | Lista | O(n) |

Em uma árvore equilibrada h é O(log n). Como a BST não é balanceada, o pior caso
é uma árvore degenerada com h = n, ou seja, O(n).

## Uso de inteligência artificial

Ferramenta usada: assistente de código OpenCode, para revisão do enunciado,
geração da estrutura inicial do código e revisão do roteiro de testes. A
elaboração, a conferência dos resultados e a defesa do funcionamento são
individuais.
