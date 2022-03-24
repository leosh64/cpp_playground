all: clean plot.png

plot.png: results.txt
	gnuplot plotting.gnuplot

results.txt: benchmark
	rm -f results.txt
	echo "size, sort, partialsort, nthelement" | tee -a results.txt
	./benchmark 1000 | tee -a results.txt
	./benchmark 10000 | tee -a results.txt
	./benchmark 100000 | tee -a results.txt
	./benchmark 200000 | tee -a results.txt
	./benchmark 400000 | tee -a results.txt
	./benchmark 800000 | tee -a results.txt
	./benchmark 1600000 | tee -a results.txt
	./benchmark 3200000 | tee -a results.txt
	./benchmark 6400000 | tee -a results.txt
	./benchmark 12800000 | tee -a results.txt
	./benchmark 25600000 | tee -a results.txt
	./benchmark 51200000 | tee -a results.txt
	./benchmark 100000000 | tee -a results.txt
	./benchmark 200000000 | tee -a results.txt
	./benchmark 400000000 | tee -a results.txt
	./benchmark 800000000 | tee -a results.txt
	./benchmark 1600000000 | tee -a results.txt
	# ./benchmark 3200000000 | tee -a results.txt # enable if you have enough memory

benchmark:
	$(CXX) -O3 partialsort.cpp -o benchmark

clean:
	rm -f benchmark results.txt plot.png
