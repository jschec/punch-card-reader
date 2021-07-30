// PunchCard.h
// 
// Declarations for the PunchCard class that reads in one or more
// 12 row by 80 column punchards and encodes punch data into an 80 character 
// long encoded text using an extended binary coded decimal scheme
//
// Joshua Scheck
// 2020-10-07
//

#pragma once
#include <iostream>
#include <string>

class PunchCard {
   // overloaded >> so that 12 row and 80 column input(s) consisting of 'X' or ' ' characters 
   // are used as hole punch data 
   // 
   // Pre: 
   // - At least one 12 row and 80 column input consisting of 'X' or ' ' characters.
   // - An initialized PunchCard object to stream data into
   //
   // Post:
   // - Returns the input stream object.
   friend std::istream& operator>>(std::istream& input, PunchCard& punchCard);

   public:
      // Constructor for PunchCard class 
      PunchCard();

      // Determines if the current card is the last card
      // 
      // Pre: 
      // - This PunchCard data must be initialized to a 12 row and 80 column
      //   input consisting of 'X' or ' ' characters
      //
      // Post:
      // - Returns true if this PunchCard contains 'X' characters each row of its first
      //   column, false otherwise
      const bool isLastCard();
        
      // Retrieves the encoded text (via extended BCD) 
      // 
      // Pre: 
      // - This PunchCard data must not be null
      //
      // Post:
      // - Returns an 80 character long extended BCD encoded text
      const std::string toString();
        
   private:
      // Number of columns in PunchCards
      static int const COL_LEN = 80;
        
      // Number of rows in PunchCards
      static int const ROW_LEN = 12;

      // Punched holes in this PunchCard
      char data[ROW_LEN][COL_LEN];
        
      // Extended Binary Coded Decimal scheme for character encoding
      char extendedBCD[4][10];
};

// Declaration of >> operator for overloading to input stream hole punch data
// into PunchCard object
// 
// Pre: 
// - At least one 12 row and 80 column input consisting of 'X' or ' ' characters.
// - An initialized PunchCard object to stream data into
//
// Post:
// - Returns the input stream object.
std::istream& operator>>(std::istream& input, PunchCard& punchCard);