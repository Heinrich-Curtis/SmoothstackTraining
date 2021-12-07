#!/usr/bin/bash

#runs a dockerdev container, mounting the directory of my git repo from my host os
#note that this is the run command, which CREATES A NEW CONTAINER
#to start the most recent container created, use StartDockerDev
host_dir=/mnt/d/CodingStuff/SmoothstackTraining/
docker run -it -v $host_dir:/mnt/SmoothstackTraining/ dockerdev bash