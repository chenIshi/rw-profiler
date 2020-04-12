ddl = libio.so
exec = main
cc = gcc
srcDir = src
ddlDir = /tmp
testDir = test
output = ouput.txt

all : $(ddl) $(exec)

# gcc -D_GNU_SOURCE -shared -Wl,--no-as-needed -ldl -fPIC io.c -o /tmp/libio.so

LDFLAG:= -D_GNU_SOURCE -shared -Wl,--no-as-needed -ldl -fPIC

$(ddl) : $(srcDir)/*.c
	$(cc) $(LDFLAG) -o $(ddlDir)/$(ddl) $<

$(exec) : $(testDir)/$(exec).c
	$(cc) $< -o ./$(testDir)/$(exec)

# LD_PRELOAD=/tmp/libhotspot.so ./main

test : $(ddl) $(exec)
	@echo "### Clone test ###"
	@rm -f $(testDir)/$(output)
	@cd $(testDir) && LD_PRELOAD=$(ddlDir)/$(ddl) ./$(exec)
	@rm -f $(testDir)/$(output)

.PHONY: clean

clean:
	rm ./$(testDir)/$(exec)