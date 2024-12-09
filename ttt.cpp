#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Use:\n"
              << "   text2table source destination\n";
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cout << "Can not open file '" << argv[1] << "'\n";
    return 2;
  }
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
    std::cout << lenwords[i] << " ";
  }
  inFile.clear();
  inFile.seekg(0); 
  std::ofstream outFile(argv[2]);
  if (!outFile.is_open()) {
    std::cout << "Can not write to file '" << argv[2] << "'\n";
    inFile.close();
    return 3;
  }
  wordlen = 0;
  wordnum = 0;
  int char_counter = 0;
  while ((ch = inFile.get()) != EOF) {
    if (ch == ' ' || ch == '\t') {
      if (wordlen != 0) {
        ++wordnum;
        wordlen = 0;
      }
    }
    else if (ch == '\n') {
	    outFile.put('\n');
      wordnum = 0;
      wordlen = 0;
      char_counter = 0;
    }
    else { 
      if (wordlen == 0 && wordnum > 0) {
        while (char_counter <= lenwords[wordnum-1]) {
          outFile.put(' ');
          ++char_counter;
        }
        char_counter = 0;
      }
      outFile.put(ch);
      ++wordlen;
      ++char_counter;
    }
  }
  inFile.close();
  outFile.close();
}
