cat data.txt |tr -d "[A-Z][a-z]" |
while read line
do 
    first=${line:0:1}
    last=$(echo $line | rev | cut -b 1)
    echo $line : $((total+=${first}${last}))
done
