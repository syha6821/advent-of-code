app: *.o
	g++ -std=c++14 *.o -o app

*.o: *.cpp *.h
	g++ -c -std=c++14 *.cpp

clean:
	rm *.o app

run : app
	./app
