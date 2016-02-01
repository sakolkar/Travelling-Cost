make clean
make main
make datagen
make serialtester

./datagen
./main $1
./serialtester

echo "Time taken: "
sed '3q;d' data_output
