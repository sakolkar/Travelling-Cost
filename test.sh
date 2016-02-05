make clean
make main
make datagen
make serialtester

loops=100

#!/bin/bash
for((c=1; c<=$loops; c++))
do
    ./datagen -s $2
    ./main $1
    
    if (./serialtester | grep -q wrong)
    then
        echo "Failed on $c"
        break
    fi

    if (($c == $loops/10)); then
        echo -ne '#            (10%)\r'
    fi

    if (($c == $loops*2/10)); then
        echo -ne '##           (20%)\r'
    fi

    if (($c == $loops*3/10)); then
        echo -ne '###          (30%)\r'
    fi

    if (($c == $loops*4/10)); then
        echo -ne '####         (40%)\r'
    fi

    if (($c == $loops*5/10)); then
        echo -ne '#####        (50%)\r'
    fi

    if (($c == $loops*6/10)); then
        echo -ne '######       (60%)\r'
    fi

    if (($c == $loops*7/10)); then
        echo -ne '#######      (70%)\r'
    fi

    if (($c == $loops*8/10)); then
        echo -ne '########     (80%)\r'
    fi

    if (($c == $loops*9/10)); then
        echo -ne '#########    (90%)\r'
    fi

    if (($c == $loops)); then
        echo -ne '##########  (100%)\r'
    fi

done
echo -ne '\n'
echo "Time taken: "
sed '3q;d' data_output
