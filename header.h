#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;

class TrieNode
{
public:
   bool isEndOfWord;
   string meaning;
   TrieNode* children[26];
   static int count;

   TrieNode();
};

class Trie
{
private:
   TrieNode* root;
   ofstream out;
   int countSave;

   void collectWords(TrieNode* node, const string& prefix, vector<string>& suggestions);
   void collectWordsSave(TrieNode* node, const string& prefix, vector<string>& suggestions);
   int countRepeted;

public:
   Trie();
   void captialToSmall(char& ch);
   bool insert(const string& word, string Meaning);
   bool search(const string& word);
   string getMeaning(const string& word);
   bool updateMeaning(const string& word, string Meaning);
   bool startsWith(const string& prefix);
   bool deleteWord(const string& word);
   void updateWord(const string& oldWord, const string& newWord);
   vector<string> wordSuggestions(const string& prefix);
   vector<string> wordSuggestionsSave(const string& prefix);
   void convert_to_trietree();
   void savaTree();
};