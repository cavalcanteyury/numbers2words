#ifndef DICT_H
# define DICT_H

typedef struct s_entry
{
	unsigned long long	key;
	char				*value;
	struct s_entry		*next;
}	t_entry;

void		free_dict(t_entry *dict);
char		*dict_lookup(t_entry *dict, unsigned long long key);
t_entry		*parse_dict(const char *content);

#endif
