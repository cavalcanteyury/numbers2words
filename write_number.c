#include "utils.h"
#include "dict.h"
#include "number.h"

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
