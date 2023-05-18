#!/bin/bash

factorial() {
 if [ $1 -eq 0 ]; then
 echo 1
 else
 prev=$(factorial $(($1 - 1)))
 echo $(($1 * $prev))
 fi
}
echo "Enter a number: "
read num
result=$(factorial $num)
echo "Factorial of $num is: $result"