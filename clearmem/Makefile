build:
	ca65 clearmem.asm -o clearmem.o
	ld65 -C nes.cfg clearmem.o -o clearmem.nes

clean:
	rm *.o *.nes

run:
	fceux clearmem.nes

getschwifty:
	make build
	make run
	make clean
