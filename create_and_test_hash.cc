// Xihao Jiang
// CSCI 335
// Homework 4
// 4/12/21
// Setup number of items, size of hash table, load factor, average number of collisions, and total number of collisions.
// Give the correct equation for load factor and average number of collisions.

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include "linear_probing.h"
#include "double_hashing.h"
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
    cout << "TestFunctionForHashTables..." << endl;
    cout << "Words filename: " << words_filename << endl;
    cout << "Query filename: " << query_filename << endl;
    hash_table.MakeEmpty();
    //..Insert your own code
    ifstream infile(words_filename);
    string word;
    while (getline(infile, word))
    {
        if (word.length() > 0)
        {
            if (word[word.length() - 1] == '\r')
            {
                word = word.substr(0, word.length() - 1);
            }
            hash_table.Insert(word);
        }
    }
    infile.close();

    // Setup number of items, size of hash table, load factor, average number of collisions, and total number of collisions.
    int numberOfItem = hash_table.getNumberOfElement();
    int sizeOfHashTable = hash_table.getSizeOfTable();
    float loadOfFactor = (float)numberOfItem / sizeOfHashTable;
    int collisions = hash_table.getNumberOfCollisions();
    float averageCollisions = (float)collisions / numberOfItem;

    cout << "Number of items: " << numberOfItem << endl;
    cout << "Size of hash table: " << sizeOfHashTable << endl;
    cout << "Load factor: " << loadOfFactor << endl;
    cout << "Average number of collisions: " << averageCollisions << endl;
    cout << "Total number of collisions: " << collisions << endl;
    cout << endl;

    ifstream queryfile(query_filename);
    while (getline(queryfile, word))
    {
        if (word.length() > 0)
        {
            bool found = hash_table.Contains(word);
            int probe = hash_table.getProbe();
            if (found)
            {
                cout << word << " Found " << probe << endl;
            }
            else
            {
                cout << word << " Not_Found " << probe << endl;
            }
        }
    }
    queryfile.close();
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 0;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        // cout << "Linear:" << endl;
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "quadratic")
    {
        // cout << "Quadratic:" << endl;
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "double")
    {
        // cout << "Double:" << endl;
        // cout << "r_value: " << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
    }
    else
    {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED
