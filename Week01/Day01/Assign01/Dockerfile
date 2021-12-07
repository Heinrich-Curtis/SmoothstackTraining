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
#RUN dnf -y install htop
#RUN yum -y install iftop
#RUN yum -y install iotop
RUN yum -y install cscope
#I just made a minor change to the supplied bashrc (I added an alias for ls -a) to show this works
ADD .bashrc /root/.bashrc
