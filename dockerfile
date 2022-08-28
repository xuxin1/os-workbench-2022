FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN echo 'root:123123' | chpasswd
RUN apt-get update
RUN apt-get install -y  gcc-9-riscv64-linux-gnu
RUN apt-get install -y build-essential
RUN apt-get install -y gcc-multilib
RUN apt-get install -y qemu-system
RUN apt-get install -y strace
RUN apt-get install -y gdb
RUN apt-get install -y sudo
RUN apt-get install -y python3
RUN apt-get install -y libsdl2-dev
RUN apt-get install -y libreadline-dev
RUN apt-get install -y llvm-11
RUN apt-get install -y gcc-riscv64-linux-gnu
RUN useradd -ms /bin/bash user
USER user
WORKDIR /home/user
