#include "header.h"

int main()
{
   Trie trie;

   trie.convert_to_trietree(); // load dictionarry

   cout << "\n\n\n---------------------------------------------------------\n";
   cout << "------------------  LOADING .....  ----------------------\n";
   cout << "---------------------------------------------------------\n";

   this_thread::sleep_for(chrono::seconds(1));

   system("cls");

   int choice, update;
   string word;
   string meaning;

   string newWord;
   vector<string> suggestions;

   system("cls");
   
   cout << " -----------------------------------------------" << endl;
   cout << " |     Welcome to FAST-NUCES E-Dictionary      |" << endl;
   cout << " -----------------------------------------------\n";

   do {
       cout << " ===============================================" << endl;
       cout << " |       E-Dictionary Available Modules        |" << endl;
       cout << " ===============================================\n";
       cout << " |" << setw(19) << "1) Add Word" << "                          |" << endl;
       cout << " |" << setw(22) << "2) Search Word" << "                       |" << endl;
       cout << " |" << setw(22) << "3) Delete Word" << "                       |" << endl;
       cout << " |" << setw(22) << "4) Update Word" << "                       |" << endl;
       cout << " |" << setw(27) << "5) Suggestions Word" << "                  |" << endl;
       cout << " |" << setw(15) << "6) Exit" << "                              |" << endl;
       cout << " ===============================================\n" << endl;
       cout << "Enter your choice: ";

       while (true)
       {
           cin >> choice;
           if (choice >= 1 && choice <= 6)
               break;
           else
           {
               cout << "Invalid choice. Please enter a valid option: ";
           }
           cin.clear();
           cin.ignore();

       }

       switch (choice)
       {
       case 1:
           system("cls");
           cout << " ===============================================" << endl;
           cout << " |               Add Word Module               |" << endl;
           cout << " ===============================================\n";
           cin.ignore();
           cout << "Enter the word to add: ";
           cin >> word;
           cout << "Enter the meaning of '" << word << "': ";
           cin >> meaning;

           if (trie.insert(word, meaning))
               trie.savaTree();

           system("pause");
           system("cls");
           break;
       case 2:
           system("cls");
           cout << " ===============================================" << endl;
           cout << " |             Search Word Module              |" << endl;
           cout << " ===============================================\n";
           cin.ignore();
           cout << "Enter the word to search: ";
           cin >> word;

           trie.search(word);
           system("pause");
           system("cls");
           break;
       case 3:

           system("cls");
           cout << " ===============================================" << endl;
           cout << " |             Delete Word Module              |" << endl;
           cout << " ===============================================\n";
           cin.ignore();
           cout << "Enter the word to delete: ";
           cin >> word;

           if (trie.deleteWord(word))
               trie.savaTree();

           system("pause");
           system("cls");
           break;
       case 4:
	   
           system("cls");
           cout << " ===============================================" << endl;
           cout << " |             Update Word Module              |" << endl;
           cout << " ===============================================\n";
           cin.ignore();
           cout << "Enter the previous word to update: ";
           cin >> word;

           system("cls");

           cout << " ===============================================" << endl;
           cout << " |           Further Update Modules            |" << endl;
           cout << " ===============================================\n";
           cout << " |" << setw(32) << "1) Update Meaning only" << "             |" << endl;
           cout << " |" << setw(29) << "2) Update Word only" << "                |" << endl;
           cout << " |" << setw(41) << "3) Update both Word and Meaning" << "    |" << endl;
           cout << " |" << setw(20) << "4) Go Back" << "                         |" << endl;
           cout << " ===============================================\n" << endl;

           cout << "Enter your choice: ";
           while (true)
           {
               cin >> update;
               if (update >= 1 && update <= 4)
                   break;
               else
               {
                   cout << "Invalid choice. Please re-enter a valid option: ";
               }
               cin.clear();
               cin.ignore();
           }
           switch (update) {

           case(1):
               cout << "Enter the new meaning: ";
               cin >> meaning;
               trie.updateMeaning(word, meaning);
               break;
           case(2):
               cout << "Enter the new word: ";
               cin >> newWord;
               trie.updateWord(word, newWord);
               break;
           case(3):
               cout << "Enter the new word: ";
               cin >> newWord;
               cout << "Enter the new meaning: ";
               cin >> meaning;
               trie.deleteWord(word);
               trie.insert(newWord, meaning);
               break;
           }

           trie.savaTree();
           system("pause");
           system("cls");
           break;
       case 5:
           system("cls");
           cout << " ===============================================" << endl;
           cout << " |            Suggetion Word Module             |" << endl;
           cout << " ===============================================\n";
           cin.ignore();
           char ch;

           cout << "Enter the word to suggest: ";
           cout << "/n";

           while (1)
           {
               if (_kbhit()) {
                   ch = _getch();

                   word += ch;
                   if (int(ch) == 13)
                       break;

                   if (int(ch) == 8) {
                       word.erase(word.size() - 2);
                   }

                   suggestions = trie.wordSuggestions(word);
                   cout << "Word Suggestions starting with '" << word << "': " << endl;

                   for (int i = 0; i < suggestions.size() && i < 10; i++)
                   {
                       cout << i + 1 << ") " << suggestions[i] << endl;
                   }
                   cout << endl;
               }
           }

           system("pause");
           system("cls");
           break;
       case 6:
           cout << "Exiting program. Thank you!" << endl;
           this_thread::sleep_for(chrono::seconds(1));
           system("cls");
           break;
       }

   } while (choice != 6);

   cout << " ===============================================" << endl;
   cout << " |  E-Dictionary has been exited successfully! |" << endl;
   cout << " ===============================================\n";

   return 0;
}