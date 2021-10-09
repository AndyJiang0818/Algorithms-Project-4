// Xihao Jiang
// CSCI 335
// Homework 4
// 4/12/21
// Setup what to do when facing Case A, Case B, and Case C.
// As well as check each word.

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// all the characters in the lower cases
string cleanWord(string word)
{
    stringstream ss;
    for (unsigned int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            ss << word[i];
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            ss << (char)(word[i] - 'A' + 'a');
        }
    }
    return ss.str();
}

// add the missing character
void caseACorrect(string word, HashTable<string> &dictionary)
{
    for (unsigned int i = 0; i < word.length() + 1; i++)
    {
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            stringstream ss;
            if (i > 0)
            {
                ss << word.substr(0, i);
            }
            ss << ch;
            if (i < word.length() + 1)
            {
                ss << word.substr(i);
            }
            string fixWord = ss.str();
            if (dictionary.Contains(fixWord))
            {
                cout << "*** " << word << " -> " << fixWord << " *** case A" << endl;
            }
        }
    }
}

// remove the additional character
void caseBCorrect(string word, HashTable<string> &dictionary)
{
    for (unsigned int i = 0; i < word.length(); i++)
    {
        string fixWord = word.substr(0, i) + word.substr(i + 1);
        if (dictionary.Contains(fixWord))
        {
            cout << "*** " << word << " -> " << fixWord << " *** case B" << endl;
        }
    }
}

// swap adjacent characters
void caseCCorrect(string word, HashTable<string> &dictionary)
{
    for (unsigned int i = 0; i < word.length() - 1; i++)
    {
        stringstream ss;
        if (i > 0)
        {
            ss << word.substr(0, i);
        }
        ss << word[i + 1] << word[i];
        if (i < word.length() - 1)
        {
            ss << word.substr(i + 2);
        }
        string fixWord = ss.str();
        if (dictionary.Contains(fixWord))
        {
            cout << "*** " << word << " -> " << fixWord << " *** case C" << endl;
        }
    }
}

// check if the word is correct or incorrect
int testSpellingWrapper(int argument_count, char **argument_list)
{
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTable<string> dictionary;
    dictionary.MakeEmpty();
    ifstream infile(dictionary_filename);
    string word;
    while (getline(infile, word))
    {
        if (word.length() > 0)
        {
            if (word[word.length() - 1] == '\r')
            {
                word = word.substr(0, word.length() - 1);
            }
            dictionary.Insert(word);
        }
    }
    infile.close();

    ifstream documentFile(document_filename);
    while (documentFile >> word)
    {
        word = cleanWord(word);
        if (word.length() > 0)
        {
            if (dictionary.Contains(word))
            {
                cout << word << " is CORRECT" << endl;
            }
            else
            {
                cout << word << " is INCORRECT" << endl;
                caseACorrect(word, dictionary);
                caseBCorrect(word, dictionary);
                caseCCorrect(word, dictionary);
            }
        }
    }
    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
