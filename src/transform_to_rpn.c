
// transform_to_rpn.c
// Converts input equation into the reverse polish notation.
// Author: Hanna Kulaieva 

#include "../includes/calculator.h"

/*	Function: check_valid_input
Checks if the symbols of the input string are in the valid format.
input: input string
size: size of the string
Returns: '1' if input is valid or '0' in case of an error. */
int					check_valid_input(char *input, int size)
{
	int		i;
	int		check_dot;

	check_dot = 0;
	i = -1;
	while (++i < size)
	{
		if (!isdigit(input[i]) && input[i] != '(' && !isoperator(input[i]) && input[i] != ' ' &&
		input[i] != '.' && input[i] != ')')
			return (0);
		if ((input[i] == '.' && i == 0) || (input[i] == '.' && input[i - 1] && !isdigit(input[i - 1])))
			return (0);
		if (isoperator(input[i]) && input[i + 1] == ' ' && !isdigit(input[i + 2]) &&
		input[i + 2] != '(')
			return (0);
		if (isoperator(input[i]) && input[i] != '(' && isoperator(input[i + 1]) &&
		input[i + 1] != '(')
			return (0);
		if (isdigit(input[i]))
		{
			while (isdigit(input[i]))
				i++;
			if (input[i] == '.' && !check_dot)
			{
				check_dot = 1;
				i++;
				while (isdigit(input[i]))
					i++;
			}
			if (input[i] == '.' && check_dot)
				return (0);
			if ((input[i] == ' ' && !isoperator(input[i + 1])) ||
			(input[i] != ' ' && input[i] != ')' && input[i] != '\0' && !isoperator(input[i])))
				return (0);
		}
		check_dot = 0;
	}
	return (1);
}

/*	Function: set_precedence
Creates the new element op the 'operator' type with specific precedence.
operator: operator value for the new element
Returns: pointer to the created element or NULL in case of error. */
t_operators		*set_precedence(char operator)
{
	t_operators *res;

	res = NULL;
	if ((res = (t_operators*)malloc(sizeof(t_operators))) != NULL)
	{
		res->operator = operator;
		if (operator == '+' || operator == '-')
			res->precedence = 0;
		else if (operator == '*' || operator == '/')
			res->precedence = 1;
		else
			res->precedence = 0;
	}
	return (res);
}

/*	Function: isoperator
Checks if the input char is a mathematical operator.
c: char to check
Returns: '1' if the symbol is an operator, '0' - if it's not. */
int			 isoperator(char c)
{
	if (c == '+' || c == '-' || c == '*' ||
	c == '/')
		return (1);
	return (0);
}

/*	Function: free_and_return
Frees the allocated memory of the input values.
ops: operator stack pointer
rpn_output: output string
Returns: NULL pointer. */
void			 *free_and_return(t_stack *ops, char *rpn_output)
{
	if (rpn_output)
		free(rpn_output);
	if (ops)
		free_stack(ops);
	return (NULL);
}

/*	Function: digit_handle
Checks if the portion of the input string, pointed by iterator, is a valid
numerical value and copies it to the output string.
i: current iterator
input: input string
rpn_output: output string
str_size: input string lenght
Returns: new iterator value. */
int					digit_handle(int i, char *input, char *rpn_output,
int str_size)
{
	float		tmp;
	char		*tmp_str;
	float		check_float;
	int		 j;

	check_float = 0;
	tmp = atof(&input[i]);
	check_float = tmp - (int)tmp;
	tmp_str = NULL;
	j = strlen(rpn_output);
	if (check_float)
		snprintf(&rpn_output[j], 3, "%f", tmp);
	else
	{
		tmp_str = ft_itoa(tmp);
		strcpy(&rpn_output[j], tmp_str);
		free(tmp_str);
	}
	if (input[i] == '.')
		i++;
	while (i < str_size && isdigit(input[i]))
		i++;
	if (isdigit(rpn_output[strlen(rpn_output) - 1]))
		rpn_output[strlen(rpn_output)] = ' ';
	return (i);
}

/*	Function: operator_handle
Checks if the portion of the input string, pointed by iterator, is a valid
mathematical operator and pushes it to th eoperator stack.
i: current iterator
input: input string
rpn_output: output string
ops: operator stack pointer */
void					operator_handle(int i, char *input, char *rpn_output,
t_stack *ops)
{
	t_operators	*operator_to_stack;
	t_operators	*res;
	t_operators *element;
	int		 j;

	j = 0;
	operator_to_stack = set_precedence(input[i]);
	element = (t_operators*)ops->data;
	res = (t_operators*)malloc(sizeof(t_operators));
	if (ops->top != -1 && input[i] != '(')
	{
		j = strlen(rpn_output);
		while (ops->top != -1 &&
		(element[ops->top]).precedence >= operator_to_stack->precedence &&
		element[ops->top].operator != '(')
		{
			if (pop(ops, res))
			{
				rpn_output[j] = res->operator;
				rpn_output[j + 1] = ' ';
				j += 2;
			}
		}
	}
	free(res);
	free(operator_to_stack);
	push(ops, operator_to_stack);
}

/*	Function: brackets_handle
Validates brackets and pushes the left bracket to the
operator stack.
rpn_output: output string
ops: operator stack pointer
Returns: '1' if bracket is pushed or '0' in case of an error. */
int					 brackets_handle(char *rpn_output, t_stack *ops)
{
	int			j;
	t_operators *element;
	t_operators *op_tmp;

	element = (t_operators*)ops->data;
	if (!(op_tmp = (t_operators*)malloc(sizeof(t_operators))))
		return (0);
	j = strlen(rpn_output);
	while (ops->top != -1 && element[ops->top].operator != '(')
	{
		if (ops->top == 0 && element[ops->top].operator != '(')
			return (0);
		if (pop(ops, op_tmp))
		{
			rpn_output[j] = op_tmp->operator;
			rpn_output[j + 1] = ' ';
			j += 2;
		}
	}
	if (element[ops->top].operator == '(')
		pop(ops, op_tmp);
	free(op_tmp);
	return (1);
}

/*	Function: handle_operators_stack
After the main parsing loop, copies the leftout operators to the output
string.
rpn_output: output string
ops: operator stack pointer
Returns: '1' if operators are pushed or '0' in case of an error. */
int					handle_operators_stack(char *rpn_output, t_stack *ops)
{
	int			j;
	t_operators *element;
	t_operators *op_tmp;

	j = strlen(rpn_output);
	element = (t_operators*)ops->data;
	if (!(op_tmp = (t_operators*)malloc(sizeof(t_operators))))
		return (0);
	while (ops->top != -1)
	{
		if (element[ops->top].operator == '(' ||
		element[ops->top].operator == ')')
			return (0);
		if (pop(ops, op_tmp))
		{
			rpn_output[j] = op_tmp->operator;
			rpn_output[j + 1] = ' ';
			j += 2;
		}
	}
	free(op_tmp);
	return (1);
}

/*	Function: transform_to_rpn
Runs a loop, that converts input string to reverse polish notation.
input: input string
Returns: converted string or NULL in case of an error. */
char					*transform_to_rpn(char *input)
{
	int			str_size;
	int			i;
	char		*rpn_output;
	t_stack		*ops;

	str_size = strlen(input);
	rpn_output = (char*)malloc(sizeof(char) * str_size + 250);
	bzero(rpn_output, str_size + 250);
	ops = init_stack(str_size, sizeof(t_operators));
	i = -1;
	while (++i < str_size)
	{
		if (!check_valid_input(input, str_size))
			return (free_and_return(ops, rpn_output));
		if (isdigit(input[i]))
		{
			i = digit_handle(i, input, rpn_output, str_size);
			if (!i)
				return (free_and_return(ops, rpn_output));
		}
		if (isoperator(input[i]) || input[i] == '(')
			operator_handle(i, input, rpn_output, ops);
		if (input[i] == ')')
		{
			if (!brackets_handle(rpn_output, ops))
				return (free_and_return(ops, rpn_output));
		}
	}
	if (!handle_operators_stack(rpn_output, ops))
		return (free_and_return(ops, rpn_output));
	if (rpn_output[strlen(rpn_output) - 1] == ' ')
		rpn_output[strlen(rpn_output) - 1] = '\0';
	else
		rpn_output[strlen(rpn_output)] = '\0';
	free_stack(ops);
	return (rpn_output);
}
