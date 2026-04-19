/*
** utils.c
** Funções utilitárias de caractere e string.
** Substituem funções da biblioteca padrão (strlen, isdigit, etc.)
** pois só podemos usar: write, malloc, free, open, read, close.
*/
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

/*
** Retorna 1 se o caractere é um dígito de '0' a '9', 0 caso contrário.
*/
int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** Retorna 1 se o caractere é um espaço ou tabulação, 0 caso contrário.
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

/*
** Calcula o comprimento de uma string manualmente (equivalente a strlen).
*/
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** Escreve uma string na saída padrão (fd=1 = terminal).
*/
void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

/*
** Cria uma cópia de s[start..end) alocada no heap (equivalente a strndup).
** Retorna NULL se malloc falhar.
**
** Exemplo: substr("hello world", 6, 11) → "world"
*/
char	*substr(const char *s, int start, int end)
{
	int		len;
	char	*copy;
	int		i;

	len = end - start;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[start + i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
