#!/bin/bash

make -f makefile clean 2>&1
make -f makefile valgrind 2>&1

