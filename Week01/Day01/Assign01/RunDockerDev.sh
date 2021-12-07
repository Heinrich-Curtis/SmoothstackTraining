#!/usr/bin/bash

#runs the dockerdev container, mounting the directory of my git repo from my host os

host_dir=/mnt/d/CodingStuff/SmoothstackTraining/

echo $host_dir

docker run -it -v $host_dir:/mnt/SmoothstackTraining/ dockerdev bash
