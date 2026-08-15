a.out: main.o createDB.o display.o restore.o save.o search.o slist.o update.o validateFiles.o
	gcc main.o createDB.o display.o restore.o save.o search.o slist.o update.o validateFiles.o

main.o: main.c inverted.h
	gcc -c main.c

createDB.o: createDB.c inverted.h
	gcc -c createDB.c

display.o: display.c inverted.h
	gcc -c display.c

restore.o: restore.c inverted.h
	gcc -c restore.c

save.o: save.c inverted.h
	gcc -c save.c

search.o: search.c inverted.h
	gcc -c search.c

slist.o: slist.c inverted.h
	gcc -c slist.c

update.o: update.c inverted.h
	gcc -c update.c

validateFiles.o: validateFiles.c inverted.h
	gcc -c validateFiles.c

clean:
	rm -f *.o a.out
