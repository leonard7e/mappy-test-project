
all: mymap
	echo "Jetzt wird das Programm kompiliert!"

clean: mymap main.o spielfeld.o sitzung.o
	rm $^

mymap: main.o spielfeld.o sitzung.o
	gcc $^ -o mymap

%.o: %.c
	gcc -o $@ -c $^
