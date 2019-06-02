
// calculator.h
// Header file with the list of all used functions and all included libraries.
// Author: Hanna Kulaieva

#ifndef CALCULATOR_H
# define CALCULATOR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct		s_operators
{
	char			operator;
	int				precedence;
}					t_operators;

typedef struct		s_stack
{
	int				size;
	int				top;
	int				member_size;
	void			*data;
}					t_stack;

t_stack				*init_stack(int stack_size, int member_size);
int					stack_size(t_stack *stack);
int					push(t_stack *stack, void *elem);
int					pop(t_stack *stack, void *target);
int					top(t_stack *stack,  void *target);
void				free_stack(t_stack *stack);
char				*ft_itoa(int n);
char				*transform_to_rpn(char *input);
int					isoperator(char c);
float       		solve_rpn(char *rpn_input);

#endif
