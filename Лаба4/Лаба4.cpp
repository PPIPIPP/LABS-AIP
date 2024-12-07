#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <locale>
#include <iomanip>

using namespace std;

class FileProcessor {
private:
    string inputFileName;
    string outputFileName;
    string content;

    string removeSpaces(const string& str) {
        string result;
        copy_if(str.begin(), str.end(), back_inserter(result), [](char c) { return !isspace(c); });
        return result;
    }

    string truncateFloats(const string& str) {
        istringstream stream(str);
        ostringstream result;
        string word;

        while (stream >> word) {
            size_t pos = word.find('.');
            if (pos != string::npos && pos + 1 < word.size() && isdigit(word[pos + 1])) {
                try {
                    float num = stof(word);
                    result << fixed << setprecision(2) << num;
                }
                catch (...) {
                    result << word;
                }
            }
            else {
                result << word;
            }
            result << " ";
        }

        string res = result.str();
        if (!res.empty() && res.back() == ' ') {
            res.pop_back();
        }
        return res;
    }

    string toUpperCase(const string& str) {
        string result;
        transform(str.begin(), str.end(), back_inserter(result), [](unsigned char c) { return toupper(c); });
        return result;
    }

public:
    FileProcessor(const string& inputFile, const string& outputFile)
        : inputFileName(inputFile), outputFileName(outputFile) {
        ifstream inputFileStream(inputFileName);
        if (inputFileStream.is_open()) {
            string line;
            while (getline(inputFileStream, line)) {
                content += line;
            }
            inputFileStream.close();
        }
        else {
            cerr << "Ошибка при открытии входного файла: " << inputFileName << endl;
        }
    }

    ~FileProcessor() {
        content = removeSpaces(content);
        content = truncateFloats(content);
        content = toUpperCase(content);

        ofstream outputFileStream(outputFileName);
        if (outputFileStream.is_open()) {
            outputFileStream << content;
            outputFileStream.close();
        }
        else {
            cerr << "Ошибка при открытии выходного файла: " << outputFileName << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    string inputFile, outputFile;
    cout << "Введите путь к входному файлу: ";
    cin >> inputFile;
    cout << "Введите путь к выходному файлу: ";
    cin >> outputFile;

    FileProcessor processor(inputFile, outputFile);
    return 0;
}
