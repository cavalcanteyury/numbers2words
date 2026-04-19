#ifndef UTILS_H
# define UTILS_H

int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_strlen(const char *s);
void	ft_putstr(const char *s);
char	*substr(const char *s, int start, int end);
char	*read_file(const char *path);

#endif
