# Remote System Monitoring using RPC

## Overview
In this project, we created a server that a client could communicate with
via RPC. The server has three different functions (or batches of data) that
the client can request for. The server can give the client the following
information: Current System Time, CPU Usage, Memory Usage, and Load Procs per
min.

## Usage
To run this program, run the following commands in your shell:

`make`

`./server &`

`./client localhost`

At this point, you will be interacting with the program. After you exit the
program, run:
`kill <PID>`, where `<PID>` is the pid of the server.
You can run `make clean` to clean the directory.
