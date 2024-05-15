
#include "LetterBag-1.h"

LetterBag::LetterBag() {
	clear();
}


LetterBag::LetterBag(const vector<char> & v) {
	clear();
	for (unsigned int i = 0; i < v.size(); i++)
		if (inRange(v[i])) 	 {
			counts[v[i] - 'a']++;
			size++;
		}
}

LetterBag::LetterBag(const string & s) {
    clear();
    for (unsigned int i = 0; i < s.size(); i++)
        if (inRange(s[i])) {
            counts[s[i] - 'a']++;
            size++;
        }
}



int LetterBag::getCurrentSize() const {
	return size;
}

bool LetterBag::isEmpty() const {
	return size == 0;
}

LetterBag & LetterBag::add(char c) {
	if (inRange(c))		 {
		counts[c - 'a']++;
		size++;
	}
	return *this;
}
LetterBag & LetterBag::operator+=(char c) {
    add(c);
    return *this;
}
LetterBag  LetterBag::operator+(char c) const {
    LetterBag temp = *this;
    temp.add(c);
    return temp;
}

// add the contents of other  the current object and return the current object.
LetterBag & LetterBag::operator+=(const LetterBag & other) {
    for (int i = 0; i < 26; i++)
        counts[i] += other.counts[i];
    size += other.size;
    return *this;

}

// add the contents of other to a copy of the current object and return the copy.
LetterBag LetterBag::operator+(const LetterBag & other) const {
    LetterBag temp = *this;
    temp += other;
    return temp;
}



LetterBag & LetterBag::remove(char c) {
	if (inRange(c) && counts[c-'a'] > 0)  {
		counts[c - 'a']--;
		size--;
	}
	return *this;
}

LetterBag & LetterBag::operator-=(char c) {
    remove(c);
    return *this;
}
LetterBag  LetterBag::operator-(char c) const {
    LetterBag temp = *this;
    temp.remove(c);
    return temp;
}

void LetterBag::clear() {
	size = 0;
	for (int i = 0; i < 26; i++)
		counts[i] = 0;
}

int LetterBag::getFrequency(char c) const {
	return inRange(c) ? counts[c-'a'] : 0;
}

vector<char> LetterBag::toVector() const {
	vector<char> result(size);

	for (int i = 0, index = 0; i < 26; i++)
		for (int j = 0; j < counts[i]; j++)
			result[index++] = (char) ('a' + i);

	return result;
}

string LetterBag::toString() const {
    string s;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < counts[i]; j++)
            s += (char)('a' + i);
    return s;
}

bool LetterBag::isSubbag(const LetterBag & other) const {
	for (int i = 0; i < 26; i++)
		if (other.counts[i] > this->counts[i]) return false;
	return true;
}
// return true if the current object is a proper subbag of other.
bool LetterBag::operator<(const LetterBag & other) const {
    return isSubbag(other);
}
// return true if the current object is a subbag of other.
bool LetterBag::operator<=(const LetterBag & other) const {
    return !(other < *this);
}

// return true if the other is a proper subbag of the current object.
bool LetterBag::operator>(const LetterBag & other) const {
    return other < *this;
}

// return true if the other is a subbag of the current object.
bool LetterBag::operator>=(const LetterBag & other) const {
    return other <= *this;
}

bool LetterBag::operator==(const LetterBag & other) const {
    if (this->size != other.size) return false;
    for (int i = 0; i < 26; i++)
        if (this->counts[i] != other.counts[i]) return false;
    return true;
}

bool LetterBag::operator!=(const LetterBag & other) const {
    return !this->operator==(other);
}
bool LetterBag::inRange(char c) {return c <= 'z' && c >= 'a';}
