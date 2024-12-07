
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

class File_work {
public:

	void ImportCode(string& code) {
		FILE* InpFile = fopen("input.txt", "r");
		char c = fgetc(InpFile);
		while (c != EOF) {
			code.push_back(c);
			c = fgetc(InpFile);
		}
	}

	void ImportToFile(vector<pair<string, int>> ErrorVec) {
		ofstream file("output.txt");
		if (ErrorVec.size() == 0) {
			file << "Break is used correctly!";
		}
		else {
			for (int i = 0; i < ErrorVec.size(); i++) {
				file << ErrorVec[i].second << "> Error: " << ErrorVec[i].first << "\n";
			}
		}
		file.close();
	}
};