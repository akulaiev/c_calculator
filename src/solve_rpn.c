
// solve_rpn.c
// Reverse polish notation solver.
// Author: Hanna Kulaieva 

#include "../includes/calculator.h"

/*	Function: free_data
Frees the allocated memory.
tokens: token array
sise: size of token array
numbers: pointer to the numerical stack */
void		free_data(char **tokens, int size, t_stack *numbers)
{
	int		i;

	i = -1;
	while (++i < size)
		free(tokens[i]);
	free(tokens);
	free_stack(numbers);
}

/*	Function: tokenize
Splits the input reverse polish notation string into the array of
strings, separated by spaces.
rpn_input: input string
size: size of the new string array
Returns: converted string array. */
char		**tokenize(char *rpn_input, int size)
{
	char	**tokens;
	char	*tmp_token;
	int		dest_size;
	int		i;

	if (!(tokens = (char**)malloc(sizeof(char*) * size)))
		exit (-1);
	i = -1;
	while (++i < size)
	{
		tmp_token = strtok(rpn_input, " ");
		dest_size = strlen(tmp_token) + 1;
		if (!(tokens[i] = (char*)malloc(dest_size)))
			exit (-1);
		strlcpy(tokens[i], tmp_token, dest_size);
		rpn_input = NULL;
	}
	free(rpn_input);
	return (tokens);
}

/*	Function: get_size
Returns the size of the reverse polish notation string array.
rpn_input: input string */
int			get_size(char *rpn_input)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (rpn_input[i++])
	{
		if (rpn_input[i] == ' ')
			size++;
	}
	return (size + 1);
}

/*	Function: solve_rpn
Runs a loop, that solves the input reverse polish notation equasion.
rpn_input: input string
Returns: result value or '0' in case of error. */
float		solve_rpn(char *rpn_input)
{
	char	**tokens;
	char	*token;
	t_stack *numbers;
	float	num_one;
	float	num_two;
	float	tmp_res;
	float	res;
	int		size;
	int		i;

	size = get_size(rpn_input);
	tokens = tokenize(rpn_input, size);
	numbers = init_stack(size, sizeof(float));
	i = 0;
	while (i < size)
	{
		token = tokens[i];
		if (isoperator(token[0]))
		{
			if (top(numbers, &num_one))
				pop(numbers, NULL);
			if (top(numbers, &num_two))
				pop(numbers, NULL);
			if (token[0] == '+')
				tmp_res = num_two + num_one;
			else if (token[0] == '-')
				tmp_res = num_two - num_one;
			else if (token[0] == '*')
				tmp_res = num_two * num_one;
			else
				tmp_res = num_two / num_one;
			push(numbers, &tmp_res);
		}
		else
		{
			tmp_res = atof(token);
			push(numbers, &tmp_res);
		}
		tmp_res = 0;
		num_one = 0;
		num_two = 0;
		i++;
	}
	if (stack_size(numbers))
	{
		top(numbers, &res);
		while (stack_size(numbers))
			pop(numbers, NULL);
		free_data(tokens, size, numbers);
		return (res);
	}
	return (0);
}
