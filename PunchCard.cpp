// PunchCard.cpp
// 
// Implementations for the PunchCard class that reads in one or more
// 12 row by 80 column punchards and encodes punch data into an 80 character 
// long encoded text using an extended binary coded decimal scheme
//
// Joshua Scheck
// 2020-10-07
//

#include <iostream>
#include <vector>
#include <string>
#include "PunchCard.h"

// Constructor for this PunchCard class
PunchCard::PunchCard()    
{  
   // initalize this PunchCard with empty hole punch data 
   for (int rowIdx = 0; rowIdx < PunchCard::ROW_LEN; rowIdx++) {
      for (int colIdx = 0; colIdx < PunchCard::COL_LEN; colIdx++) {
         PunchCard::data[rowIdx][colIdx] =  ' ';
      }
   }

   int extendedBCD[4][10] = {
      {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
      {'&', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'},
      {'-', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'},
      {'0', '/', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
   };

   // Iteratively add extended BCD schema because assigning matrix
   // in single statement does not use conventional syntax in the constructor
   for (int rowIdx = 0; rowIdx < 4; rowIdx++) {
      for (int colIdx = 0; colIdx < 10; colIdx++) {
         PunchCard::extendedBCD[rowIdx][colIdx] =  extendedBCD[rowIdx][colIdx];
      }
   }
}

// Retrieves the encoded text (via extended BCD) 
// 
// Pre: 
// - This PunchCard data must not be null
//
// Post:
// - Returns an 80 character long extended BCD encoded text
const std::string PunchCard::toString() {

   int startingColIdx;
   std::string result;

   // Skip the first column of this PunchCard when this PunchCard
   // is the last
   if (PunchCard::isLastCard()) {
      startingColIdx = 1;
      result += " ";
   } else {
      startingColIdx = 0;
   }

   for (int colIdx = startingColIdx; colIdx < PunchCard::COL_LEN; colIdx++) {
      std::vector<int> adjustedCoordinates;
      int lastVal;

      // Looks for 'X' characters in the current column and records the row 
      // in which it was found and stores the adjusted value in a vector to 
      // be later used as coordinates to access the extended BCD matrix
      for (int rowIdx = 0; rowIdx < PunchCard::ROW_LEN; rowIdx++) {
         char currItem = PunchCard::data[rowIdx][colIdx];
         if (currItem == 'X' && adjustedCoordinates.size() < 2) {
            lastVal = rowIdx;                
            if (rowIdx >= 3 && rowIdx < 12) {
               adjustedCoordinates.push_back(rowIdx - 2);
            } else {
               adjustedCoordinates.push_back(rowIdx + 1);
            }
         }
         // If two 'X' characters have been found then skip to the next 
         // column
         else if (adjustedCoordinates.size() == 2) {
            break;
         }
      }

      // Add a zero at the beginning of the vector if the punch
      // was found in rows named 1 through 9
      if (adjustedCoordinates.size() == 1 && lastVal >= 3) {
         adjustedCoordinates.insert(adjustedCoordinates.begin(), 0);
      }
        
      // If no rows in the the current column index are punched
      // then fill vector with zeros 
      while (adjustedCoordinates.size() < 2) {
         adjustedCoordinates.push_back(0);
      }

      // Coordinates to access extended BCD matrix
      int coord1 = adjustedCoordinates[0];
      int coord2 = adjustedCoordinates[1];
       
      result += PunchCard::extendedBCD[coord1][coord2];
   }
    
   // New line for each String result
   result += "\n";

   return result;
}

// Determines if the current card is the last card
// 
// Pre: 
// - This PunchCard data must be initialized to a 12 row and 80 column
//   input consisting of 'X' or ' ' characters
//
// Post:
// - Returns true if this PunchCard contains 'X' characters each row of its first
//   column, false otherwise
const bool PunchCard::isLastCard() {
   for (int rowIdx = 0; rowIdx < PunchCard::ROW_LEN; rowIdx++) {
      if (PunchCard::data[rowIdx][0] != 'X') {
         return false;
      }
   }

   // Returns true if all values in first column are 'X' characters 
   return true;
}

// Overloaded >> so that 12 row and 80 column input(s) consisting of 'X' or ' ' characters 
// are used as hole punch data 
// 
// Pre: 
// - At least one 12 row and 80 column input consisting of 'X' or ' ' characters.
// - An initialized PunchCard object to stream data into
//
// Post:
// - Returns the input stream object.
std::istream& operator>>(std::istream& input, PunchCard& punchCard) {
   std::string currLine;
   for (int rowIdx = 0; rowIdx < PunchCard::ROW_LEN; rowIdx++) {
        
      getline(input, currLine);

      // Set each item in character array to the string value obtained
      // from the current line
      for (int colIdx = 0; colIdx < PunchCard::COL_LEN; colIdx++) {
         punchCard.data[rowIdx][colIdx] = currLine[colIdx];
      }
   }

   // If not the last card then request a line from input stream
   // and do nothing with retrieved line
   if (!punchCard.isLastCard()) {
      getline(input, currLine);
   }

   return input;
}