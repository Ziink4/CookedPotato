# HFALFW : Hello From A LibC-Free World - Experiments
https://blogs.oracle.com/linux/hello-from-a-libc-free-world-part-1-v2
https://blogs.oracle.com/linux/hello-from-a-libc-free-world-part-2-v2


Baseline :
```
clang -o hello hello.c
wc -c hello //Byte count
objdump -t hello //Symbol count
```

No printf (segfault on exit) :
```
clang -nostdlib -o hello_no_printf hello_no_printf.c 
```

Link manually with crt1.o
```
clang -Os -c hello_no_printf.c
ld /usr/lib/crt1.o -o hello_no_printf hello_no_printf.o
```

With custom start :
```
clang-6.0 -nostdlib -o hello_no_printf start.S hello_no_printf.c 
```

Disassemble :
```
objdump -d hello_no_printf
```

With all I could find of the best :
```
clang-6.0 -Wall -Wextra -std=c11 -O3 -s -march=native -flto -pipe -fno-asynchronous-unwind-tables -nostdlib syscall1.S crt.c hello_no_printf.c

```
