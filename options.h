#include <getopt.h>
#include <string>

struct options {
	std::string clientURL;
	std::string pubURL;
	bool flood;
	options() :
		clientURL("tcp://127.0.0.1:5655"),
		pubURL("epgm://;224.0.0.1:5656"),
		flood(false)
		{}

	void configure(int argc, char **argv) {
		struct option longopts[] = {
			{"help",	0, NULL, 'h'},
			{"client-url",	1, NULL, 'c'},
			{"pub-url",	1, NULL, 'p'},
			{"flood",	0, NULL, 'f'},
			{0, 0, 0, 0}
		};
		while (true) {
			int longindex;
			int opt = getopt_long(argc, argv, "hf", longopts, &longindex);
			if (opt == '?')
				usage(argv[0], 1);
			else if (opt == 'h')
				usage(argv[0]);
			else if (opt == 'f')
				flood = true;
			else if (opt == 'c')
				clientURL = optarg;
			else if (opt == 'p')
				pubURL = optarg;
			else if (opt == -1)
				break;
		}
	}

	void usage(const char* program_invocation_name, int status=0) {
		exit(status);
	}

};

