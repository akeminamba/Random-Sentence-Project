#include <fstream>
#include "WordFrequency.h"
#include "sanitize.h"
using namespace std;

WordFrequency::WordFrequency() {}
void WordFrequency::readIn(const string & filename) {
  ifstream find(filename);

  string word_find;

  while(find >> word_find) {
    //word goes in the readIn
    sanitize(word_find);
    //will take out any punctuation not needed
    char punctuation = word_find[word_find.size() - 1];

    if(punctuation == '!' || punctuation == '.' || punctuation == '?') {
      word_find = word_find.substr(0, word_find.size() -1);
    }
    if(hashtable.count(word_find) == 0) {
      hashtable[word_find] = 1;
    } else {
      hashtable.at(word_find) += 1;
    }
  }
}

//will return the number of words inside the hash table
size_t WordFrequency::numberOfWords() {
  return hashtable.size();
}

//will return the number of times a word shows up
size_t WordFrequency::wordCount(const string & word_find) {
  return hashtable[word_find];
}

//will return the most frequent word
string WordFrequency::mostFrequentWord() {
  unordered_map<string,int>::iterator it = hashtable.begin();
  string seen_most = it -> first;

  while(it!=hashtable.end()) {
    if(hashtable[seen_most] < hashtable[it -> first]) {
      seen_most = it -> first;
    }
    it++;
  }
  return seen_most;
}

size_t WordFrequency::maxBucketSize() {
  size_t max = 0;

  for(int i = 0; i < hashtable.bucket_count(); i++) {
    if(hashtable.bucket_size(i) > max) {
      max = hashtable.bucket_size(i);
    }
  }
  return max;
}
