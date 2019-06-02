# c_calculator

Simple mathematical equations evaluator in C language.
It is a simple program, that takes an equasion in 'human readable'
mathematical notation and evaluates it. The result is printed to console,
format depends on the numerical presition of the value (integer or fractional
with 3 points presition) and '0' is returned.

In case of an invalid input or calculation error the program returns '-1' and
nothing is printed.

Input format:
	- mathematical operators: '+', '-', '*', '/';
	- parenthesis: '(' and ')';
	- integer values (i.e. '3', '14', '159');
	- fractional numbers (i.e. '3.14159');

To compile executable, run 'make' command.

```
Usage: ./calculator "1 + 2 + 3"
	./calculator "-3.3333333333333333333 + 8 * 2 - ((567/13) +5) * 13"
	./calculator "-5 + 8 - (3 * (17 / 13))"
```
