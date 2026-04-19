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
**
** Por que dois nomes (s_entry e t_entry)?
**   O campo *next precisa apontar para a própria struct — mas no momento
**   em que o compilador lê essa linha, o typedef ainda não terminou e
**   "t_entry" ainda não existe. A solução é dar um nome à struct antes
**   do typedef ("s_entry") para poder usá-lo internamente. Fora daqui,
**   apenas "t_entry" é usado; "s_entry" existe só para resolver esse
**   problema de referência circular.
*/
typedef struct s_entry          /* ← nome da struct, usado só internamente */
{
	unsigned long long	key;    /* número: ex. 20, 100, 1000               */
	char				*value; /* palavra: ex. "vinte", "cem"              */
	struct s_entry		*next;  /* ← referencia s_entry pois t_entry ainda
	                               não existe neste ponto da declaração    */
}	t_entry;                    /* ← alias público; use sempre t_entry     */

void		free_dict(t_entry *dict);
char		*dict_lookup(t_entry *dict, unsigned long long key);
t_entry		*parse_dict(const char *content);

#endif
