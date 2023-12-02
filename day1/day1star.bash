cat data.txt |
while read line
do
    echo -n $line :
    line=${line//one/o1e}
    line=${line//two/t2o}
    line=${line//three/t3e}
    line=${line//four/f4r}
    line=${line//five/f5e}
    line=${line//six/s6x}
    line=${line//seven/s7n}
    line=${line//eight/e8t}
    line=${line//nine/n9e}
    echo -n $line :
    line=$( echo $line | tr -d [A-Za-z] )
    first=${line:0:1}
    last=$(echo $line | rev | cut -b 1)
    echo $line : $first : $last : $((total+=${first}${last}))
done
