#include <stdbool.h>
#include <unistd.h>

#include "modules/out.h"

static void default_write(char ch) { write(STDOUT_FILENO, &ch, 1); }
static void (*out)(char ch) = &default_write;

void Out_WriteCh(char ch) { out(ch); }

void Out_WriteInt(int x, int n) {
	int i = 0;
	char a[10];
	bool negative = x < 0;
	if (negative) { --n; a[i++] = (char) ('0' - x % 10); x = -(x / 10); }
	else { a[i++] = (char) ('0' + x % 10); x /= 10; }
	while (x > 0) { a[i++] = (char) ('0' + x % 10); x /= 10; }

	while (n > i) { Out_WriteCh(' '); --n; }
	if (negative) { Out_WriteCh('-'); }
	do { --i; Out_WriteCh(a[i]); } while (i > 0);
}

void Out_WriteLn() { Out_WriteCh('\n'); }

void Out_Init_Module() { out = &default_write; }

void Out_set_output(void (*write)(char ch)) { out = write; }
void Out_reset_output() { out = &default_write; }
