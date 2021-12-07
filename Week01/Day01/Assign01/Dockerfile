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
#still stuck on getting bashrc imported