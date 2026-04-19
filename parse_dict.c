#include <stdlib.h>
#include "utils.h"
#include "dict.h"

static int	parse_value(const char *line, int i, char **value)
{
	int		start;
	int		end;

	while (ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	if (end <= start)
		return (-1);
	*value = substr(line, start, end);
	if (!*value)
		return (-1);
	return (1);
}

static int	parse_line(const char *line, unsigned long long *key, char **value)
{
	int					i;
	unsigned long long	n;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	if (!ft_isdigit(line[i]))
		return (-1);
	n = 0;
	while (ft_isdigit(line[i]))
	{
		n = n * 10 + (unsigned long long)(line[i] - '0');
		i++;
	}
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != ':')
		return (-1);
	*key = n;
	return (parse_value(line, i + 1, value));
}

static int	next_line(const char *content, int i)
{
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] == '\n')
		i++;
	return (i);
}

static t_entry	*make_entry(t_entry *dict, unsigned long long key, char *value)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (!entry)
	{
		free(value);
		free_dict(dict);
		return (NULL);
	}
	entry->key = key;
	entry->value = value;
	entry->next = dict;
	return (entry);
}

t_entry	*parse_dict(const char *content)
{
	t_entry				*dict;
	unsigned long long	key;
	char				*value;
	int					i;

	dict = NULL;
	i = 0;
	while (content[i])
	{
		value = NULL;
		if (parse_line(content + i, &key, &value) == -1)
		{
			free_dict(dict);
			return (NULL);
		}
		if (value)
			dict = make_entry(dict, key, value);
		if (value && !dict)
			return (NULL);
		i = next_line(content, i);
	}
	return (dict);
}
