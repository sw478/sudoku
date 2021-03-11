#!/bin/bash
USAGE="[ q:quit | m:make | b:basic | t:time ]"

while true; do

echo
echo $USAGE
read type

if [ "$type" = "q" ]; then
   exit 0

elif [ "$type" = "m" ]; then
   make clean
   make

elif [ "$type" = "b" ] || [ "$type" = "t" ] || [ "$type" = "v" ]; then
   echo "problem:"
   echo "\"s\" for sudoku"
   echo "\"sg\" for generating sudoku"
   echo "\"s2\" for sudoku2"
   echo "\"so\" for sudoku orientation"
   echo "\"sgo\" for sudoku gen orientation"
   echo "\"q\" for n queens"
   read problem

   if [ "$problem" = "s" ] || [ "$problem" = "s2" ] || [ "$problem" = "so" ]; then
      echo "dimension? \"x\" \"y\""
      read x y
      
      if [ "$type" = "t" ]; then
         make
         time ./a.out ${problem} tests/${x}x${y}.txt

      elif [ "$type" = "v" ]; then
         make
         valgrind --leak-check=full --error-exitcode=13 --track-origins=yes ./a.out ${problem} tests/${x}x${y}.txt

      elif [ "$type" = "b" ]; then
         make
         ./a.out ${problem} tests/${x}x${y}.txt
      fi

   elif [ "$problem" = "q" ]; then
      echo "n?"
      read n

      if [ "$type" = "t" ]; then
         time ./a.out ${problem} ${n}

      elif [ "$type" = "v" ]; then
         valgrind --leak-check=full --error-exitcode=13 --track-origins=yes ./a.out q ${n}

      elif [ "$type" = "b" ]; then
         make
         ./a.out q ${n}
      fi
   
   elif [ "$problem" = "sg" ] || [ "$problem" = "sgo" ]; then
      echo "dimension? \"x\" \"y\""
      read x y
      
      if [ "$type" = "t" ]; then
         time ./a.out ${problem} tests/${x}x${y}.txt ${x} ${y}

      elif [ "$type" = "v" ]; then
         valgrind --leak-check=full --error-exitcode=13 --track-origins=yes ./a.out ${problem} tests/${x}x${y}.txt ${x} ${y}

      elif [ "$type" = "b" ]; then
         make
         ./a.out ${problem} tests/${x}x${y}.txt ${x} ${y}
      fi

   fi

fi

done