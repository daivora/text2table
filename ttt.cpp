#include <iostream>
#include <fstream>
int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Use:\n"
			  << "	text2table sourse destination\n";
		return 1;
	}

	std::ifstream inFile(argv[1]);
	if (!inFile) {
		std::cout << "Can not open file '" << argv[1] << "'\n";
		return 2;
	}
	//1. Ïðîéòè ïî ôàéëó è ïîäñ÷èòàòü øèðèíû ñòîëáöîâ.
	int lenwords[200] = { 0 };
	int wordlen = 0;
	int wordnum = 0;
	int ch;
	while ((ch = inFile.get()) != EOF) {
		if (ch == ' ' || ch == '\t') {
			if (wordlen != 0) {
				if (lenwords[wordnum] < wordlen) {
					lenwords[wordnum] = wordlen;
				}
				wordlen = 0;
				++wordnum;
			}
		}
		else if (ch == '\n') {
			if (lenwords[wordnum] < wordlen) {
				lenwords[wordnum] = wordlen;
			}
			wordlen = 0;
			wordnum = 0;
		}
		else {
			++wordlen;
		}
	}
	if (wordlen != 0) {
		if (lenwords[wordnum] < wordlen) {
			lenwords[wordnum] = wordlen;
		}
	}
	for (int i = 0; i < 200; ++i) {
		std::cout << lenwords[i] << std::endl;
	}
	return 0;
}
