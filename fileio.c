#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

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
