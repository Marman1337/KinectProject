#include <iostream>
#include <fstream>
#include <string>
#include "../ScoreProcessor.h"

using namespace std;
using namespace arma;

/*
* A simple program that writes the result of getScore from the 
* ScoreProcessor class to a text file to be tested against the 
* Matlab results.
*/

int main()
{
	ScoreProcessor myScore("teacher_new.txt","case4_new.txt");
  Skeleton t(myScore.getTeacher().getData());
  Skeleton s(myScore.getStudent().getData());
  double averageScore = myScore.getScore(t, s);
  ofstream myFile;
  cout << averageScore << endl;
  myFile.open("./getScoreTest.txt");
  if(myFile.is_open())
  {
    cout << "Open\n";
  }
  else
  {
    cout << "Not open\n";
  
  }
  myFile << averageScore << "\n";
  myFile.close();
  return 0;
}
