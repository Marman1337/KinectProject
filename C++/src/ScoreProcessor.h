#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <iostream>
#include <fstream>
#include "armadillo"
#include "Skeleton.h"
using namespace arma;
using namespace std;

class ScoreProcessor
{
private:
	Skeleton teacher; // raw teacher data
	Skeleton student; // raw student data
	Skeleton alignedTeacher; // aligned teacher data
	Skeleton alignedStudent; // aligned student data
	mat coordinateScoreWindowed; // windowed score for EVERY coordinate
	mat jointScoreWindowed; // windowed score for each separate joint
	double avgTotalScore; // average simple score for the entire dance

	// Data analysis functions
	double getScore(Skeleton teacherInterim, Skeleton studentInterim); // add delay estimate
	int findShorterLength(Skeleton teacherInterim, Skeleton studentInterim);
	Skeleton truncate(Skeleton data, int length);
	double getScalingFactor(Skeleton data);

public:
	// Constructors
	ScoreProcessor(void);
	ScoreProcessor(Skeleton teach, Skeleton stud);
	ScoreProcessor(const char *file_teach, const char *file_stud);
	ScoreProcessor(ifstream &file_teach, ifstream &file_stud);
	ScoreProcessor(ScoreProcessor &c);

	// Destructor
	~ScoreProcessor(void);

	// Setters
	void setTeacher(Skeleton teach);
	void setTeacher(const char *file_teach);
	void setTeacher(ifstream &file_teach);
	void setStudent(Skeleton stud);
	void setStudent(const char *file_stud);
	void setStudent(ifstream &file_stud);

	// Getters
	Skeleton getTeacher(void);
	Skeleton getStudent(void);
	Skeleton getAlignedTeacher(void);
	Skeleton getAlignedStudent(void);
	mat getCoordinateWindowedScore(void);
	mat getJointWindowedScore(void);
	int getAvgTotalScore(void);

	// Assignment operator
	ScoreProcessor operator=(ScoreProcessor &c);

};

#endif /* SCORE_PROC_H */