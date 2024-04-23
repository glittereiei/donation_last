complie : main10.cpp
	g++ main10.cpp -o dnt

run : dnt
	./dnt

clean : dnt
	rm dnt