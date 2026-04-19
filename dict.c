/*
** dict.c
** Módulo responsável por tudo relacionado ao dicionário:
** leitura linha a linha, construção da lista ligada,
** busca por chave e validação das chaves obrigatórias.
*/
#include <stdlib.h>
#include "utils.h"
#include "dict.h"

/*
** Lista das 32 chaves que o algoritmo de conversão precisa obrigatoriamente.
** 'static' aqui significa que essa variável só existe dentro deste arquivo.
*/
static unsigned long long	g_required[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 30, 40, 50, 60, 70, 80, 90,
	100, 1000, 1000000, 1000000000ULL
};

/*
** Libera toda a memória alocada pelo dicionário.
** Percorre a lista nó a nó, liberando o valor (string) e depois o nó.
*/
void	free_dict(t_entry *dict)
{
	t_entry	*next;

	while (dict)
	{
		next = dict->next;
		free(dict->value);
		free(dict);
		dict = next;
	}
}

/*
** Procura no dicionário uma entrada com a chave 'key'.
** Retorna a string do valor correspondente, ou NULL se não encontrar.
*/
char	*dict_lookup(t_entry *dict, unsigned long long key)
{
	while (dict)
	{
		if (dict->key == key)
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}

/*
** Analisa uma única linha do dicionário.
** Formato: [número][espaços]:[espaços][valor][espaços]\n
**
** Retorna:
**    1 → linha válida com uma entrada
**    0 → linha vazia (ignorar)
**   -1 → erro de formato
**
** 'static' porque essa função é um detalhe interno deste módulo.
** Nenhum outro arquivo precisa chamá-la diretamente.
*/
static int	parse_line(const char *line, unsigned long long *key, char **value)
{
	int					i;
	unsigned long long	n;
	int					start;
	int					end;

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
	i++;
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
	*key = n;
	*value = substr(line, start, end);
	if (!*value)
		return (-1);
	return (1);
}

/*
** Analisa o conteúdo completo do arquivo de dicionário linha por linha.
** Monta e retorna a lista ligada de entradas.
** Retorna NULL em caso de erro de formato.
*/
t_entry	*parse_dict(const char *content)
{
	t_entry				*dict;
	t_entry				*entry;
	unsigned long long	key;
	char				*value;
	int					i;
	int					result;

	dict = NULL;
	i = 0;
	while (content[i])
	{
		result = parse_line(content + i, &key, &value);
		if (result == -1)
		{
			free_dict(dict);
			return (NULL);
		}
		if (result == 1)
		{
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
			dict = entry;
		}
		while (content[i] && content[i] != '\n')
			i++;
		if (content[i] == '\n')
			i++;
	}
	return (dict);
}

/*
** Verifica se todas as 32 chaves obrigatórias estão presentes no dicionário.
** Retorna 1 se válido, 0 se alguma chave estiver faltando.
*/
int	validate_dict(t_entry *dict)
{
	int	count;
	int	i;

	count = (int)(sizeof(g_required) / sizeof(g_required[0]));
	i = 0;
	while (i < count)
	{
		if (!dict_lookup(dict, g_required[i]))
			return (0);
		i++;
	}
	return (1);
}
