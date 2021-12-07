#here's where we add all the features we want
FROM centos:latest
RUN yum update -y
RUN yum -y install vim
RUN yum -y install gdb
RUN dnf -y group install "Development Tools"
RUN yum -y install valgrind
RUN yum -y install clang

#we also need to set the environment to the home directory of the host OS (by which I mean,
#the root of this git repo). look at ENV command?

#here's where we add the command that instantly puts us in the container on startup

