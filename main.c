#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "dict.h"
#include "number.h"

static int	get_args(int argc, char **argv, const char **path, const char **num)
{
	if (argc == 2)
	{
		*path = "numbers.dict";
		*num = argv[1];
	}
	else if (argc == 3)
	{
		*path = argv[1];
		*num = argv[2];
	}
	else
		return (0);
	return (1);
}

static t_entry	*load_dict(const char *path)
{
	char	*content;
	t_entry	*dict;

	content = read_file(path);
	if (!content)
		return (NULL);
	dict = parse_dict(content);
	free(content);
	return (dict);
}

static int	run(t_entry *dict, unsigned long long n)
{
	if (!write_number(dict, n))
	{
		free_dict(dict);
		ft_putstr("Dict Error \n");
		return (1);
	}
	write(1, "\n", 1);
	free_dict(dict);
	return (0);
}

int	main(int argc, char **argv)
{
	const char			*dict_path;
	const char			*num_str;
	t_entry				*dict;
	unsigned long long	n;

	if (!get_args(argc, argv, &dict_path, &num_str))
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (parse_number_arg(num_str, &n) < 0)
	{
		ft_putstr("Error\n");
		return (1);
	}
	dict = load_dict(dict_path);
	if (!dict)
	{
		ft_putstr("Dict Error \n");
		return (1);
	}
	return (run(dict, n));
}
