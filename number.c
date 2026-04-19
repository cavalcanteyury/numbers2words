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
** Controla o espaço separador entre palavras.
** 'static' → existe apenas dentro deste arquivo.
** 0 = nenhuma palavra escrita ainda
** 1 = já escrevemos algo (escreve espaço antes da próxima palavra)
*/
static int	g_sep = 0;

/*
** Escreve uma palavra no terminal.
** Se não for a primeira palavra, escreve um espaço antes.
*/
static void	put_word(const char *s)
{
	if (g_sep)
		write(1, " ", 1);
	ft_putstr(s);
	g_sep = 1;
}

/*
** Converte e escreve qualquer número de 1 a 999 usando o dicionário.
** Retorna 1 em sucesso, 0 se alguma chave necessária não for encontrada.
**
** Para as dezenas, multiplicamos o quociente por 10 para obter a chave:
**   n=42 → n/10=4 → chave=40 → dict_lookup(dict, 40) = "forty"
*/
static int	write_below_thousand(t_entry *dict, unsigned long long n)
{
	char	*word;

	if (n >= 100)
	{
		/*
		** Para centenas: n/100 dá o dígito das centenas (ex.: 342 → 3).
		** Buscamos a palavra do dígito (ex.: "três") e depois a palavra
		** de 100 (ex.: "cem"/"cento"), escrevendo as duas em sequência.
		** n %= 100 descarta a parte das centenas e continua com o resto.
		*/
		word = dict_lookup(dict, n / 100);
		if (!word) return (0);
		put_word(word);
		word = dict_lookup(dict, 100);
		if (!word) return (0);
		put_word(word);
		n %= 100;
	}
	if (n >= 20)
	{
		/*
		** Para dezenas de 20 a 99: (n / 10) * 10 arredonda para a dezena
		** exata (ex.: 42 → 4 → 40) e buscamos essa chave no dicionário.
		** n %= 10 pega a unidade restante (ex.: 42 → 2) para ser tratada
		** no próximo if — mas só se n > 0 após o módulo (ex.: 40 não tem unidade).
		*/
		word = dict_lookup(dict, (n / 10) * 10);
		if (!word) return (0);
		put_word(word);
		n %= 10;
		if (n > 0)
		{
			word = dict_lookup(dict, n);
			if (!word) return (0);
			put_word(word);
		}
	}
	else if (n > 0)
	{
		/*
		** Números de 1 a 19 têm palavras próprias no dicionário (não seguem
		** a lógica dezena+unidade), então buscamos diretamente pela chave.
		*/
		word = dict_lookup(dict, n);
		if (!word) return (0);
		put_word(word);
	}
	return (1);
}

/*
** Converte e escreve o número completo dividindo em grupos:
**   bilhões → milhões → milhares → resto (<1000)
**
** Retorna 1 em sucesso, 0 se alguma chave necessária não for encontrada.
*/
int	write_number(t_entry *dict, unsigned long long n)
{
	char	*word;

	if (n == 0)
	{
		word = dict_lookup(dict, 0);
		if (!word) return (0);
		put_word(word);
		return (1);
	}
	if (n >= 1000000000ULL)
	{
		if (!write_below_thousand(dict, n / 1000000000ULL)) return (0);
		word = dict_lookup(dict, 1000000000ULL);
		if (!word) return (0);
		put_word(word);
		n %= 1000000000ULL;
	}
	if (n >= 1000000)
	{
		if (!write_below_thousand(dict, n / 1000000)) return (0);
		word = dict_lookup(dict, 1000000ULL);
		if (!word) return (0);
		put_word(word);
		n %= 1000000;
	}
	if (n >= 1000)
	{
		if (!write_below_thousand(dict, n / 1000)) return (0);
		word = dict_lookup(dict, 1000ULL);
		if (!word) return (0);
		put_word(word);
		n %= 1000;
	}
	if (n > 0)
	{
		if (!write_below_thousand(dict, n)) return (0);
	}
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
		/*
		** Verificação de overflow ANTES de multiplicar para não ultrapassar
		** UINT_MAX (4.294.967.295). A lógica é:
		**   - Se n > 429.496.729, qualquer dígito a seguir já estoura.
		**   - Se n == 429.496.729, só dígito ≤ 5 ainda cabe (…295 é o limite).
		** Fazemos isso com inteiros maiores (unsigned long long) para a
		** comparação ser segura antes de realizar a operação n*10+digit.
		*/
		if (n > 429496729ULL || (n == 429496729ULL && digit > 5))
			return (-1);
		n = n * 10 + digit;
		i++;
	}
	/* Se ainda há caracteres não-dígito após o número, o argumento é inválido */
	if (s[i] != '\0')
		return (-1);
	*out = n;
	return (0);
}
