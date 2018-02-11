#include "TriangleWalker.cpp"
#include <iostream>

int Solve53(){
  auto myObj = TriangleWalker();
  return myObj.solveEuler53();
}

int main(int argc, char** argv){
  
  std::cout << Solve53();

}