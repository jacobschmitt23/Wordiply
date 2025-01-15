CFLAGS = -Wall -pedantic -std=gnu99

all: uqwordiply
uqwordiply: uqwordiply.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm uqwordiply

reallyclean:
	rm uqwordiply
	rm *.stdout
	rm *.stderr
	rm -rf testfiles
