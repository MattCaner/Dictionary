#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#ifndef _DICTIONARY_H
#define _DICTIONARY_H


using namespace std;

class Dictionary{
public:
    Dictionary(int declaredSize); //constructor
    int AddElement(const string& key, const string& content);   //adds element to the Dictionary. If addition was successful, return element index. In case of an error (dictionary overload) returns -1.
    const string* FindElement(const string& key);   //returns pointer to element with key. In case of failure return NULLPTR.
    const string* operator[](const string& key);    //works exactly as FindElement, but is shorter.
    int ElementIndex(const string& key);
    int RemoveElement(const string& key);       //removes element at key. In case of success, return index. In case of failure, returns -1.

    int GetMaxSize() const {return limitSize_;}    //readonly limitSize
    int GetRealSize() const;        //returns amount of filled elements (free positions = GetMaxSize - GetRealSize)

    friend ostream& operator<<(ostream& os, const Dictionary& dict);    //befriended ostream enables printing dictionary to console with std::cout
private:
    enum status{EMPTYF, FILLEDF, REMOVEDF};
    int limitSize_;     //current maximum size of dictionary
    vector<string> keyTable_;   //table of string keys
    vector<string> contentTable_;   //table of string contents
    vector<status> statusTable_;    //table of statuses

    int Hasher(const string& s, int limit); //hashing function, returns hash of string s
    int Resolver(int d_hash);   //linear resolver for collisions
};

#endif // _DICTIONARY_H
