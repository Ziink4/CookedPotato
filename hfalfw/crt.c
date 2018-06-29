#define EXIT 60
#define EXIT_GROUP 231

// External ones
long __syscall1(long code, long arg1);
int main(void);

_Noreturn static void exit(int ec)
{
	__syscall1(EXIT, ec);
	for (;;) __syscall1(EXIT_GROUP, ec);
}

_Noreturn void _start()
{
	exit(main());
}
