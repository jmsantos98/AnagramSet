#ifndef ANAGRAMSET_H
#define ANAGRAMSET_H
#include "LetterBag-1.h"
#include <iostream>
#include <algorithm>
class AnagramSet
{
    public:
        AnagramSet();
        string key;
        vector<string> words;
        AnagramSet * next;


        friend std::ostream & operator<< (std::ostream & out, const AnagramSet & s);   // output the AnagramSet in a format like {aet: ate, eat, eta, tea}

          // NOTE: "aet" is the key as a sorted string and "ate", "eat" ... are the contents of the words vector.



        AnagramSet(const string s,  AnagramSet * n = nullptr); // Generate the key from s, and store s in the words vector.  Also initialize next to n.



        void insert(const string & s);  // Don't insert if s is already in the words vector. Otherwise insert it in sorted order.



        void remove(const string & s); //  Remove s from the words vector, if it's there . Otherwise do nothing.



        int getSize() const;  // return the size of the words vector



        bool contains(const string & s);  // Return true if the words vector contains s and return false otherwise  .



        void clear();   // Set words back to the empty vector.



        vector<string>  getWords() const;  // Just return a copy of the words vector.


        static int hashValue(const string &  key, int tableSize);  // Generate a hash value from the given sorted string


    protected:

    private:
};

#endif // ANAGRAMSET_H
