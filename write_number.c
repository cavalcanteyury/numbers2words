/*
** write_number.c
** Converte e escreve um número em palavras, e analisa o argumento numérico.
*/
#include "utils.h"
#include "dict.h"
#include "number.h"

/*
** Converte e escreve o número completo dividindo em grupos:
**   bilhões → milhões → milhares → resto (<1000)
**
** Retorna 1 em sucesso, 0 se alguma chave necessária não for encontrada.
*/
int	write_number(t_entry *dict, unsigned long long n)
{
	char	*word;
	int		sep;

	sep = 0;
	if (n == 0)
	{
		word = dict_lookup(dict, 0);
		if (!word)
			return (0);
		put_word(word, &sep);
		return (1);
	}
	if (!write_group(dict, &n, 1000000000ULL, &sep))
		return (0);
	if (!write_group(dict, &n, 1000000ULL, &sep))
		return (0);
	if (!write_group(dict, &n, 1000ULL, &sep))
		return (0);
	if (n > 0 && !write_below_thousand(dict, n, &sep))
		return (0);
	return (1);
}

/*
** Converte a string 's' para um número inteiro sem sinal.
** Rejeita números acima de UINT_MAX (4.294.967.295).
**
** Preenche *out e retorna 0 em sucesso, -1 em erro.
**
** Verificação de overflow antes de cada multiplicação:
**   429.496.729 × 10 + 5 = 4.294.967.295 = UINT_MAX (exato) ✓
**   429.496.729 × 10 + 6 = 4.294.967.296 > UINT_MAX         ✗
*/
int	parse_number_arg(const char *s, unsigned long long *out)
{
	unsigned long long	n;
	unsigned long long	digit;
	int					i;

	n = 0;
	i = 0;
	if (!s[i] || !ft_isdigit(s[i]))
		return (-1);
	while (ft_isdigit(s[i]))
	{
		digit = (unsigned long long)(s[i] - '0');
		if (n > 429496729ULL || (n == 429496729ULL && digit > 5))
			return (-1);
		n = n * 10 + digit;
		i++;
	}
	if (s[i] != '\0')
		return (-1);
	*out = n;
	return (0);
}
