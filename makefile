complie : main9.cpp
	g++ main9.cpp -o dnt

run : dnt
	./dnt

clean : dnt
	rm dnt