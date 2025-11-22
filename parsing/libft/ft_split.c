
#include "../../includes/cub3d.h"

static int	ft_count(char *str, char set)
{
	int	i;
	int	count;
	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != set) &&  (i == 0 || str[i - 1] == set))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(n + 1);
	if (p == NULL)
		return (NULL);
	while (s1[i] && (i < n))
	{
		p[i] = (char)s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	allocation_tab(char **tab, const char *s, char c)
{
	int	i; 
	int	j; 
	int	start;

	i = ((j = 0), 0);
	while (s[i])
	{

		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			tab[j] = ft_strndup(s + start, i - start);
			if (tab[j] == NULL)
			{
				free_tab(tab, j);
				return (0);
			}
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	len = ft_count((char *)s, c);
	tab = malloc((len + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (!allocation_tab(tab, s, c))
		return (NULL);
	return (tab);
}
