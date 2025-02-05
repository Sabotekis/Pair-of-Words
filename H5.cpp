/*************************
Pāvels Petrovs, pp23055
H5. Dots teksta fails. Atrast tekstā 5 viesbiežāk sastopamos blakus esošo vārdu pārus (blakus esošie ir vienā rindā esoši vārdi, kurus atdala tikai ne-burtu simboli). 
Izdrukāt vārdu pārus pēc to sastapšanas reižu skaita dilstošā secībā, pievienojot arī sastapšanas biežumu (piemēram, of the 12, and the 10, at the 10, on the 10, he would 8). 
Informācijas glabāšanai pirms izdrukas failā izmantot vārdnīcu (STL) map un/vai STL list. Par vārdu tiek uzskatīta latīņu alfabēta burtu virkne.
Programma izveidota: 2024/04/27
*******************************/

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

// Šis ir funkcijas removeNonAlpha definīcija, kas ņem vārdu kā argumentu un atgriež virkni, kurā nav ne-burtu simbolu. 
// Tā iterē caur katru rakstzīmi vārdā un pievieno to rezultāta virknei tikai tad, ja tā ir burtu rakstzīme.
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
    inputFile.open("teksta_fails.txt", ios::in);
    if (!inputFile.is_open()) {
        cout << "Nevar atvērt failu!" << endl;
        return 1;
    }

    // Šī daļa lasa vārdus no ievades faila vienu pa vienam. Katram vārdam tiek noņemti ne-burtu simboli, izmantojot removeNonAlpha funkciju. 
    // Ja vārds nav tukšs un ir iepriekšējais vārds, tas apvieno pašreizējo vārdu ar iepriekšējo vārdu, veidojot pāri, atdalot tos ar atstarpi. Pēc tam tiek palielināts šī pāra skaits wordPairs mapē.
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

    // Pāru saraksta izveide
    list<pair<string, int>> pairsList;
    for(const auto& pair : wordPairs) {
        pairsList.push_back(make_pair(pair.first, pair.second));
    }

    // Pāru sarakstu sakārtošana dilstošā secībā pēc sastapšanas reižu skaita
    pairsList.sort([](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    int count = 0;
    fstream outputFile;
    outputFile.open("rezultats.txt", ios::out);
    if (!outputFile.is_open()) {
        cout << "Nevar atvērt rezultātu failu!" << endl;
        return 1;
    }

    for(const auto& pair : pairsList) {
        if(count >= 5)
            break;
        outputFile << pair.first << " " << pair.second << endl;
        count++;
    }

    outputFile.close();
    cout << "Rezultāti saglabāti failā rezultats.txt" << endl;
    return 0;
}
