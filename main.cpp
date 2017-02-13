/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Hristina Petkova
 * @idnumber
 * @task 0
 * @compiler GCC
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

#include "Tree.h"
#include "Vector.h"
#include "Frequency.h"
#include "Code.h"

using namespace std;

bool updateExistingNode(Vector<Tree<Frequency>>* allCharsVec, char tempChar);
void writeKeys(Vector<Code>* codedCharsVec, ofstream* archive);
void writeArchive(std::string fileContent, ofstream* archive);
void createArchive(std::string nameOfFile, ofstream* archive);

int main()
{
    std::string nameOfFile = "text";

    //create archive file
    ofstream archive("rar.bin", ios::binary);

    for(size_t i = 0; i < 3;/**number of all files*/ i++)
    {
        createArchive(nameOfFile, &archive);
    }

    archive.close();

    cout << "Archive is create" << endl;

	system("pause");
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
    Vector<Tree<Frequency>> allCharsVec;

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
        allCharsVec.push(tempTree);
    }
    //-----------------------------------------

    // sort vector
    allCharsVec.sortList();

    // create one tree with all elements
    while(allCharsVec.getVectorSize() > 1)
    {
        Tree<Frequency> leftChild;
        Tree<Frequency> rightChild;
        Tree<Frequency> newTree;

		//get last element from vector
        allCharsVec.pop(leftChild);

		//get last element from vector
        allCharsVec.pop(rightChild);

        newTree.createRootFromTrees(leftChild, rightChild);

        allCharsVec.push(newTree);
        allCharsVec.sortList();
    }
    //-----------------------------------------
    // get tree
    Tree<Frequency> finalTree;
    allCharsVec.pop(finalTree);

    cout << "coding... ";
    // contains all chars with them binary code
    Vector<Code> codedCharsVec;
	std::string s;
    finalTree.getAllElements(&codedCharsVec,s);

    writeKeys(&codedCharsVec, archive);

    // contains full text in coded variant
    std::string codedText;

    for(size_t i = 0; i < textSize; i++)
    {
        // get char one by one
        char tempChar = *(buffer + i);
        // iterator for codedCharsVec
        ListNode<Code>* itr = codedCharsVec.getIterator();

        while(itr != 0)
        {
            Code codeForCurrentChar = itr->getData();
            if(tempChar == codeForCurrentChar.getChar() )
            {
                codedText.append(codeForCurrentChar.getBits());

                itr = 0;
            }
            else
            {
                itr = itr->getNextPtr();
            }
        }
    }

    writeArchive(codedText, archive);

    delete[] buffer;
}

bool updateExistingNode(Vector<Tree<Frequency>>* allCharsVec, char tempChar)
{
    ListNode<Tree<Frequency> >* itr = allCharsVec->getIteratorVector();
    while(itr != 0)
    {
        // get pointer to data in root in every element of vector
        Frequency* currentNode = itr->getDataPointer()->getRootPtr()->getDataPointer();

        if(currentNode->getSeries() == tempChar)
        {
            uint64_t newValue = currentNode->getValue() + 1;
            currentNode->setValue(newValue);
            return true;
        }
        itr = itr->getNextPtr();
    }
    return false;
}

void writeKeys(Vector<Code>* codedCharsVec, ofstream* archive)
{
    cout << "writing code... ";
    //iterator for vector whit all object for word and them binary code
    ListNode<Code>* itr = codedCharsVec->getIterator();

    // get size of vector, it's number of all coded chars
    uint64_t numberOfAllCodedChar = codedCharsVec->getVectorSize();

    // store number in begin of the file
    // when read archive this number tell us how many objects we must to read
    archive->write((char*)&numberOfAllCodedChar, sizeof(numberOfAllCodedChar));

    while(itr != 0)
    {
        // object of coded char
        Code* codeForWrite = itr->getDataPointer();
        // char
        char charFromCode = codeForWrite->getChar();
        // binary code
        string bitsFromCode = codeForWrite->getBits();
        // length of binary code
        size_t sizeOfbits = bitsFromCode.size();

        // write char to archive
        archive->write(&charFromCode, sizeof(charFromCode ));
        // write length of binary code
        archive->write((char*)&sizeOfbits, sizeof(sizeOfbits));
        // write binary code
        archive->write(bitsFromCode.c_str(), sizeof(codeForWrite->getBits() ));

        // go to next node
        itr = itr->getNextPtr();
    }
}

void writeArchive(std::string fileContent, ofstream* archive)
{
    cout << "writing content... " << endl;
    size_t fileContentSize = fileContent.size();

    archive->write((char*)&fileContentSize, sizeof(fileContentSize));

    Vector<bitset<100>> bitVector;

    // store bits from string to bitset
    // get it by piece for 100 bits
    for(size_t i = 0; i < fileContentSize; i+=100)
    {
        std::string subString = fileContent.substr (i, i+100);
        bitset<100> tempSet (subString);
        bitVector.push(tempSet);
    }

    // write bits to file
    uint64_t bitVectorSize = bitVector.getVectorSize();
    for(size_t i = 0; i < bitVectorSize; i++)
    {
        bitset<100> temp;
        bitVector.pop(temp);
        archive->write((char*)&temp, sizeof(temp));
    }
}

