#!/bin/bash

#starts the most recent docker dev image available without creating a new container
container=`docker ps -a|tail -1|awk '{print $1}'`
docker start $container
docker exec -it  $container bash 
