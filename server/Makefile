# YOU WILL NEED TO CHANGE THE FOLLOWING LINE, 
# DEPENDING ON WHERE YOU PLACE THIS DIRECTORY
include ../../xia-core/xia.mk

CFLAGS += -g
LDFLAGS += $(LIBS)


all: ContentServer CidDirectoryServer


# Makes for Content Servers 1 2 3 and 4
ContentServer: ContentServer.o Utility.o
	g++ -Wall -Wextra $(CFLAGS) -o $@ ContentServer.o Utility.o $(LDFLAGS)
	cp ContentServer ContentServer1
	cp ContentServer ContentServer2
	cp ContentServer ContentServer3
	cp ContentServer ContentServer4
	rm ContentServer

ContentServer.o: ContentServer.cpp Utility.h
	g++ -Wall -Wextra $(CFLAGS) -c ContentServer.cpp


# Just the CID directory functionality
CidDirectoryServer: CidDirectoryServer.o Utility.o
	g++ -Wall -Wextra $(CFLAGS) -o $@ CidDirectoryServer.o Utility.o $(LDFLAGS)

CidDirectoryServer.o: CidDirectoryServer.cpp Utility.h
	g++ -Wall -Wextra $(CFLAGS) -c CidDirectoryServer.cpp

Utility.o: Utility.h Utility.cpp
	g++ -Wall -Wextra $(CFLAGS) -c Utility.cpp


clean:
	rm *.o CidDirectoryServer ContentServer
