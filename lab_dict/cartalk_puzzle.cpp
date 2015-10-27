/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"
#include <iostream>
using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
  	vector< StringTriple > v;
  	
  	ifstream words(word_list_fname);
  	std::string word;
  	if(words.is_open()){
  		while(getline(words,word)){
  			if(word.length() == 5){
  			//cout<< "original: " << word<< endl;
			std::string first = word.substr(1,4);
			//cout<< "first: " <<first<< endl;
			std::string second = first.substr(1,3);
			second = word.at(0)+second;
			//cout<<"second: "<< second<< endl;
			//std::second.append(word_list_frame.str(2,3);
			if(d.homophones(word, first) && d.homophones(word, second)){
				//auto turple3 = std:: make_tuple(word, first, second);
				v.push_back(std:: make_tuple(word, first, second)); 
			}
			}
		}
	}	/* Your code goes here! */
    return v;
}


