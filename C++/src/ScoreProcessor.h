#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <iostream>
#include <string>
#include <fstream>
#include "armadillo"
using namespace arma;
using namespace std;

class ScoreProcessor
{
private:
	mat teacher; // raw teacher data
	mat student; // raw student data
	mat alignedTeacher; // aligned teacher data
	mat alignedStudent; // aligned student data
	mat coordinateScoreWindowed; // windowed score for EVERY coordinate
	mat jointScoreWindowed; // windowed score for each separate joint
	int avgTotalScore; // average simple score for the entire dance

public:
	// Constructors
	ScoreProcessor(void);
	ScoreProcessor(mat teach, mat stud);
	ScoreProcessor(string file_teach, string file_stud);
	ScoreProcessor(ifstream &file_teach, ifstream &file_stud);
	ScoreProcessor(ScoreProcessor &c);

	// Destructor
	~ScoreProcessor(void);

	// Setters
	void setTeacher(mat teach);
	void setTeacher(string file_teach);
	void setTeacher(ifstream &file_teach);
	void setStudent(mat stud);
	void setStudent(string file_stud);
	void setStudent(ifstream &file_stud);

	// Getters
	mat getTeacher(void);
	mat getStudent(void);
	mat getAlignedTeacher(void);
	mat getAlignedStudent(void);
	mat getCoordinateWindowedScore(void);
	mat getJointWindowedScore(void);
	int getAvgTotalScore(void);

	// Assignment operator
	ScoreProcessor operator=(ScoreProcessor &c);

	// Data analysis functions

};

#endif /* SCORE_PROC_H */