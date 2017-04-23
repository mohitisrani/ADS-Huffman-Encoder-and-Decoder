all:
	g++ -std=c++11 encoder.cpp -o encoder

	g++ -std=c++11 decoder.cpp -o decoder

	cat instructions
