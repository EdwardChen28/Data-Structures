/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <iostream>
#include <algorithm> /* I wonder why this is included... */
#include <fstream>
using namespace std;
using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
	ifstream words(filename);
	string word;
	if(words.is_open()){
		while(getline(words,word)){
		
		string sort1 = word;
		sort(sort1.begin(), sort1.end());
		dict[sort1].push_back(word);
	
		
	}
}
}		


/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
	
	
		for(const string& word : words){
		string sort1 = word;
		sort(sort1.begin(), sort1.end());
		dict[sort1].push_back(word);
		}
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
	string sortedWord = word;
	std::sort(sortedWord.begin(), sortedWord.end());
	auto whatever = dict.find(sortedWord);
	if(whatever==dict.end()) return vector <string>();
	return whatever->second;

}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
   std::vector< vector < string > > all;
	for(auto& key: dict){
		if(key.second.size()> 1)
			all.push_back(key.second);
	}
    return all;
}


