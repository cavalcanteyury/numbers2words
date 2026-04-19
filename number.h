/*
** number.h
** Cabeçalho do módulo de conversão numérica.
**
** Inclui dict.h porque as funções deste módulo recebem
** um t_entry* como parâmetro — o compilador precisa conhecer
** a definição de t_entry para entender as assinaturas.
*/
#ifndef NUMBER_H
# define NUMBER_H

# include "dict.h"

int	parse_number_arg(const char *s, unsigned long long *out);
int	write_number(t_entry *dict, unsigned long long n);

#endif
