#!/bin/bash

make
echo "starting server"
./server &
SERVER_PID=$!
echo $SERVER_PID
echo "starting client"
./client localhost
echo "shutting down server"
kill $SERVER_PID
make clean
