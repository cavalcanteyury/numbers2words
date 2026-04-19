/*
** dict.c
** Módulo responsável por tudo relacionado ao dicionário:
** leitura linha a linha, construção da lista ligada e busca por chave.
*/
#include <stdlib.h>
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
