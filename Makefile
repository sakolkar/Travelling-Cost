main:
	gcc -g -Wall -o main src/main.c src/Lab2IO.c -lm -lpthread

datagen:
	gcc -o datagen src/datagen.c src/Lab2IO.c

serialtester:
	gcc -o serialtester src/serialtester.c src/Lab2IO.c

clean:
	rm main data_input data_output lab2sol_bar serialtester datagen
