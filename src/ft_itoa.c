
#include "../includes/calculator.h"

static int		ten_sqr(long long i)
{
	int		res;

	res = 1;
	while (i > 0)
	{
		res = res * 10;
		i--;
	}
	return (res);
}

static int		ft_count(long long i)
{
	int count;

	count = 1;
	while (i > 9)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

static char		*create_str(char *str_n, int count, long long n, int j)
{
	while (count > 0)
	{
		str_n[j] = (n / ten_sqr(count - 1)) + '0';
		n = n % ten_sqr(count - 1);
		j++;
		count--;
	}
	str_n[j] = '\0';
	return (str_n);
}

char			*ft_itoa(int n)
{
	char		*str_n;
	int			count;
	int			check;
	long long	nn;
	long long	i;

	nn = n;
	check = 0;
	if (nn < 0)
	{
		nn = -nn;
		check = 1;
	}
	i = nn;
	count = ft_count(i);
	if ((str_n = (char*)malloc(sizeof(char) * count + 1 + check)))
	{
		if (check)
			str_n[0] = '-';
		str_n = create_str(str_n, count, nn, check);
		return (str_n);
	}
	return (0);
}
