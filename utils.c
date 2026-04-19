/*
** utils.c
** Funções utilitárias usadas por todos os outros módulos.
** Substituem funções da biblioteca padrão (strlen, isdigit, etc.)
** pois só podemos usar: write, malloc, free, open, read, close.
*/
#include <unistd.h>
#include <fcntl.h>
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

/*
** Abre o arquivo em 'path' e lê todo o conteúdo para uma string no heap.
**
** A cada chunk lido de 4096 bytes:
**   1. Aloca um buffer novo (total atual + chunk + 1 para '\0')
**   2. Copia o conteúdo antigo + novo chunk para o buffer novo
**   3. Libera o buffer antigo
**
** Retorna NULL se não conseguir abrir o arquivo ou se malloc falhar.
*/
char	*read_file(const char *path)
{
	int		fd;
	char	*content;
	char	*tmp;
	char	buf[4096];
	int		total;
	int		n;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	total = 0;

	/*
	** A estratégia é:
	** a cada iteração, alocar um buffer novo do tamanho total acumulado
	** (total) + o chunk recém lido (n) + 1 byte para o '\0' final.
	** Depois copiamos o conteúdo antigo e o novo chunk para esse buffer,
	** liberamos o buffer anterior e repetimos até EOF - END OF FILE (read retorna 0).
	*/
	while ((n = (int)read(fd, buf, sizeof(buf))) > 0)
	{
		tmp = malloc(total + n + 1);
		if (!tmp)
		{
			free(content);
			close(fd);
			return (NULL);
		}
		/* Copia o conteúdo já acumulado para o novo buffer */
		i = 0;
		while (i < total) { tmp[i] = content[i]; i++; }
		/* Acrescenta o chunk recém lido logo após o conteúdo anterior */
		i = 0;
		while (i < n) { tmp[total + i] = buf[i]; i++; }
		total += n;
		tmp[total] = '\0'; /* Garante que a string sempre termina com '\0' */
		free(content);     /* Libera o buffer antigo; tmp passa a ser o atual */
		content = tmp;
	}
	close(fd);
	return (content);
}
