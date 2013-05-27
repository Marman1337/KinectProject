#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <iostream>
#include <fstream>
#include "armadillo"
#include "Skeleton.h"
using namespace arma;
using namespace std;

#define NUM_WINDOWS 10

class ScoreProcessor
{
private:
	Skeleton teacher; // raw teacher data
	Skeleton student; // raw student data
	Skeleton alignedTeacher; // aligned teacher data
	Skeleton alignedStudent; // aligned student data
	mat coordinateScoreWindowed; // windowed score for every coordinate (10x60)
	mat jointScoreWindowed; // windowed score for each separate joint (10x15)
	mat avgScoreWindowed; // average score for each window (10x1)
	double avgTotalScore; // average simple score for the entire dance

	// Data analysis functions
	// Calculates a simple score for the entire dance
	double calculateScore(Skeleton teacherInterim, Skeleton studentInterim, int delay);

	// Calculates a windowed score for every joint's coordinate; (10x60)
	mat calculateCoordinateScoreWindow(Skeleton teacherInterim, Skeleton studentInterim);
	// Calculates an average windowed score for every joint; (10x15)
	mat calculateJointScoreWindow(mat coordinateScore);
	// Calculates an average score for each window; (10x1)
	colvec calculateAvgScoreWindow(mat jointScore);

	int findShorterLength(Skeleton teacherInterim, Skeleton studentInterim);
	Skeleton truncate(Skeleton data, int length);
	double calculateScalingFactor(Skeleton data);
	Skeleton translate(Skeleton data, int frame);

	// New functions
	int motionlessFrameOverall(Skeleton data, const int windowLen);
	int motionlessFrame(colvec coordData, const int windowLen);
	mat differenceMatrix(mat inputMatrix);
	int delayEstimate(Skeleton data1, Skeleton data2);
	void zeroPad(mat &inputSignal1, mat &inputSignal2);
	void align(Skeleton data1, Skeleton data2, int delayEstimate, mat &correctSignal1, mat &correctSignal2);

public:
	// Constructors
	ScoreProcessor(void);
	ScoreProcessor(Skeleton teach, Skeleton stud);
	ScoreProcessor(const char *file_teach, const char *file_stud);
	ScoreProcessor(ifstream &file_teach, ifstream &file_stud);
	ScoreProcessor(const ScoreProcessor &c);

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
	mat getAvgWindowedScore(void);
	double getAvgTotalScore(void);

	// Assignment operator
	ScoreProcessor operator=(const ScoreProcessor &c);

	// Analyse
	void analyse();
};

#endif /* SCORE_PROC_H */