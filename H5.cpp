#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

string removeNonAlpha(const string& word) {
    string result;
    for(char c : word) {
        if(isalpha(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    fstream inputFile;
    inputFile.open("text.txt", ios::in);
    if (!inputFile.is_open()) {
        cout << "Can`t open the file!" << endl;
        return 1;
    }

    map<string, int> wordPairs; 
    string prevWord, word;
    while(inputFile >> word) {
        word = removeNonAlpha(word);
        if(!word.empty()) {
            if(!prevWord.empty()) {
                string pair = prevWord + " " + word;
                wordPairs[pair]++;
            }
            prevWord = word;
        }
    }

    inputFile.close();

    list<pair<string, int>> pairsList;
    for(const auto& pair : wordPairs) {
        pairsList.push_back(make_pair(pair.first, pair.second));
    }

    pairsList.sort([](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    int count = 0;
    fstream outputFile;
    outputFile.open("answer.txt", ios::out);
    if (!outputFile.is_open()) {
        cout << "Can`t open Answer!" << endl;
        return 1;
    }

    for(const auto& pair : pairsList) {
        if(count >= 5)
            break;
        outputFile << pair.first << " " << pair.second << endl;
        count++;
    }

    outputFile.close();
    cout << "Answers are saved in answers.txt" << endl;
    return 0;
}
