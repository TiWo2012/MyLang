# File to test bash functions to then implement them in the compiler

#!/bin/bash

x=0

if [ $x -eq 1 ]; then
    echo "True"

    exit 1
fi

exit 0