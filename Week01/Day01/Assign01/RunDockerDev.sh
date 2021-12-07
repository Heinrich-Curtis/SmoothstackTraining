#!/usr/bin/bash

#runs a dockerdev container, mounting the directory of my git repo from my host os

host_dir=/mnt/d/CodingStuff/SmoothstackTraining/


docker run -it -v $host_dir:/mnt/SmoothstackTraining/ dockerdev bash
