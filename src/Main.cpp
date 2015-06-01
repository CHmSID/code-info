//This code is under GPL2 license.
//Original author: Jerzy Baran

#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::ifstream;
using std::string;

void listFiles(string);
bool containsSuffix(string, string);
int countLines(string);

int main(){

	listFiles(".");

	return 0;
}

void listFiles(string name){

	struct dirent *entry;
	DIR *dir;
	dir = opendir(name.c_str());

	while((entry = readdir(dir)) != nullptr){

		string filename = entry->d_name;

		if(filename != "." && filename != ".."){

			if(entry->d_type == 8){

				string path = name + "/" + filename;
				string displayPath = path;
				
				if(path.length() > 40)
					displayPath = "..." + path.substr(path.length() - 37);

				if(containsSuffix(filename, ".cpp") ||
					containsSuffix(filename, ".c") ||
					containsSuffix(filename, ".c++") ||
					containsSuffix(filename, ".h") ||
					containsSuffix(filename, ".hpp") ||
					containsSuffix(filename, ".h++") ||
					containsSuffix(filename, ".java")){

					printf("%-40s %i\n", displayPath.c_str(), countLines(path));
				}
			}
			else if(entry->d_type == 4){
				string nextPath = name + "/" + filename;
				listFiles(nextPath.c_str());
			}
		}
	}
}

bool containsSuffix(string name, string suffix){

	if(suffix.length() > name.length())
		return false;

	return name.substr(name.length() - suffix.length()) == suffix;
}

int countLines(string filename){

	ifstream file;
	file.open(filename.c_str());
	string line;

	int numLines = 0;
	int numWhiteLines = 0;

	while((file.rdstate() & ifstream::eofbit) == 0){

		getline(file, line);
		if(line == "")
			numWhiteLines++;
		numLines++;
	}

	file.close();

	return numLines;
}