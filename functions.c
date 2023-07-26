#include "main.h"

/**
 * print_char - Prints a char
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * print_string - Prints a string
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, x;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/**
 * print_percent - Prints a percent sign
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Prints int.
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(m, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[x--] = (num % 10) + '0';
		num /= 10;
	}

	x++;

	return (write_number(is_negative, x, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: get Width
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, x, sum;
	unsigned int e[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	e[0] = n / m;
	for (x = 1; x < 32; x++)
	{
		m /= 2;
		e[x] = (n / m) % 2;
	}
	for (x = 0, sum = 0, count = 0; x < 32; x++)
	{
		sum += e[x];
		if (sum || x == 31)
		{
			char z = '0' + e[x];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
