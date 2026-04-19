#include <unistd.h>
#include "utils.h"
#include "dict.h"
#include "number.h"

void	put_word(const char *s, int *sep)
{
	if (*sep)
		write(1, " ", 1);
	ft_putstr(s);
	*sep = 1;
}

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

int	write_below_thousand(t_entry *dict, unsigned long long n, int *sep)
{
	if (!write_hundreds(dict, &n, sep))
		return (0);
	return (write_tens(dict, n, sep));
}

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
