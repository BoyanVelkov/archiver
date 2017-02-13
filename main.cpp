#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>

#include "Tree.h"
#include "Frequency.h"
#include "Code.h"

using namespace std;

bool updateExistingNode(std::vector<Tree<Frequency>>* allCharsVec, char tempChar);
void writeKeys(std::vector<Code>* codedCharsVec, ofstream* archive);
void writeArchive(std::string* fileContent, ofstream* archive);
void createArchive(std::string nameOfFile, ofstream* archive);

int main()
{
    std::string nameOfFile = "text";

    //create archive file
    ofstream archive("rar.bin", ios::binary);

    ///for(size_t i = 0; i < 1;/**number of all files*/ i++)
    ///{
        createArchive(nameOfFile, &archive);
    ///}

    archive.close();

    cout << "Archive is create" << endl;

    return 0;
}

void createArchive(std::string nameOfFile, ofstream* archive)
{
    //reading from file
    ifstream text;
    text.open(nameOfFile, ios::binary);

    if(!text.is_open())
    {
        cout << "File not found!" << endl;
    }


    cout << "\"" << nameOfFile << "\"" << " reading... ";

    // get size of text file and go back to beginning
    text.seekg(0, text.end);
    unsigned int textSize = text.tellg();
    text.seekg (0, text.beg);

    // create buffer with size of file
    char* buffer = new char [textSize];
    // copy file to buffer
    text.read(buffer, textSize);

    // don't need file anymore
    text.close();

    // vector with all chars every node is a root of own tree
    std::vector<Tree<Frequency>> allCharsVec;

    // iterate buffer and count char repetition
    for(size_t i = 0; i < textSize; i++)
    {
        // get char one by one
        char tempChar = *(buffer + i);

        // if char exist update it's number
        if(updateExistingNode(&allCharsVec, tempChar))
        {
            // and continue to next char
            continue;
        }
        // if find new char add it to vector
        Tree<Frequency> tempTree;
        tempTree.insertNode(Frequency(1, tempChar));
        allCharsVec.push_back(tempTree);
    }
    //-----------------------------------------

    // sort vector
    std::sort(allCharsVec.begin(), allCharsVec.end(), [](const Tree<Frequency>& lhs, const Tree<Frequency>& rhs)
              {
                  return lhs > rhs;
              });

    /// print for test
/**    for(auto const& node : allCharsVec)
    {
        cout << "node = " << node << endl;
    }
*/
    // create one tree with all elements
    while(allCharsVec.size() > 1)
    {
        Tree<Frequency> leftChild;
        Tree<Frequency> rightChild;
        Tree<Frequency> newTree;

		//get last element from vector
        leftChild = allCharsVec.back();
        allCharsVec.pop_back();

		//get last element from vector
        rightChild = allCharsVec.back();
        allCharsVec.pop_back();

        newTree.createRootFromTrees(leftChild, rightChild);

        allCharsVec.push_back(newTree);

        std::sort(allCharsVec.begin(), allCharsVec.end(), [](const Tree<Frequency>& lhs, const Tree<Frequency>& rhs)
              {
                  return lhs > rhs;
              });

    }
    //-----------------------------------------
    // get tree
    Tree<Frequency> finalTree;
    finalTree = allCharsVec.back();
    allCharsVec.pop_back();

    cout << "coding... ";
    // contains all chars with them binary code
    std::vector<Code> codedCharsVec;
	std::string s;
    finalTree.getAllElements(&codedCharsVec,s);

    writeKeys(&codedCharsVec, archive);

    // contains full text in coded variant
    std::string codedText = "";

    for(size_t i = 0; i < textSize; i++)
    {
        // get char one by one
        char tempChar = *(buffer + i);

        for (auto const& codeForCurrentChar : codedCharsVec)
        {
            if(tempChar == codeForCurrentChar.getChar() )
            {
                codedText.append(codeForCurrentChar.getBits());
                break;
            }
        }
    }

    writeArchive(&codedText, archive);

    delete[] buffer;
}

bool updateExistingNode(std::vector<Tree<Frequency>>* allCharsVec, char tempChar)
{
    for(auto const& vectorElement : *allCharsVec)
    {
        Frequency* currentNode = vectorElement.getRootPtr()->getDataPointer();

        if(currentNode->getSeries() == tempChar)
        {
            uint64_t newValue = currentNode->getValue() + 1;
            currentNode->setValue(newValue);
            return true;
        }
    }

    return false;
}

void writeKeys(std::vector<Code>* codedCharsVec, ofstream* archive)
{
    cout << "writing code... ";

    // get size of vector, it's number of all coded chars
    uint64_t numberOfAllCodedChar = codedCharsVec->size();

    // store number in begin of the file
    // when read archive this number tell us how many objects we must to read
    archive->write((char*)&numberOfAllCodedChar, sizeof(numberOfAllCodedChar));

    for(auto const& codeForWrite : *codedCharsVec)
    {
        // char
        char charFromCode = codeForWrite.getChar();
        // binary code
        string bitsFromCode = codeForWrite.getBits();
        // length of binary code
        size_t sizeOfbits = bitsFromCode.size();

        // write char to archive
        archive->write(&charFromCode, sizeof(charFromCode ));
        // write length of binary code
        archive->write((char*)&sizeOfbits, sizeof(sizeOfbits));
        // write binary code
        archive->write(bitsFromCode.c_str(), sizeof(codeForWrite.getBits() ));
    }
}

void writeArchive(std::string* fileContent, ofstream* archive)
{
    cout << "writing content... " << endl;
    size_t fileContentSize = fileContent->size();

    // write size of all file
    archive->write((char*)&fileContentSize, sizeof(fileContentSize));

    std::vector<bitset<100>> bitVector;

    // store bits from string to bitset
    // get it by piece for 100 bits
    for(size_t i = 0; i < fileContentSize; i+=100)
    {
        std::string subString = fileContent->substr (i, i+100);
        bitset<100> tempSet (subString);
        bitVector.push_back(tempSet);
    }

    // write bits to file
    uint64_t bitVectorSize = bitVector.size();
    for(size_t i = 0; i < bitVectorSize; i++)
    {
        bitset<100> temp;

        temp = bitVector.back();
        bitVector.pop_back();

        archive->write((char*)&temp, sizeof(temp));
    }
}

