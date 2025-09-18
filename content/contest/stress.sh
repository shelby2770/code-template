#!/bin/bash
cf gen > in             # input generator
cf bf < in > exp        # bruteforce
cf code < in > out      # buggy code name

for ((i = 1; ; ++i)) do
   echo $i
   ./gen > in
   ./bf < in > exp
   ./code < in > out    # buggy code name
   diff -w exp out || break
done
# Shows expected first, then user
notify-send "bug found!!!!"

