myproject: main.o utills.o symbols.o pre_processor.o hashmap.o first_pass.o error.o second_pass.o
			gcc -g -Wall -ansi -pedantic main.o utills.o symbols.o pre_processor.o hashmap.o first_pass.o error.o second_pass.o -o myproject
main.o: main.c utills.h symbols.h pre_processor.h hashmap.h error.h first_pass.h second_pass.h
		gcc -g -c -Wall -ansi -pedantic main.c -o main.o
utills.o: utills.c utills.h symbols.h error.h
			gcc -g -c -Wall -ansi -pedantic utills.c -o utills.o
symbols.o: symbols.c symbols.h
			gcc -g -c -Wall -ansi -pedantic symbols.c -o symbols.o
pre_processor.o: pre_processor.c pre_processor.h hashmap.h error.h symbols.h utills.h
			gcc -g -c -Wall -ansi -pedantic pre_processor.c -o pre_processor.o
hashmap.o: hashmap.c hashmap.h
			gcc -g -c -Wall -ansi -pedantic hashmap.c -o hashmap.o
first_pass.o: first_pass.c first_pass.h utills.h symbols.h error.h
				gcc -g -c -Wall -ansi -pedantic first_pass.c -o first_pass.o
error.o: error.c error.h
	gcc -g -c -Wall -ansi -pedantic error.c -o error.o
second_pass.o: second_pass.c second_pass.h utills.h symbols.h error.h
				gcc -g -c -Wall -ansi -pedantic second_pass.c -o second_pass.o


