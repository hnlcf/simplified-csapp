#!/bin/bash

echo "Count lines for all .c and .h files"
echo "==========================================>"

find src/ include/ test/ -name '*.[ch]' | xargs wc -l | sort