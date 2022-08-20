FILES = address_analizer.c base32.c dynamic_string.c main.c operations_table.c registers.c static_arrays.c address_table.c dictionary.c first_process.c memory_image.c pre_processor.c second_process.c symbol_table.c
OBJ = $(FILES:.c=.o)

OUTPUT = Assembler

Assembler: $(OBJ) 
	gcc -Wall -ansi -pedantic $(FILES) -o $(OUTPUT) -lm

.PHONY: clean

clean:
	rm -f *.o