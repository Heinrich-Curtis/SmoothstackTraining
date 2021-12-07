#here's where we add all the features we want
FROM centos:latest
RUN yum update -y
RUN yum -y install vim
RUN yum -y install gdb
RUN dnf -y group install "Development Tools"
RUN yum -y install valgrind
RUN yum -y install clang
RUN yum -y install tree
RUN yum -y install zip
RUN yum -y install curl
#RUN yum -y install iftop
#RUN yum -y install iotop
RUN yum -y install cscope

#we also need to set the environment to the home directory of the host OS (by which I mean,
#the root of this git repo). look at ENV command?
#maybe this is only doable at docker run time, so we need a shell script that sets the fields
#ENV HOME=/mnt/d/CodingStuff/SmoothstackTraining/
