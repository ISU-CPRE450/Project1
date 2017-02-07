cc=GCC

all: rpc client server

rpc:
		rpcgen -k rsm.x

client:
		gcc -o client client.c rsm_clnt.c

server:
		gcc -o server server.c rsm_svc.c

.PHONY: clean
clean:
		@rm -rf *.o rsm_clnt.c rsm.h rsm_svc.c client server
		@echo "Directory cleaned"
