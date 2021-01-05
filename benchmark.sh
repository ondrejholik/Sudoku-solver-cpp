for x in `ls puzzles/*`
do
  >&2 echo $x
  ./solver < $x > /dev/null
  echo
done
  
