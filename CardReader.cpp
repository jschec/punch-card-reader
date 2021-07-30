// CardReader.cpp
// 
// Demonstrates reading input streams into PunchCard object 
// to encode the punch card hole data into extended BSD encoding
//
// Joshua Scheck
// 2020-10-07
//

#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

#include "PunchCard.h"

// Test constructor of PunchCard class
void testConstructor() {
   PunchCard testCard;

   // Create blank string 80 characters long
   string blankTestStr (80, ' ');
   blankTestStr += "\n";

   // Constructor initializes with empty punch data
   // thus empty string with new line character expected
   assert(testCard.isLastCard() == false);
   assert(testCard.toString() == blankTestStr);
}

// Test isLastCard method of PunchCard class
void testIsLastCard() {
   PunchCard testCard1;
   PunchCard testCard2;
   
   // File with one punch card
   ifstream testFile1;
   // File with two punch cards
   ifstream testFile2; 
   
   testFile1.open("./tst_files/tst1.txt");
   testFile1 >> testCard1;
   assert(testCard1.isLastCard() == true);
   
   testFile2.open("./tst_files/tst2.txt");
   testFile2 >> testCard2;
   assert(testCard2.isLastCard() == false);
   testFile2 >> testCard2;
   assert(testCard2.isLastCard() == true);
}

// Test toString() method of PunchCard class
void testToString() {
   PunchCard testCard1;
   PunchCard testCard2;
   // File with punch data extracted from programming assignment
   // web page
   ifstream testFile1;
   // File with authors name in one card and card from testFile1
   // as second card
   ifstream testFile2;

   string blankStr59 (59, ' ');
   string blankStr75 (75, ' ');

   string testStr1 = " 0123456789 ABCDEFGHI";
   testStr1 += blankStr59;
   testStr1 += "\n";

   string testStr2 = " JOSH";
   testStr2 += blankStr75;
   testStr2 += "\n";
   
   testFile1.open("./tst_files/tst1.txt");
   testFile1 >> testCard1;
   assert(testCard1.toString() == testStr1);

   testFile2.open("./tst_files/tst2.txt");
   testFile2 >> testCard2;
   assert(testCard2.toString() == testStr2);
   testFile2 >> testCard2;
   assert(testCard2.toString() == testStr1);
}

int main (int argc, char * const argv[])
{
   // Unit testing
   //testConstructor();
   //testIsLastCard();
   //testToString();

   PunchCard myCard;

   while (!myCard.isLastCard()) {
      cin >> myCard;
      cout << myCard.toString();
   }
}
