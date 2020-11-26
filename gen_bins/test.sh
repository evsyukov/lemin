#!/bin/bash


##   --flow-one : generates an ant farm with distinctive path and [1] ant in it ## 
##   --flow-ten : generates an ant farm with distinctive path and approximately [10] ants in it
##   --flow-thousand : generates an ant farm with distinctive path and approximately [100] ants in it
##   --big : generates a big map (approximately [1000] rooms) to test the time complexity
##   --big-superposition : generates a big map with overlapping paths

VAR=$(./generator_scale  --big-superposition)

echo "$VAR" | tail -n 1

echo -e "OUR :\c"

time echo "$VAR" | ../lem-in -m | wc -l

