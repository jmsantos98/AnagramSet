#include "AnagramSet.h"

AnagramSet::AnagramSet(const string s, AnagramSet * n)
{
    string sortedString = s;
    int length = sortedString.length();
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length - i - 1; j++) {
            if(sortedString[j] > sortedString[j+1]) {
                swap(sortedString[j], sortedString[j+1]);
            }
        }
    }
    key = sortedString;
    next = n;
}

std::ostream & operator<< (std::ostream & out, const AnagramSet & s) {
    out << "{ " << s.key << " : ";
    for(int i = 0; i < s.words.size(); i++) {
        out << s.words[i] << " ";
    }
    out << "}";
};

void AnagramSet::insert(const string &s) {
    if(!contains(s))
        words.push_back(s);
}

void AnagramSet::remove(const string &s) {
    for(int i = 0; i < words.size(); i++) {
        if(words[i] == s)
            words.erase(words.begin()+i);
    }
}

int AnagramSet::getSize() const {
    return words.size();
}

bool AnagramSet::contains(const string &s) {
    for(int i = 0; i < words.size(); i++) {
        if(words[i] == s)
            return true;
    }
    return false;
}

void AnagramSet::clear() {
    words.clear();
}

vector<string> AnagramSet::getWords() const {
    return words;
}

int AnagramSet::hashValue(const string &key, int tableSize) {
    string sortedString = key;
    int length = sortedString.length();
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            if(sortedString[j] > sortedString[j+1])
                swap(sortedString[j], sortedString[j+1]);
        }
    }
    unsigned int h = 0;
    int power = 1;
    for(int i = 0; i < sortedString.length(); i++) {
        h += (sortedString[i] - 'a') * power;
        power *= 29;
    }
    return h % tableSize;
}
