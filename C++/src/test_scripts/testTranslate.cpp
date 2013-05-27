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
	ScoreProcessor myScore("teacher_new.txt","case4_new.txt");
  // Initialise 2 Skeletons for the teacher and student data
  Skeleton t(myScore.getTeacher().getData());

  /**********************
  * Do Data Analysis here
  **********************/
  // Save the translated skeleton
  Skeleton tTranslated(myScore.translate(t, 30));
  // Write results to a file
  tTranslated.getData().save("../../Matlab/DataFiles/translate_results.txt", raw_ascii);
 
  return 0;
}
