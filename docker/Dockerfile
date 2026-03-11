FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    nasm \
    qemu-system-x86 \
    make \
    gdb \
    gcc \
    binutils \
    xorriso \
    grub-pc-bin \
    vim \
    nano \
    bsdextrautils \
    git \
    && apt clean

# Create a user that matches my machine user
ARG USER_ID=1000
ARG GROUP_ID=1000
RUN groupadd -g $GROUP_ID maxvth && \
    useradd -u $USER_ID -g $GROUP_ID -m maxvth

USER maxvth
WORKDIR /work
