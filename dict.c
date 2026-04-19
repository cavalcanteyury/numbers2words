#include <stdlib.h>
#include "dict.h"

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
