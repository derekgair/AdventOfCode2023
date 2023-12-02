in one line:
```
cat data.txt | tr -d "[A-Z][a-z]" | while read l ; do f=${l:0:1}; l=$(echo $l| rev|cut -b 1);echo $l : $((t+=$f$l)); done
```
