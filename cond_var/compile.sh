gcc -g -c queue.c -o queue.o
gcc -g -c cond_var.c -o cond_var.o
gcc -g cond_var.o queue.o -o run.exe -lpthread
