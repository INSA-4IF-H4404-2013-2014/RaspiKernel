source gdb/os_kernel.gdb
c
c
n
n
n
n
n
si
si
si
si
si
si
si
n
clear kernel_main
clear kernel_scheduler_handler
clear kernel_scheduler_yield
clear kernel_scheduler_yield_noreturn
b kernel_scheduler.c:72
b kernel_scheduler.c:90
b kernel_scheduler.c:100
