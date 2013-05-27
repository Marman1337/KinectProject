#include <iostream>
#include <fstream>
#include <string>
#include "../ScoreProcessor.h"

using namespace std;
using namespace arma;

/*
* A simple program that writes the result of the analyse method from the 
* ScoreProcessor class to a text file to be tested against the 
* Matlab results. It writes the results of the class members:
*   - coordinateScoreWindowed
*   - jointScoreWindowed
*   - avgScoreWindowed
*   - avgTotalScore
*/

int main()
{
  // Initialise an instance of the ScoreProcessor class
	ScoreProcessor myScore("../teacher_new.txt","../case4_new.txt");
  myScore.analyse();
  // Write the results of the three different class members to three different files 
  // in the matlab test directory.
  mat score = myScore.getCoordinateWindowedScore();
  score.save("../../../Matlab/DataFiles/coordinatScoreWindowed_results.txt", raw_ascii);  
  score = myScore.getJointWindowedScore();
  score.save("../../../Matlab/DataFiles/jointScoreWindowed_results.txt", raw_ascii);  
  score = myScore.getAvgWindowedScore();
  score.save("../../../Matlab/DataFiles/averageScoreWindowed_results.txt", raw_ascii);
  score = myScore.getAvgTotalScore();
  score.save("../../../Matlab/DataFiles/averageTotalScore_results.txt", raw_ascii);

  return 0;
}
