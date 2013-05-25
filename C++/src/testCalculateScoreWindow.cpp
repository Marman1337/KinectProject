#include <iostream>
#include <fstream>
#include <string>
#include "ScoreProcessor.h"

using namespace std;
using namespace arma;

/*
* A simple program that writes the results of the calculateScoreWindow methods
* from the ScoreProcessor class to a text file to be tested against the 
* Matlab results.
*/

int main()
{
  ScoreProcessor myScore("teacher_new.txt", "case4_new.txt");
  Skeleton myTeach("../../Matlab/DataFiles/teacher_new.txt");
  Skeleton myStud("../../Matlab/DataFiles/case4_new.txt");
  mat coor = myScore.calculateCoordinateScoreWindow(myTeach,myStud);
  coor.save("../../Matlab/DataFiles/coordinateScoreWindow.txt", raw_ascii);
  mat joint = myScore.calculateJointScoreWindow(coor);
  joint.save("../../Matlab/DataFiles/jointScoreWindow.txt", raw_ascii);
  colvec avg = myScore.calculateAvgScoreWindow(joint);
  avg.save("../../Matlab/DataFiles/avgScoreWindow.txt", raw_ascii);
  return 0;
}
