#include <vnix/kio.h>

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
