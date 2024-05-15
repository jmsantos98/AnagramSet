#include "Dictionary.h"

Dictionary::Dictionary()
{
    numWords = 0;
}

Dictionary::Dictionary(std::string words[], int wordCount) {
    for(int i = 0; i < wordCount; i++) {
        insertWord(words[i]);
    }
}

Dictionary::Dictionary(std::string fileName) {
    numWords = 0;
    string inputLine;
    ifstream infile(fileName);
    while(getline(infile, inputLine)) {
        insertWord(inputLine);
    }
}

Dictionary::~Dictionary()
{
    clear();
}

bool Dictionary::insertWord(std::string w) {
    int bucket = AnagramSet::hashValue(w, TABLESIZE);
    AnagramSet * current = hashTable[bucket];
    AnagramSet * temp = new AnagramSet(w);
    string sortedW = temp->key;
    delete temp;
    // if(!contains(w)) {
        // Loop through each node in the bucket until a key is found or nullptr is reached. If key is found, calls AnagramSet::insert, updates numWords and returns true otherwise proceeds through the function
        while(current) {
            if(current->key == sortedW) {
                current->insert(w);
                numWords++;
                return true;
            }
            current = current->next;
        }
    // If the key is not found in each bucket, create a new AnagramSet object and set it to the front of the linked list. Updates numWords and returns true
        AnagramSet * newSet = new AnagramSet(w, hashTable[bucket]);
        hashTable[bucket] = newSet;
        newSet->insert(w);
        numWords++;
        return true;
    // }
    // return false if w is in the dictionary
    return false;
}



int Dictionary::getNumWords() const {
    return numWords;
}

void Dictionary::clear() {
    AnagramSet * temp = nullptr;
    for(int i = 0; i < TABLESIZE; i++) {
        while(hashTable[i] != nullptr) {
            temp = hashTable[i];
            delete hashTable[i];
            hashTable[i] = temp->next;
            numWords--;
        }
    }
}

bool Dictionary::removeWord(std::string w) {
    int bucket = AnagramSet::hashValue(w, TABLESIZE);
    AnagramSet * current = hashTable[bucket];
    AnagramSet * previous = nullptr;
    while(current) {
        if(current->contains(w)) {
            current->remove(w);
            if(current->words.empty()) {
                if(previous) {
                    previous->next = current->next;
                }
                else {
                    hashTable[bucket] = current->next;
                }
                delete current;
            }
            numWords--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

bool Dictionary::contains(std::string w) const {
    int bucket = AnagramSet::hashValue(w, TABLESIZE);
    AnagramSet * current = hashTable[bucket];

    while(current != nullptr) {
        if(current->contains(w))
            return true;
        current = current->next;
    }

    return false;
}

vector<std::string> Dictionary::getWords(std::string w) const {
    int bucket = AnagramSet::hashValue(w, TABLESIZE);
    AnagramSet * current = hashTable[bucket];
    AnagramSet * temp = new AnagramSet(w);
    string sortedW = temp->key;
    temp->insert("hey");
    delete temp;
    while (current) {
        if(current->key == sortedW) {
            return current->words;
        }
        current = current->next;
    }
    return {};
}

int Dictionary::getNumAnagrams(const std::string &w) const {
    int bucket = AnagramSet::hashValue(w, TABLESIZE);
    AnagramSet * current = hashTable[bucket];
    while(current) {
        if(current->contains(w))
            return current->getSize();
        current = current->next;
    }
    return 0;
}

void Dictionary::printDictionary(int limit, bool verbose , ostream& out) const {
    int nonEmptyCount = 0, longest = 0, maxLength = 0;
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashTable[i] != nullptr) {
            nonEmptyCount++;
            AnagramSet* a = hashTable[i];
            int currentLength = 0;
            if (nonEmptyCount <= limit) {
                out << i << "...\t";
                while (a != nullptr) {
                    currentLength++;
                    if (verbose) out << *a << "  ";
                    else out << a->key << "   "; // or just a->key if you used a sorted string
                    a = a->next;
                }
                out << endl;

            }
            else while (a != nullptr) {
                currentLength++;
                a = a->next;
            }
            if (currentLength > longest) longest = currentLength;
        }
    }
    if (verbose) {
        out << endl;
        out << "Number of words = " << numWords << "\ttableSize = " << TABLESIZE << endl;
        out << "Total number of nonEmpty buckets = " << nonEmptyCount << endl;
        out << "Percent empty = " << 100.0 * (TABLESIZE - nonEmptyCount)  / TABLESIZE << endl;
        out << "Longest chain = " << longest << endl << endl;
    }
}
