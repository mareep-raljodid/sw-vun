TARGET = retlib 

all: ${TARGET}

setuid: ${TARGET}
	sudo chown root ${TARGET}
	sudo chmod u+s ${TARGET}

N = 412
retlib: retlib.c
	gcc -m32 -g -DBUF_SIZE=${N} -fno-stack-protector -z noexecstack -o $@ $@.c

clean:
	rm -f *.o *.out ${TARGET} badfile



echo "startxfce4" > ~/.xsession; chmod +x ~/.xsession;sudo systemctl restart xrdp.service