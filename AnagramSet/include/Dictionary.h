#ifndef DICTIONARY_H
#define DICTIONARY_H


#include "AnagramSet.h"
#include "fstream"
#include <string>
#include <algorithm>

class Dictionary {
public:
    static const int TABLESIZE = 200001;
private:

    AnagramSet* hashTable[TABLESIZE] = { nullptr };
    int numWords;


public:

    // default constructor: creates an empty dictionary
    Dictionary();

    // default constructor: creates an empty dictionary
    Dictionary(std::string words[], int wordCount);

    // constructor to get words from a file
    Dictionary(std::string fileName);

    // Copy constructor. Initialize current dictionary.
    // Initialize numWords to 0, then add words from d to
    // the current Dictionary
    Dictionary(const Dictionary& d);

    // Destructor; just call clear
    ~Dictionary();

    // Return numWords.
    int getNumWords() const;

    // Empty the Dictionary, delete all nodes.
    void clear();


    // Insert w into the Dictionary if not already there and return true.
    // If w is already there, change nothing and return false.
    bool insertWord(std::string w);

    // Remove w from the Dictionary if there and return true.
    // If not there, change nothing and return false.
    // Also remove the AnagramSetif w sa
    bool removeWord(std::string w);

    // Return true if w is in the Dictionary and false otherwise.
    bool contains(std::string w) const;

    // Return all words that contain same letters as w (anagrams)
    vector<std::string> getWords(std::string w)  const;

    // Return number of words with same letters as w (number of anagrams)
    int getNumAnagrams(const std::string& w)  const;

    // Print the contents of the Dictionary, up to limit nonempty buckets.
    void printDictionary(int limit = TABLESIZE, bool verbose = true, ostream& out = cout) const;


};


#endif // DICTIONARY_H
