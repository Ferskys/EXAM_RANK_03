/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:55:31 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/08 12:02:47 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h> 

int ft_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void ft_putstr(char *str) {
    write(1, str, ft_strlen(str));
}

void ft_putnbr_hex(unsigned int n) {
    char hex_digits[] = "0123456789abcdef";
    if (n >= 16)
        ft_putnbr_hex(n / 16);
    write(1, &hex_digits[n % 16], 1);
}

int ft_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;
    int i = 0;
    while (format[i] != '\0') {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            if (format[i] == 's') {
                char *str = va_arg(args, char *);
                ft_putstr(str);
                written += ft_strlen(str);
            } else if (format[i] == 'd') {
                int num = va_arg(args, int);
                char num_str[12]; // Assuming a maximum of 11 digits for an int
                int len = snprintf(num_str, sizeof(num_str), "%d", num);
                write(1, num_str, len);
                written += len;
            } else if (format[i] == 'x') {
                unsigned int num = va_arg(args, unsigned int);
                ft_putnbr_hex(num);
                written += sizeof(unsigned int) * 2; // Each hex digit is 4 bits
            } else {
                // Unsupported conversion specifier, just print the character
                write(1, &format[i], 1);
                written++;
            }
        } else {
            write(1, &format[i], 1);
            written++;
        }
        i++;
    }

    va_end(args);
    return written;
}

int main() {
    ft_printf("%s\n", "toto");
    ft_printf("Magic %s is %d\n", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    return 0;
}
