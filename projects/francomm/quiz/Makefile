CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc testme.c -o testme $(CFLAGS) 

runtest:
	./testme >> results.out
	gcov -b -u testme.c >> results.out
	cat testme.c >> results.out
clean:
	rm -f testme
