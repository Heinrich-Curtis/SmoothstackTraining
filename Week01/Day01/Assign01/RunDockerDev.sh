#!/usr/bin/bash

#runs a dockerdev container, mounting the directory of my git repo from my host os
#note that this is the run command, which CREATES A NEW CONTAINER
#to start the most recent container created, use StartDockerDev
if test $# -eq 1;
	then
		host_dir=/mnt/d/CodingStuff/SmoothstackTraining/
		docker run -it -v $host_dir:/mnt/SmoothstackTraining/ $1 bash
	else

		echo "Usage: RunDockerDev.sh containerName"
fi
