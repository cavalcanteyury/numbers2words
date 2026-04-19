/*
** number.c
** Módulo responsável por:
**   - Validar e converter o argumento numérico (string → número)
**   - Converter o número para palavras usando o dicionário
*/
#include <unistd.h>
#include "utils.h"
#include "dict.h"
#include "number.h"

/*
** Escreve uma palavra no terminal.
** Se não for a primeira palavra, escreve um espaço antes.
** *sep controla o separador: 0 = primeira palavra, 1 = já escreveu algo.
*/
void	put_word(const char *s, int *sep)
{
	if (*sep)
		write(1, " ", 1);
	ft_putstr(s);
	*sep = 1;
}

/*
** Escreve a parte das centenas de n (ex.: 342 → "três" "cem").
** Atualiza *n para o resto após descartar as centenas (342 → 42).
** Retorna 1 em sucesso, 0 se a chave não for encontrada no dicionário.
*/
static int	write_hundreds(t_entry *dict, unsigned long long *n, int *sep)
{
	char	*word;

	if (*n < 100)
		return (1);
	word = dict_lookup(dict, *n / 100);
	if (!word)
		return (0);
	put_word(word, sep);
	word = dict_lookup(dict, 100);
	if (!word)
		return (0);
	put_word(word, sep);
	*n %= 100;
	return (1);
}

/*
** Escreve a parte das dezenas e unidades de n (1–99).
** Para n >= 20: busca a dezena exata com (n/10)*10, depois a unidade.
** Para 1–19: busca diretamente (cada número tem palavra própria).
** Retorna 1 em sucesso, 0 se alguma chave não for encontrada.
*/
static int	write_tens(t_entry *dict, unsigned long long n, int *sep)
{
	char	*word;

	if (n == 0)
		return (1);
	if (n >= 20)
	{
		word = dict_lookup(dict, (n / 10) * 10);
		if (!word)
			return (0);
		put_word(word, sep);
		n %= 10;
		if (n == 0)
			return (1);
	}
	word = dict_lookup(dict, n);
	if (!word)
		return (0);
	put_word(word, sep);
	return (1);
}

/*
** Escreve qualquer número de 1 a 999 combinando centenas e dezenas/unidades.
*/
int	write_below_thousand(t_entry *dict, unsigned long long n, int *sep)
{
	if (!write_hundreds(dict, &n, sep))
		return (0);
	return (write_tens(dict, n, sep));
}

/*
** Escreve um grupo de magnitude 'div' (ex.: bilhões, milhões, milhares).
** Ex.: n=2500, div=1000 → escreve "dois" "mil", atualiza *n para 500.
** Retorna 1 em sucesso, 0 se alguma chave não for encontrada.
*/
int	write_group(t_entry *dict, unsigned long long *n,
		unsigned long long div, int *sep)
{
	char	*word;

	if (*n < div)
		return (1);
	if (!write_below_thousand(dict, *n / div, sep))
		return (0);
	word = dict_lookup(dict, div);
	if (!word)
		return (0);
	put_word(word, sep);
	*n %= div;
	return (1);
}
