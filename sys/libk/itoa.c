/*
	Permission to use, copy, modify, and/or distribute this software for
	any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
	FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
	DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
	AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
	OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
	AUTHOR: gimura2022 <gimura0001@gmail.com>
	DATE  : 31.12.2024
	FILE  : sys/libk/itoa.c

	int to string converter function header
*/

#include <stdbool.h>

static void reverse(char* str, int len);

char* kitoa(int num, char* buf, int base)
{
	int i            = 0;
	bool is_negative = false;

	if (num == 0) {
		buf[i++] = '0';
		buf[i]   = '\0';
	}

	if (num < 0 && base == 10) {
		is_negative = true;
		num         = -num;
	}

	while (num != 0) {
		int rem  = num % base;
		buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num      = num / base;
	}

	if (is_negative)
		buf[i++] = '-';

	buf[i] = '\0';

	reverse(buf, i);

	return buf;
}

static void reverse(char* str, int len)
{
	int start = 0;
	int end   = len - 1;

	while (start < end) {
		char tmp   = str[start];
		str[start] = str[end];
		str[end]   = tmp;

		end--;
		start++;
	}
}
