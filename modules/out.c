#include <stdbool.h>
#include <unistd.h>

static void default_write(char ch) { write(STDOUT_FILENO, &ch, 1); }
static void (*out)(char ch) = &default_write;

void WriteCh(char ch) { out(ch); }

void WriteInt(int x, int n) {
	int i = 0;
	char a[10];
	bool negative = x < 0;
	if (negative) { --n; a[i++] = (char) ('0' - x % 10); x = -(x / 10); }
	else { a[i++] = (char) ('0' + x % 10); x /= 10; }
	while (x > 0) { a[i++] = (char) ('0' + x % 10); x /= 10; }

	while (n > i) { WriteCh(' '); --n; }
	if (negative) { WriteCh('-'); }
	do { --i; WriteCh(a[i]); } while (i > 0);
}

void WriteLn() { WriteCh('\n'); }

void Init_Module() { out = &default_write; }

void set_output(void (*write)(char ch)) { out = write; }
void reset_output() { out = &default_write; }
