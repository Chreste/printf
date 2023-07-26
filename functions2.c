#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, pad = ' ';
	int xnd = BUFF_SIZE - 2, len = 2, pad_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[xnd--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_c = '+', len++;
	else if (flags & F_SPACE)
		extra_c = ' ', len++;

	xnd++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, xnd, len,
		width, flags, pad, extra_c, pad_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[x] != '\0')
	{
		if (is_printable(str[x]))
			buffer[x + offset] = str[x];
		else
			offset += append_hexa_code(str[x], buffer, x + offset);

		x++;
	}

	buffer[x + offset] = '\0';

	return (write(1, buffer, x + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int x, cont = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char z = str[x];

		write(1, &z, 1);
		cont++;
	}
	return (cont);
}
/**
 * print_rot13string - Print a string in rot13.
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int e, g;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (e = 0; str[e]; e++)
	{
		for (g = 0; in[g]; g++)
		{
			if (in[g] == str[e])
			{
				x = out[g];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[g])
		{
			x = str[e];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
