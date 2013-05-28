#include <iostream>
#include <fstream>
#include <string>
#include "../ScoreProcessor.h"

using namespace std;
using namespace arma;

/*
* A simple program that writes the result of translate from the 
* ScoreProcessor class to a text file to be tested against the 
* Matlab results.
*/

int main()
{
  // Initialise an instance of the ScoreProcessor class
	ScoreProcessor myScore("../teacher_new.txt","../case4_new.txt");
  // Initialise 2 Skeletons for the teacher and student data
  myScore.analyse();
  mat score = myScore.getCoordinateWindowedScore();
  score.save("../../../Matlab/DataFiles/errorToScoreCoordinate_results.txt", raw_ascii);  
  score = myScore.getJointWindowedScore();
  score.save("../../../Matlab/DataFiles/errorToScoreJoint_results.txt", raw_ascii);  
  score = myScore.getAvgWindowedScore();
  score.save("../../../Matlab/DataFiles/errorToScoreAvg_results.txt", raw_ascii);

  
  return 0;
}
