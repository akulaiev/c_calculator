
// my_stack.c
// Simplified implementation of "stack" data structure.
// Author: Hanna Kulaieva

#include "../includes/calculator.h"

/*	Function: init_stack
Allocates the new stack.
stack_size:  number of stack elements
member_size: size of an element data in bytes
Returns: pointer to the allocated stack or NULL in case of error.. */
t_stack			*init_stack(int stack_size, int member_size)
{
	t_stack	*res;

	res = (t_stack*)malloc(sizeof(t_stack));
	res->size = stack_size;
	res->member_size = member_size;
	res->top = -1;
	if ((res->data = (void*)malloc(res->size * res->member_size)) == NULL)
		return (NULL);
	return (res);
}


/*	Function: stack_size
Returns the size of the stack.
stack: pointer to the stack */
int				stack_size(t_stack *stack)
{
	return (stack->top + 1);
}

/*	Function: push
Pushes the element on top of the stack.
stack: pointer to the stack
elem: data of the element to push
Returns: '0' if the stack is already full,
'1' if element is successfully pushed. */
int				push(t_stack *stack, void *elem)
{
	void	*target;

	if (stack->top == stack->size - 1)
		return (0);
	stack->top++;
	target = (char*)stack->data + (stack->top * stack->member_size);
  	memcpy(target, elem, stack->member_size);
	return (1);
}

/*	Function: pop
Pops the element from top of the stack.
stack: pointer to the stack
target: pointer to the target element
Returns: '0' if the stack is already empty,
'1' if element is successfully popped. */
int				pop(t_stack *stack, void *target)
{
	void	*source;

	if (stack->top == -1)
		return (0);
	source = (char*)stack->data + (stack->top * stack->member_size);
	stack->top--;
	if (target)
		memcpy(target, source, stack->member_size);
	return (1);
}

/*	Function: top
Copies the element from top of the stack without decreasing the size.
stack: pointer to the stack
target: pointer to the target element
Returns: '0' if the stack is already empty,
'1' in case of success. */
int				top(t_stack *stack,  void *target)
{
	void	*source;

	if (stack->top == -1)
		return (0);
	source = (char*)stack->data + (stack->top * stack->member_size);
	if (target)
		memcpy(target, source, stack->member_size);
	return (1);
}

/*	Function: free_stack
Frees the allocated stack memory.
stack: pointer to the stack */
void			free_stack(t_stack *stack)
{
	free(stack->data);
	free(stack);
}
