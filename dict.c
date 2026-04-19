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
	/* Pula espaços/tabs no início da linha */
	while (ft_isspace(line[i]))
		i++;
	/* Linha em branco ou fim de string → ignorar (retorna 0, não é erro) */
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	if (!ft_isdigit(line[i]))
		return (-1);
	/* Converte a sequência de dígitos para número */
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
	/* 'start' aponta para o primeiro caractere do valor */
	start = i;
	/* Avança até o fim da linha para encontrar onde o valor termina */
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	/*
	** Remove espaços/tabs no final do valor (trim direito).
	** Decrementamos 'end' enquanto o caractere antes dele for espaço.
	** Ao final, substr(line, start, end) captura só o texto sem espaços.
	*/
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	/* Se após o trim não sobrou nada entre ':' e '\n', o formato é inválido */
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
		/*
		** 'content + i' é um ponteiro para o início da linha atual dentro
		** do buffer completo. parse_line lê a partir desse ponto sem
		** precisar de uma cópia separada da linha.
		*/
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
			/*
			** Inserção no início da lista (prepend): o novo nó aponta para
			** o topo atual e passa a ser o novo topo. É O(1) e evita
			** percorrer a lista toda só para inserir no final.
			*/
			entry->next = dict;
			dict = entry;
		}
		/* Avança 'i' até o '\n' para posicionar no início da próxima linha */
		while (content[i] && content[i] != '\n')
			i++;
		if (content[i] == '\n')
			i++;
	}
	return (dict);
}

