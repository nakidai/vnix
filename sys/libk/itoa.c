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
