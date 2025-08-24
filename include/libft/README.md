<div id="header" align="center">
  <img src="https://media.giphy.com/media/ztl9x7JlhSlU4MWD6h/giphy.gif" width="200"/>

<h1 align="center">Libft | 42 SP</h1>
</div>

<h2 align="center">
	<a href="#sobre">Sobre</a>
	<span> · </span>
	<a href="#índice">Índice</a>
	<span> · </span>
	<a href="#requisitos">Requisitos</a>
	<span> · </span>
	<a href="#instruções">Instruções</a>
	<span> · </span>
	<a href="#tester">Teste</a>
</h2>

## Sobre
> Primeiro projeto que fiz na formação da 42SP.

> __Libft__ é uma biblioteca personalizada criada usando __C__ com funções úteis que serão permitidas usar em projetos futuros da formação. Usando essa biblioteca, o processo de codificação em projetos futuros será mais eficaz. O objetivo de reescrever essas funções é entender melhor o funcionamento da linguagem __C__ e também como as funções se comportam, e claro que elas tarão muitas utilidades para os próximos projetos da formação.
> 
## Índice
### Funções da biblioteca `<ctype.h>`
* `ft_isascii` - Testa se um caractere é ASCII de 7 bits.
* `ft_isalpha` - Testa se um caractere é alfabético.
* `ft_isdigit` - Testa se um caractere é um dígito decimal.
* `ft_isalnum` - Testa se um caractere é alfanumérico.
* `ft_isprint` - Testa se um caractere é imprimível, incluindo espaço.
* `ft_tolower` - Converte um caractere para minúsculo.
* `ft_toupper` - Converte um caractere para maiúsculo.

### Funções da biblioteca `<stdlib.h>`
* `ft_atoi` - Converte string ASCII para inteiro.
* `ft_calloc` - Aloca espaço para um array e o inicializa com 0. Esta função e `malloc` retornam um ponteiro `void`, que não tem tipo associado. Um ponteiro `void` pode conter endereço de qualquer tipo e pode ser convertido para qualquer tipo.

### Funções da biblioteca `<strings.h>`
* `ft_bzero` - Define a primeira parte de um objeto como bytes nulos (preenchendo com zeros).
* `ft_memset` - Define uma área de memória com um valor específico.
* `ft_memchr` - Encontra a primeira ocorrência de um caractere em um buffer.
* `ft_memcmp` - Compara bytes em dois buffers.
* `ft_memmove` - Copia bytes de um buffer para outro, tratando corretamente sobreposições.
* `ft_memcpy` - Copia bytes de um buffer para outro.

### Funções da biblioteca `<string.h>`
* `ft_strlen` - Obtém o comprimento de uma string.
* `ft_strchr` - Encontra a primeira ocorrência de um caractere em uma string.
* `ft_strrchr` - Encontra a última ocorrência de um caractere em uma string.
* `ft_strnstr` - Localiza uma substring em uma string.
* `ft_strncmp` - Compara duas strings até um dado comprimento.
* `ft_strdup` - Cria uma duplicata de uma string usando `malloc`.
* `ft_strlcpy` - Copia string com limite de tamanho.
* `ft_strlcat` - Concatena string com limite de tamanho.

### Funções não padronizadas
* `ft_itoa` - Converte inteiro para string ASCII.
* `ft_substr` - Obtém uma substring de uma string.
* `ft_strtrim` - Remove caracteres do início e do final de uma string.
* `ft_strjoin` - Concatena duas strings em uma nova string usando `calloc`.
* `ft_split` - Divide string em um array de strings, usando um caractere como delimitador.
* `ft_strmapi` - Cria nova string modificada por uma função especificada.
* `ft_striteri` - Modifica uma string com uma função dada.
* `ft_putchar_fd` - Imprime um caractere em um arquivo.
* `ft_putstr_fd` - Imprime uma string em um arquivo.
* `ft_putendl_fd` - Imprime uma string com nova linha em um arquivo.
* `ft_putnbr_fd` - Imprime um inteiro em um arquivo.

### Funções de lista encadeada *(bônus)*
* `ft_lstnew` - Cria uma nova lista.
* `ft_lstsize` - Conta elementos de uma lista.
* `ft_lstlast` - Encontra o último elemento de uma lista.
* `ft_lstadd_back` - Adiciona novo elemento ao final de uma lista.
* `ft_lstadd_front` - Adiciona novo elemento ao início de uma lista.
* `ft_lstdelone` - Remove elemento de uma lista.
* `ft_lstclear` - Remove uma sequência de elementos a partir de um ponto inicial.
* `ft_lstiter` - Aplica uma função ao conteúdo de todos os elementos da lista.
* `ft_lstmap` - Aplica uma função ao conteúdo de todos os elementos da lista em uma nova lista.

## Requisitos
A biblioteca é escrita em __linguagem C__ e requer o compilador `gcc`, com as bibliotecas padrão `<stdlib.h>` e `<unistd.h>` para rodar. Como usei a biblioteca `<unistd.h>` somente nas funções __fd__ então inclui a essa biblioteca somente nas proprias funções __fd__.

## Instruções

### 1. Compilando a biblioteca

Para compilar a biblioteca, vá até o diretório e execute:

Para funções __básicas__:
```
$ make
```

Para funções __bonus__:
```
$ make bonus
```

### 2. Limpando todos os arquivos binários (.o) e executáveis ​​(.a)

Para excluir todos os arquivos gerados com o make, vá até o caminho e execute:
```
$ make fclean
```

### 3. Usando-o em seu código

Para usar as funções da biblioteca no seu código, basta incluir este cabeçalho:
```
#include "libft.h"
```

## Tester
Esta biblioteca foi testada com [Francinette](https://github.com/xicodomingues/francinette) e [libftTester](https://github.com/Tripouille/libftTester).
