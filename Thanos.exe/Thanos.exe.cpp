#include "stdafx.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <random>
#include <stdio.h>


namespace fs = std::experimental::filesystem;


void processFile(const fs::v1::directory_entry& entry) {
	if (rand() % 2) {
		if (remove(entry)) {
			std::cout << "Unluck file -->  " << entry << std::endl;
		}
	}
}


void processDirectory(const fs::path& path, int level) {
	if (fs::exists(path) && fs::is_directory(path)) {
		for (const auto& entry : fs::directory_iterator(path)) {
			if (fs::is_directory(entry.status())) {
				processDirectory(entry, level + 1);
			} else if (fs::is_regular_file(entry.status())) {
				processFile(entry);
			}
		}
	}
}


int main(int argc, char* argv[]) {

	srand(time(0));

	std::cout << "\n WARNING \n\n" <<
		"This program will delete multiple files. " << "\n" <<
		"If you do not know what you are doing, close this window. " << "\n" <<
		"I (the dev) am in no way responsable for the damage this can do. " << "\n" <<
		"If you know what you are about to due (and probably running this in a virtual enviroment), type 'YES' to agree with the terms and continue. " << "\n" <<
		"\n\n$    ";

	std::string confirmInput;
	std::cin >> confirmInput;

	if (confirmInput == "YES") {
		
		std::cout << "Type a folder path ex.: C:\\Users\\User\\Desktop\\this \n\n\n\n$    ";

		std::string pathInput;
		std::cin >> pathInput;

		std::replace(pathInput.begin(), pathInput.end(), '/', '\\');

		if (pathInput.back() != '\\') {
			pathInput.append("\\");
		}

		processDirectory(pathInput, 0);

		std::cout << "Done." << std::endl;
		std::cin >> pathInput;  // just to not close

	} else {
		std::cout << "The program will exit." << std::endl;
	}

	return 0;
}
