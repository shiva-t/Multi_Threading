rm *.o *.exe *.txt
gcc -c -g asynch_cancel.c -o asynch_cancel.o
gcc -g asynch_cancel.o -o asynch_cancel.exe -lpthread
