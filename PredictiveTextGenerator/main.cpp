#include <vector>
#include <map>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

//Higher number means more words of the original document are used as context. If set too high, the output will just be the original document. If changed, recompile with "make".
const int CONTEXT = 2;

//OUTPUT_SIZE determines how many words are generated in the predictive text. If changed, recompile with "make".
const int OUTPUT_SIZE = 150;

int main(int argc, char * argv[]) {
  vector<string> tokens;
	map <list<string>, vector<string>> wordMap;

	//Initializes state as CONTEXT blanks
	list<string> state;
	for (int i = 0; i < CONTEXT; i++) {
		state.push_back("");
	}

  string next_line;  // Each line of text
	string fileName = argv[1];

  ifstream inFile(fileName);

	//creates a vector, named tokens, of all
	//words in the text file
  while (getline(inFile, next_line)) {
    istringstream iss(next_line);
    string token;
		
    while (iss >> token) {
      string nopunct = "";
      for (auto &c : token) { // For each char in word   
				if (isalpha(c)) {
					nopunct += c;
				}
      }
	  	tokens.push_back(nopunct);
		}
  }


	for (int i = 0; i < tokens.size(); i++) {
		wordMap[state].push_back(tokens.at(i));
		state.push_back(tokens.at(i));
		state.pop_front();
	}

	cout << endl;
	srand(time(NULL));

	state.clear();
	for (int i = 0; i < CONTEXT; i++) {
		state.push_back("");
	}
	for (int i = 0; i < OUTPUT_SIZE; i++) {
		int index = rand() % wordMap[state].size();
		cout << wordMap[state][index] << " ";
		state.push_back(wordMap[state][index]);
		state.pop_front();
	}
  cout << endl;

	return 0;
}