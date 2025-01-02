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
	DATE  : 3.1.2025
	FILE  : sys/kio.c

	kernel IO
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include <vnix/kio.h>

#include <libk/itoa.h>

#define MSG_OFFSET 40

static kio_putc_f puter;

void kio_set(kio_putc_f func)
{
	puter = func;
}

void kputc(char c)
{
	puter(c);
}

void kputs(const char* s)
{
	for (const char* c = s; *c != '\0'; c++)
		puter(*c);
}

void kprintf(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	bool format = false;
	char num_buf[128];

	for (const char* c = fmt; *c != '\0'; c++) {
		if (*c == '%') {
			format = true;
			continue;
		}

		if (format) switch (*c) {
		case 's':
			kputs(va_arg(list, const char*));
			continue;

		case 'i':
			kputs(kitoa(va_arg(list, int32_t), num_buf, 10));		
			continue;

		case 'u':
			kputs(kitoa(va_arg(list, uint32_t), num_buf, 10));
			continue;
		}

		kputc(*c);
	}

	va_end(list);
}

static void off_msg(const char* msg);

void kok(void)
{
	off_msg("OK\n");
}

void kerr(const char* msg)
{
	off_msg("ERROR: ");
	kputs(msg);
}

static void off_msg(const char* msg)
{
	kputc('\r');
	for (int i = 0; i < MSG_OFFSET; i++)
		kputc('\?');

	kputs(msg);
}
