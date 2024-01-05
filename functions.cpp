#include "header.h"

TrieNode::TrieNode()
{
   isEndOfWord = false;
   for (int i = 0; i < 26; i++)
   {
       children[i] = NULL;
   }
}

int TrieNode::count = 0;

void Trie::collectWords(TrieNode* node, const string& prefix, vector<string>& suggestions)
{
   if (node == NULL)
   {
       return;
   }

   if (node->isEndOfWord)
   {
       suggestions.push_back(prefix);
   }

   for (int i = 0; i < 26; i++)
   {
       char ch = i + 'a';
       captialToSmall(ch);
       TrieNode* child = node->children[i];
       collectWords(child, prefix + ch, suggestions);
   }
}

void Trie::collectWordsSave(TrieNode* node, const string& prefix, vector<string>& suggestions)
{

   if (node == NULL)
   {
       return;
   }

   if (node->isEndOfWord)
   {

       countSave++;

       out << prefix << " " << node->meaning;
       if (TrieNode::count == countSave)
       {

       }
       else
       {
           out << endl;
       }
   }

   for (int i = 0; i < 26; i++)
   {
       char ch = i + 'a';
       captialToSmall(ch);
       TrieNode* child = node->children[i];
       collectWordsSave(child, prefix + ch, suggestions);
   }
}

Trie::Trie()
{
   root = new TrieNode();
   countSave = 0;
   countRepeted = 0;
}

void Trie::captialToSmall(char& ch)
{
   if (ch >= 'A' && ch <= 'Z')
   {
       ch = ch + 32;
   }
}

bool Trie::insert(const string& word, string Meaning)
{
   TrieNode* node = root;
   for (int i = 0; i < word.length(); i++)
   {
       char ch = word[i]; // move up
       // adding line
       captialToSmall(ch);
       if (ch == ' ' || (ch < 'a' || ch > 'z'))
       {
           cout << "This is an invalid word!" << endl;
           return false;
       }
       // till here
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           node->children[index] = new TrieNode();
       }
       node = node->children[index];
   }

   if (node->isEndOfWord == true)
   {
       countRepeted++;
       cout << countRepeted << endl;
       return false;
   }
   else
   {
       node->isEndOfWord = true;
       node->meaning = Meaning;
       node->count++;
       return true;
   }
}

bool Trie::search(const string& word)
{
   TrieNode* node = root;
   for (int i = 0; i < word.length(); i++)
   {
       char ch = word[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return false;
       }
       node = node->children[index];
   }
   if (node != NULL && node->isEndOfWord)
   {
       cout << "Word Found!" << endl;
       cout << "Word: " << word << endl;
       cout << "Meaning: " << node->meaning << endl;
   }
   else
   {
       cout << "Word Not Found!" << endl;
   }

   return node != NULL && node->isEndOfWord;
}

string Trie::getMeaning(const string& word)
{
   TrieNode* node = root;
   for (int i = 0; i < word.length(); i++)
   {
       char ch = word[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return "";
       }
       node = node->children[index];
   }
   if (node != NULL && node->isEndOfWord)
   {
       return node->meaning;
   }

   return "";
}

bool Trie::updateMeaning(const string& word, string Meaning)
{
   TrieNode* node = root;
   for (int i = 0; i < word.length(); i++)
   {
       char ch = word[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return false;
       }
       node = node->children[index];
   }
   if (node != NULL && node->isEndOfWord)
   {
       cout << "Word found!" << endl;
       cout << "Word: " << word << endl;
       cout << "Old Meaning: " << node->meaning << endl;
       node->meaning = Meaning;
       cout << "\nUpdated Meaning: " << node->meaning << endl;
       return true;
   }
   else
   {
       cout << "Word Not Found!" << endl;
       return false;
   }
}

bool Trie::startsWith(const string& prefix)
{
   TrieNode* node = root;
   for (int i = 0; i < prefix.length(); i++)
   {
       char ch = prefix[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return false;
       }
       node = node->children[index];
   }
   return node != NULL;
}

bool Trie::deleteWord(const string& word)
{
   if (search(word))
   {
       TrieNode* node = root;
       for (int i = 0; i < word.length(); i++)
       {
           char ch = word[i];
           captialToSmall(ch);
           int index = ch - 'a';
           node = node->children[index];
       }
       node->isEndOfWord = false;
       node->count--;
       return true;
   }
   return false;
}

void Trie::updateWord(const string& oldWord, const string& newWord)
{
   if (search(oldWord))
   {
       string mean = getMeaning(oldWord);
       deleteWord(oldWord);
       insert(newWord, mean);
       cout << "Word Updated!" << endl;
   }
}

vector<string> Trie::wordSuggestions(const string& prefix)
{
   vector<string> suggestions;
   TrieNode* node = root;
   for (int i = 0; i < prefix.length(); i++)
   {
       char ch = prefix[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return suggestions;
       }
       node = node->children[index];
   }
   collectWords(node, prefix, suggestions);
   return suggestions;
}

vector<string> Trie::wordSuggestionsSave(const string& prefix)
{
   vector<string> suggestions;
   TrieNode* node = root;
   for (int i = 0; i < prefix.length(); i++)
   {
       char ch = prefix[i];
       captialToSmall(ch);
       int index = ch - 'a';
       if (node->children[index] == NULL)
       {
           return suggestions;
       }
       node = node->children[index];
   }

   collectWordsSave(node, prefix, suggestions);
   return suggestions;
}

void Trie::convert_to_trietree()
{
   ifstream in;
   string str;//get word from file
   string meaning;
   in.open("Dictionary.txt");

   while (!in.eof())
   {
       TrieNode* curr = root;
       in >> str;
       getline(in, meaning);
       insert(str, meaning);
   }
   in.close();
}

void Trie::savaTree()
{
   out.open("Dictionary.txt");

   cout << "Updating the data. Please wait..." << endl;

   string value = "";
   vector<string>word = wordSuggestionsSave(value);

   out.close();
   countSave = 0;
}