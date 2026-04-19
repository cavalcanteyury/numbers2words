/*
** main.c
** Ponto de entrada do programa.
** Coordena os outros módulos: lê argumentos, carrega o dicionário,
** chama a conversão e cuida de liberar a memória.
**
** Ao modularizar, o main.c fica enxuto: ele não sabe COMO cada coisa
** funciona, só QUANDO chamar cada módulo.
*/
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "dict.h"
#include "number.h"

/*
** argc == 2 → ./debs-02 <número>           (dicionário padrão)
** argc == 3 → ./debs-02 <dict> <número>    (dicionário customizado)
** outro     → erro
*/
int	main(int argc, char **argv)
{
	const char			*dict_path;
	const char			*num_str;
	char				*content;
	t_entry				*dict;
	unsigned long long	n;

	if (argc == 2)
	{
		dict_path = "numbers.dict";
		num_str = argv[1];
	}
	else if (argc == 3)
	{
		dict_path = argv[1];
		num_str = argv[2];
	}
	else
	{
		ft_putstr("Error\n");
		return (1);
	}

	/* Valida e converte o argumento numérico */
	if (parse_number_arg(num_str, &n) < 0)
	{
		ft_putstr("Error\n");
		return (1);
	}

	/* Lê o arquivo de dicionário para memória */
	content = read_file(dict_path);
	if (!content)
	{
		ft_putstr("Dict Error \n");
		return (1);
	}

	/* Faz o parse e libera o conteúdo bruto (não é mais necessário) */
	dict = parse_dict(content);
	free(content);
	if (!dict)
	{
		ft_putstr("Dict Error \n");
		return (1);
	}

	/* Converte o número para palavras */
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
