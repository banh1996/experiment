CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wmissing-prototypes -Wuninitialized -Wno-return-local-addr -Wunused -Wextra -pthread -g

all: flash_tool uds_tool

flash_tool: app_flash_tool.c
	$(CC) $(CFLAGS) -o flash_tool app_flash_tool.c

uds_tool: app_uds_tool.c
	$(CC) $(CFLAGS) -o uds_tool app_uds_tool.c

clean:
	rm -rf uds_tool flash_tool
