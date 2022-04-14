#Add required tools
FROM fedora:latest
RUN dnf -y update
RUN dnf -y upgrade
#RUN dnf --fix-missing -y install build-essential doesn't work because one of the packages
#near the end was removed from ubuntu
#dev tools
RUN dnf -y install vim 
#RUN dnf -y install gcc
RUN dnf -y install g++ 
RUN dnf -y install gdb 
RUN dnf -y install valgrind 
#RUN dnf -y install clang
#utilities
RUN dnf -y install tree
RUN dnf -y install zip
RUN dnf -y install curl
RUN dnf -y install htop
RUN dnf -y install iftop
RUN dnf -y install iotop
RUN dnf -y install cscope
#more stuff for the capstone

#eventually we need networking stuff: connecting our 8080

#I just made a minor change to the supplied bashrc (I added an alias for ls -a) to show this works
#you CANNOT use ~ here, the glob expansion is not done correctly
ADD .bashrc /root/.bashrc

