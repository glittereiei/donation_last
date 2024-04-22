complie : main5.cpp
	g++ main5.cpp -o dnt

run : dnt
	./dnt

clean : dnt
	rm dnt