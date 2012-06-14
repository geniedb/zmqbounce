all: zbserver zbclient

%: %.cpp
	$(CXX) -lzmq -o $@ $^

run: zbserver zbclient
	./zbserver > /dev/null & ./zbclient
