CFLAGS = -Wall -pedantic -std=gnu99 -g -I/local/courses/csse2310/include
LDFLAGS = -L/local/courses/csse2310/lib -lcsse2310a1

all: uqwordiply
uqwordiply: uqwordiply.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm uqwordiply

reallyclean:
	rm uqwordiply
	rm *.stdout
	rm *.stderr
	rm -rf testfiles
