//
// Created by DELL on 12/14/2022.
//

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <regex>
#include <iomanip>
using namespace std;


// breaks str1 into words and add it to mp
void add_str_to_map(string str1, map<string, int>& mp) {
    // turn str1 into lowercase
    for (auto & c : str1) {
        c = tolower(c);
    }
    // capture keywords from str1
    regex words_regex;
    words_regex = "(([\\w](-)?)+)";
    smatch match;
    while (regex_search(str1, match, words_regex)) {
        // increase the counter by 1
        mp[match[0]]++;
        str1 = match.suffix();
    }
}

// return map of <word, counter>
map<string, int> get_freq_table(const string & file_name){
    map<string, int> mp;
    fstream myFile;
    try{
        myFile.open(file_name, ios::in);
        if (!myFile) {
            throw invalid_argument("\nfile name: " + file_name + "\nNo such file exist!");
        }
    }
    catch(invalid_argument& e){
        cerr << e.what() << '\n';
        system("pause");
    }
    if (myFile){
        cout << "\nFile status: " << file_name << " opened successfully.\n";

        // read the file line by line
        // add every line to the map
        string tmp;
        while (getline(myFile, tmp)){
            // add words from tmp into map
            add_str_to_map(tmp, mp);
        }
        myFile.close();
        return mp;
    }

    return mp;
}


void print_table(const string &file_name, const map<string, int> &mp){
    cout << "\n----------------------------------------------------------------------------\n";
    cout << "file name: " << file_name << "\n\n";

    for(auto const & pair : mp) {
        cout <<  "word: " << setw(22) << pair.first << setw(10);
        cout << " | count: "<< pair.second;
        cout << '\n';
    }
    cout << "\n-----------------------------------------------------------------------------\n";
}





int main() {

#define N_TEST_CASES 3
    // test cases
    for (int i = 1; i <= N_TEST_CASES; ++i) {
        string fileName = "test"+ to_string(i) + ".txt";

        map<string, int> freq_table = get_freq_table(fileName);

        if (!freq_table.empty()){
            print_table(fileName, freq_table);
        }
    }

    system("pause");
    return 0;
}