#include <iostream>

class TriangleWalker{
  // This is an attempt to make a nice behaving object for 
  // walking the pascals triangle.
  // Most may be familiar with the shape:
  //        1
  //       1 1
  //      1 2 1
  //     1 3 3 1
  //       ...
  // This object intents to represent a single value in 
  // the triangle at any time and the tools to "walk" the triangle.
private:
  // Representation of value:
  int row;    
  int position;
  int value;
public:
  TriangleWalker(){
    // initializing at the first trivial point:
    row = 0;
    position = 0;
    value = 1;
  }
  void walk(){
    // walking is currently either going to next position on the right
    // or returning to zero position when the next position is past the middle of the triangle.
    if( hasReachedMiddle( position )){
      // Go to next row. 
      // Get next row and initialize value with the trivial "choose zero elements", i.e. 1.
      row++;
      position = 0;
      value = 1;
    } else {
      // Go to next position.
      // The new position, current row and previous value is used in the "nCr" calculation.
      auto n = row;
      auto r = ++position;
      value = value * ( n - r+1 ) / r;
    }
  }
  bool hasReachedMiddle(int testPosition){
    // Testing if the next position is past middle.
    return testPosition + 1 >= (float)( row + 1 ) / 2.;
  }
  int solveEuler53(){
    //"How many nCr are above LIMIT (1M) under a maximum n (100)"
    const int MAX_n = 100;
    const int LIMIT = 1000000;

    int resultAccumulation = 0;

    while(row <= MAX_n){
      // walk to the next position
      walk();
      // if value is above the LIMIT at the position,
      // then we add what is left on the row to the accumulation.
      // After the addition, we increase the row and reinit.
      if( value > LIMIT ){
        // row+1: nCr elements on the row.
        // 2*position: nCr elements already found to be below the limit.
        resultAccumulation += row+1 - 2*position;
        // next row and reinit the trivial N-choose-none, which is always 1.
        row++;
        position = 0;
        value = 1;
      } 
    }
    // At this point all the n below MAX_n have been examined 
    // and we return the accumulated result.
    return resultAccumulation;
  }
};
