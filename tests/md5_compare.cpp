

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring> 
#include <openssl/md5.h>

using namespace std;

void print_MD5(unsigned char *md, long size = MD5_DIGEST_LENGTH){
    for (int i = 0; i < size; i++){
        cout << hex << setw(2) << setfill('0') << (int)md[i];
    }
    cout << endl;
}

void compareFilesMD5(const string &filePath1, const string &filePath2) {
    // Calculer le MD5 du premier fichier
    ifstream file1(filePath1, ios::in | ios::binary | ios::ate);
    if (!file1.is_open()) {
        cerr << "Error: Cannot open file: " << filePath1 << endl;
        exit(EXIT_FAILURE);
    }
    long fileSize1 = file1.tellg();
    char *memBlock1 = new char[fileSize1];
    file1.seekg(0, ios::beg);
    file1.read(memBlock1, fileSize1);
    file1.close();

    unsigned char result1[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)memBlock1, fileSize1, result1);
    delete[] memBlock1;

    // Calculer le MD5 du deuxième fichier
    ifstream file2(filePath2, ios::in | ios::binary | ios::ate);
    if (!file2.is_open()) {
        cerr << "Error: Cannot open file: " << filePath2 << endl;
        exit(EXIT_FAILURE);
    }
    long fileSize2 = file2.tellg();
    char *memBlock2 = new char[fileSize2];
    file2.seekg(0, ios::beg);
    file2.read(memBlock2, fileSize2);
    file2.close();

    unsigned char result2[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)memBlock2, fileSize2, result2);
    delete[] memBlock2;

    // Comparer les deux résultats MD5
    if (memcmp(result1, result2, MD5_DIGEST_LENGTH) != 0) {
        //Print the MD5 hash of the two files
        cout << "MD5 of file '" << filePath1 << "' : ";
        print_MD5(result1);
        cout << "MD5 of file '" << filePath2 << "' : ";
        print_MD5(result2);
        cerr << "Error: Files " << filePath1 << " and " << filePath2 << " are not identical." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Files " << filePath1 << " and " << filePath2 << " are identical." << endl;
    }
}