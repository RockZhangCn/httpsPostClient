#CC=arm-uclibc-gcc
CC=gcc

FLAGS = -Wall -Werror -fPIC -g -O2 -s -ldl -lm -o


SC_LIBRARY_PATH = ../httpspost

SOURCE_FILE = example.cpp libhttpspost_x86.so

ifeq ($(CC),gcc)
OBJ = example
LIB = -lstdc++     \
      -lhttpspost_x86
else
OBJ = exsmple_arm
LIB = -lstdc++     \
      -lhttpspost_arm
endif

    
$(OBJ): $(SOURCE_FILE)
	$(CC) $(FLAGS)  $@  $(SOURCE_FILE)  -L$(SC_LIBRARY_PATH) $(LIB)

    
#SERVER_SOURCE_FILE = server.c
#ssl_server: $(SERVER_SOURCE_FILE)
#	$(CC) $(FLAGS)  $@  $(SERVER_SOURCE_FILE) $(LIB)
    
    
clean:
	rm -rf $(OBJ)
	rm -rf ssl_server

.PHONY: clean
