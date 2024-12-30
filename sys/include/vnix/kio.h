#ifndef _vnix_kio_h
#define _vnix_kio_h

typedef void (*kio_putc_f)(char);

void kio_set(kio_putc_f puter);

void kputc(char c);
void kputs(const char* s);

void kok(void);
void kerr(const char* msg);

#endif
