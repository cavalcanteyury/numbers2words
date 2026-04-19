/*
** dict.h
** Cabeçalho do módulo de dicionário.
**
** Define a estrutura t_entry e declara todas as funções
** que manipulam o dicionário.
**
** Outros módulos que precisam usar o dicionário (como number.c e main.c)
** incluem este header para conhecer o tipo t_entry e as funções disponíveis.
*/
#ifndef DICT_H
# define DICT_H

/*
** t_entry: um nó da lista ligada que representa o dicionário.
** Cada nó armazena um par chave→valor e um ponteiro para o próximo nó.
*/
typedef struct s_entry
{
	unsigned long long	key;    /* número: ex. 20, 100, 1000      */
	char				*value; /* palavra: ex. "twenty", "hundred" */
	struct s_entry		*next;  /* próximo nó da lista ligada       */
}	t_entry;

void		free_dict(t_entry *dict);
char		*dict_lookup(t_entry *dict, unsigned long long key);
t_entry		*parse_dict(const char *content);
int			validate_dict(t_entry *dict);

#endif
