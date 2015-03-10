all: main nsigma_xsec

main: main.o LLR.o
	g++ main.o LLR.o -o main `root-config --libs`

main.o: main.cxx
	g++ main.cxx -c -o main.o `root-config --cflags`

nsigma_xsec: nsigma_xsec.o NSigmaFitter.o LLR.o
	g++ nsigma_xsec.o LLR.o NSigmaFitter.o -o nsigma_xsec `root-config --libs` -lMinuit2

nsigma_xsec.o: nsigma_xsec.cxx
	g++ nsigma_xsec.cxx -c -o nsigma_xsec.o `root-config --cflags`

NSigmaFitter.o: NSigmaFitter.cxx
	g++ NSigmaFitter.cxx -c -o NSigmaFitter.o `root-config --cflags`

LLR.o: LLR.cxx
	g++ LLR.cxx -c -o LLR.o `root-config --cflags`

clean:
	rm main nsigma_xsec *.o
