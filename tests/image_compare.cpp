#include <iostream>
#include <string>
#include "md5_compare.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file1> <file2>" << endl;
        return EXIT_FAILURE;
    }

    string filePath1 = argv[1];
    string filePath2 = argv[2];

    compareFilesMD5(filePath1, filePath2);

    return EXIT_SUCCESS;
}