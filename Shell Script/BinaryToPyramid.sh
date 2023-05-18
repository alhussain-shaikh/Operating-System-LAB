#!/bin/bash
echo "Enter a binary number: "
read binary
decimal=0
for ((i=${#binary}-1;i>=0;i--)); do
 bit=${binary:i:1}
 if [ "$bit" -eq 1 ]; then
 decimal=$((decimal + 2**((${#binary}-1-i))))
 fi
done
echo "The decimal equivalent of $binary is: $decimal"