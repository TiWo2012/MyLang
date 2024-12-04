#!/bin/bash

docker stop mylang-container
docker rm mylang-container
docker build -t mylang .
docker run -d -p 2222:22 -v $(pwd)/:/app/ --name mylang-container mylang 
ssh dockeruser@localhost -p 2222
