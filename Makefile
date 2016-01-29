main:
	gcc -g -Wall -o main src/main.c src/Lab2IO.c -lm -lphread

datagen:
	gcc -Wall -o datagen src/datagen.c src/Lab2IO.c

serialtester:
	gcc -Wall -o serialtester src/serialtester.c

clean:
	rm main data_input data_output lab2sol_bar serialtester datagen
