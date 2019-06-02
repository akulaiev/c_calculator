
// calculator.c
// A simple mathematical equations calculator.
// Supported operators: '+', '-', '*', '/' and brackets.
// Author: Hanna Kulaieva

#include "../includes/calculator.h"

int						main(int argc, char **argv)
{
	char	*rpn_str;
	float	res;
	float	check_float;

	rpn_str = NULL;
	if (argc != 2)
		return (-1);
	else
	{
		rpn_str = transform_to_rpn(argv[1]);
		if (!rpn_str)
			return (-1);
		check_float = 0;
		res = solve_rpn(rpn_str);
		check_float = res - (int)res;
		if (check_float != 0)
			printf("%.3f\n", res);
		else
			printf("%i\n", (int)res);
	}
	return (0);
}