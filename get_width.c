#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */

int get_width(const char *format, int *i, va_list list)
{
	int curr_x;
	int w = 0;

	for (curr_x = *i + 1; format[curr_x] != '\0'; curr_x++)
	{
		if (is_digit(format[curr_x]))
		{
			w *= 10;
			w += format[curr_x] - '0';
		}
		else if (format[curr_x] == '*')
		{
			curr_x++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_x - 1;

	return (w);
}
