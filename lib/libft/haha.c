#include "libft.h"

static bool	    is_sep(char c, char sep)
{
	if (sep == c)
		return (true);
	return (false);
}

void     jumpaa4(char   *start, char c, int *i)
{
    char    *tmp;

    tmp = (start) + *i;
    tmp++;
    *i = *i + 1;
    while (tmp)
    {
        if (*tmp == c)
            break ;
        tmp++;
        *i = *i + 1;
    }
    tmp++;
    *i = *i + 1;
}

void    haha(char   *str, int *i, char sep)
{
    while (str[*i] != 0x00)
	{
        if (str[*i] == '"' || str[*i] == '\'')
            jumpaa4(str, str[*i], i);
		if (is_sep(str[*i], sep))
			break ;
		*i = *i +1;
	}
}

void     jumpaa2(char   **start, char c, int i)
{
    char    *tmp;

    tmp = (*start) + i;
    tmp++;
    while (tmp)
    {
        if (*tmp == c)
            break ;
        tmp++;
    }
    *start = tmp;
}

void     jumpaa3(char   *start, char c, int *i, char **arr)
{
    char    *tmp;
    char    *tmp2;

    tmp = (start) + *i;
    tmp2 = *arr + *i;
    *tmp2 = *tmp;
    tmp++;
    tmp2++;
    *i = *i + 1;
    while (tmp)
    {
        if (*tmp == c)
            break ;
        *tmp2 = *tmp;
        tmp++;
        tmp2++;
        *i = *i + 1;
    }
    *tmp2 = *tmp;
    tmp++;
    tmp2++;
    *i = *i + 1;
}