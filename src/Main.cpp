#include <stdio.h>
#include <dirent.h>
#include <string>

using std::string;

void listFiles(const char*, string);

int main(){

	// struct dirent *entry;
	// DIR *dir;
	// dir = opendir(".");

	// while((entry = readdir(dir)) != nullptr)
	// 	printf("%s %i %i\n", entry->d_name, entry->d_type, entry->d_reclen);

	listFiles(".", "");

	return 0;
}

void listFiles(const char* name, string indentation){

	struct dirent *entry;
	DIR *dir;
	dir = opendir(name);

	while((entry = readdir(dir)) != nullptr){

		string filename = entry->d_name;

		if(filename != "." && filename != ".."){

			printf("%s%s\n", indentation.c_str(), filename.c_str());
			if(entry->d_type == 4){
				string nextPath = string(name) + "/" + filename;
				listFiles(nextPath.c_str(), indentation + "  ");
			}
		}
	}
}