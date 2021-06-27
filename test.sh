#!/bin/bash

set -e

echo ">>>>>>>>>>> Sequential Read"
gcc -Wall -Werror -Wextra main2.c get_next_line.c   -o a.out
gcc -Wall -Werror -Wextra main2_generator.c -o gen.out
./gen.out > ours
./a.out > yours || (echo EXECUTION FAILED && exit 1)
diff yours ours  || (echo FAILED && exit 1)
rm -f yours ours
rm -f a.out gen.out
