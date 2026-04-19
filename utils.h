/*
** utils.h
** Cabeçalho (header) do módulo de utilitários.
**
** Um arquivo .h (header) serve como "contrato" entre módulos:
** ele declara o que existe sem definir o como.
** Qualquer arquivo .c que precisar dessas funções só precisa
** incluir este header.
**
** A guard (#ifndef / #define / #endif) evita que o header seja incluído
** mais de uma vez na mesma compilação, o que causaria erros de redefinição.
*/
#ifndef UTILS_H
# define UTILS_H

int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_strlen(const char *s);
void	ft_putstr(const char *s);
char	*substr(const char *s, int start, int end);
char	*read_file(const char *path);

#endif
