#include <unistd.h>

extern "C" void WriteCh(char ch) {
	write(STDOUT_FILENO, &ch, 1);
}

extern "C" void WriteInt(int x, int n) {
	int i { 0 };
	char a[16];
	static_assert(sizeof(int) == 4);
	if (x == -2147483648) { a[0] = '-'; a[1] = '2'; i = 2; x = 147483648; }
	else if (x < 0) { a[i] = '-'; ++i; x = -x; }
	do { a[i] = (x % 10) + '0'; x /= 10; ++i; } while (x > 0);
	while (n > i) { WriteCh(' '); --n; }
	write(STDOUT_FILENO, a, i);
}

extern "C" void WriteLn() { WriteCh('\n'); }