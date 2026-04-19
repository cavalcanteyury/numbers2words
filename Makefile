# ---------------------------------------------------------------------------
# Variáveis
# ---------------------------------------------------------------------------

# Nome do executável final
NAME	= numbers2words

# Compilador C
CC		= cc

# Flags do compilador:
#   -Wall   → ativa a maioria dos warnings
#   -Wextra → ativa warnings extras
#   -Werror → trata qualquer warning como erro
CFLAGS	= -Wall -Wextra -Werror

# Lista de todos os arquivos fonte do projeto.
# Agora temos múltiplos módulos em vez de um único arquivo.
SRCS	= main.c \
		  utils.c \
		  dict.c \
		  number.c

# Gera a lista de arquivos objeto (.o) substituindo .c por .o em cada nome.
# Resultado: main.o utils.o dict.o number.o
OBJS	= $(SRCS:.c=.o)

# ---------------------------------------------------------------------------
# Alvos
# ---------------------------------------------------------------------------

# Alvo padrão: gera o executável
all: $(NAME)

# Linka todos os .o e gera o binário final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Regra genérica: compila cada .c em seu respectivo .o
# $< = arquivo fonte (.c)   $@ = arquivo objeto (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove os arquivos objeto
clean:
	rm -f $(OBJS)

# Remove os arquivos objeto e o executável
fclean: clean
	rm -f $(NAME)

# Recompila tudo do zero
re: fclean all

# ---------------------------------------------------------------------------
# .PHONY: informa ao Make que esses alvos não são arquivos reais
# ---------------------------------------------------------------------------
.PHONY: all clean fclean re
