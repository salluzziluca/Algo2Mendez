FROM ubuntu:20.04

RUN apt-get update && apt-get -y upgrade && apt-get install -y tzdata
RUN apt install -y build-essential
RUN apt install -y valgrind
RUN apt install -y gdb
WORKDIR /home