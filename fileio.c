/*
** fileio.c
** Leitura de arquivo completo para uma string no heap.
** Separado de utils.c para respeitar o limite de funções por arquivo.
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

/*
** Aloca um buffer novo com o conteúdo antigo (old, total bytes) seguido
** pelo chunk recém lido (chunk, n bytes), terminado com '\0'.
** Libera 'old' em qualquer caso (sucesso ou falha de malloc).
** Retorna o novo buffer, ou NULL se malloc falhar.
*/
static char	*append_chunk(char *old, const char *chunk, int total, int n)
{
	char	*tmp;
	int		i;

	tmp = malloc(total + n + 1);
	if (!tmp)
	{
		free(old);
		return (NULL);
	}
	i = 0;
	while (i < total)
	{
		tmp[i] = old[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp[total + i] = chunk[i];
		i++;
	}
	tmp[total + n] = '\0';
	free(old);
	return (tmp);
}

/*
** Lê o arquivo em chunks de 4096 bytes e acumula em *content.
** Retorna 1 em sucesso, 0 se append_chunk falhar (conteúdo já liberado).
**
** A variável 'n' é inicializada antes do while e reatribuída no final
** do loop para evitar atribuição dentro da condição de controle.
*/
static int	read_loop(int fd, char **content, int *total)
{
	char	buf[4096];
	int		n;

	n = (int)read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		*content = append_chunk(*content, buf, *total, n);
		if (!*content)
			return (0);
		*total += n;
		n = (int)read(fd, buf, sizeof(buf));
	}
	return (1);
}

/*
** Abre o arquivo em 'path' e lê todo o conteúdo para uma string no heap.
** Retorna NULL se não conseguir abrir o arquivo ou se malloc falhar.
*/
char	*read_file(const char *path)
{
	int		fd;
	char	*content;
	int		total;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	total = 0;
	if (!read_loop(fd, &content, &total))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (content);
}
