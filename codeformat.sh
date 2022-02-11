#!/bin/bash

find src/ include/ test/ -type f -name '*.c' -o -name '*.h' | xargs -i clang-format -i {}
