make clean
make main
make datagen
make serialtester

./datagen -s $2
./main $1
./serialtester

echo "Time taken: "
sed '3q;d' data_output
