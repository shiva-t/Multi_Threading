rm *.txt *.o *.exe
gcc -g -c deferred_cancel.c -o deferred_cancel.o
gcc -g deferred_cancel.o -o deferred_cancel.exe -lpthread
