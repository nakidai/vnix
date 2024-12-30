#include <stdbool.h>
#include <ctype.h>

#include <libk/atoi.h>

int katoi(const char* s)
{
	bool negative = false;
	const char* c = s;
	int out       = 0;

	if (*c == '-')
		negative = true;
	c++;

	for (int i = 0; *c != '\0' || !isdigit(*c); c++, i++) {
		out += (*c - '0') * (i * 10);
	}
}
