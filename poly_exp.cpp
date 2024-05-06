///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////


#include "poly_exp.hpp"
#include <iostream>
#include <math.h>
#include <vector>

int algorithms::soccer_exhaustive(const std::vector<std::string> field) {

    //If statement to check if field is empty
    if(field.size() == 0 || field[0].size() == 0){
      throw std::invalid_argument("Invalid, empty");
    }
    //If statement to check if field is 1x1 and contains either . or X
    if(field.size() == 1 && field[0].size() == 1){
      if(field[0][0] == '.'){
        return 1;
      }
      else if(field[0][0] == 'X'){
        return 0;
      }
      else{
        throw std::invalid_argument("Invalid, character");
      }
    }
    int maxrow = field.size();
    int maxcolumn = field[0].size();
    int field_length = maxrow + maxcolumn - 2;
    //If statement to check if n is greater than 31
    if(field_length > 31){
      throw std::invalid_argument("Invalid, 32 bits");
    }
    //For loop to check if field contains valid characters and is a valid field
    for(int i = 0; i < maxrow; i++){
      for(int j = 0; j < maxcolumn; j++){
        if(field[i][j] != 'X' && field[i][j] != '.'){
          throw std::invalid_argument("Invalid, character");
        }
      }
      if(field[i].size() != maxcolumn){
        throw std::invalid_argument("Invalid, row less");
      }
    }
    int counter = 0;
    bool basecase = true;
    int row = 0;
    int column = 0;
    int b = 0;
    //For loop to run through every possible candidate
    for(int i = 0; i < pow(2,field_length); i++){
      std::vector<char> candidate;
      basecase = true;
      row = 0;
      column = 0;
      for(int j = 0; j < field_length; j++){
        b = (i >> j) & 1;
        //If statement to overload bit and push right or down into candidate vector
        if(b == 1){
          candidate.push_back('>');
        }
        else{
          candidate.push_back('v');
        }
        //If statement to count movements of candidates depending on direction
        if(candidate[j] == '>'){
          column++;
        }
        else if(candidate[j] == 'v'){
          row++;
        }
        //If statement to check and stop loop if candidate is inside the grid
        //and has never touched an x cell
        if(row >= maxrow || column >= maxcolumn || field[row][column] == 'X'){
          basecase = false;
          break;
        }
      }
      //If statement to check and count if candidate ends at (r-1)(c-1)
      //and never touched an x cell and remained in the grid
      if(basecase == true && row == maxrow - 1 && column == maxcolumn - 1){
        counter++;
      }
    }
    //returns number of routes possible
    return counter;
}

int algorithms::soccer_dyn_prog(const std::vector<std::string> field) {

    //If statement to check if field is empty
    if(field.size() == 0 || field[0].size() == 0){
      throw std::invalid_argument("Invalid, empty");
    }
    //If statement to check if field is 1x1 and contains either . or X
    if(field.size() == 1 && field[0].size() == 1){
      if(field[0][0] == '.'){
        return 1;
      }
      else if(field[0][0] == 'X'){
        return 0;
      }
      else{
        throw std::invalid_argument("Invalid, character");
      }
    }
    int maxrow = field.size();
    int maxcolumn = field[0].size();
    //For loop to check if statement contains invalid characters or is an invalid field
    for(int i = 0; i < maxrow; i++){
      for(int j = 0; j < maxcolumn; j++){
        if(field[i][j] != 'X' && field[i][j] != '.'){
          throw std::invalid_argument("Invalid, character");
        }
      }
      if(field[i].size() != maxcolumn){
        throw std::invalid_argument("Invalid, row less");
      }
    }
    int matrixarray[maxrow][maxcolumn];
    //For loop to set all elements to zero
    for(int i = 0; i < maxrow; i++){
      for(int j = 0; j < maxcolumn; j++){
        matrixarray[i][j] = 0;
      }
    }
    matrixarray[0][0] = 1;
    //For loop to run through every possible candidate
    for(int i = 0; i < maxrow; i++){
      for(int j = 0; j < maxcolumn; j++){
        //If statement to check if it is impassible
        if(field[i][j] == 'X'){
          matrixarray[i][j] = 0;
        }
        else{
          int above = 0;
          int from_left = 0;
          //If statement to check if i is greater than 0 and prev element is passible
          if(i > 0 && field[i - 1][j] == '.'){
            above = matrixarray[i - 1][j];
          }
          //If statement to check if j is greater than 0 and prev element is passible
          if(j > 0 && field[i][j - 1] == '.'){
            from_left = matrixarray[i][j - 1];
          }
          //adds possible routes to current element
          matrixarray[i][j] += above + from_left;
        }
      }
    }
    //Returns number of routes that are possible
    return matrixarray[maxrow - 1][maxcolumn - 1];
}
