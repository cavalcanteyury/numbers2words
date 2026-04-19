/*
** main.c
** Ponto de entrada do programa.
** Coordena os outros módulos: lê argumentos, carrega o dicionário,
** chama a conversão e cuida de liberar a memória.
*/
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "dict.h"
#include "number.h"

/*
** Preenche *path e *num a partir dos argumentos da linha de comando.
** argc == 2 → dicionário padrão; argc == 3 → dicionário customizado.
** Retorna 1 em sucesso, 0 em caso de uso incorreto.
*/
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

/*
** Lê o arquivo de dicionário e o converte em lista ligada.
** Libera o conteúdo bruto do arquivo após o parse.
** Retorna a lista, ou NULL em caso de erro.
*/
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

/*
** Executa a conversão e escreve o resultado, liberando o dicionário ao final.
** Retorna 0 em sucesso, 1 se alguma chave necessária não for encontrada.
*/
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
