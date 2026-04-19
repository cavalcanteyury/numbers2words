#ifndef NUMBER_H
# define NUMBER_H

# include "dict.h"

void	put_word(const char *s, int *sep);
int		write_below_thousand(t_entry *dict, unsigned long long n, int *sep);
int		write_group(t_entry *dict, unsigned long long *n,
			unsigned long long div, int *sep);
int		parse_number_arg(const char *s, unsigned long long *out);
int		write_number(t_entry *dict, unsigned long long n);

#endif
