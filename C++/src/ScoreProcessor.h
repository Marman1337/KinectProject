#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <iostream>
#include <fstream>
#include "armadillo"
#include "Skeleton.h"
#include <cmath>
using namespace arma;
using namespace std;

#define NUM_WINDOWS 10
#define SCALING_FACTOR 30000

/**
*	A struct representing the 4 tuple nature of each joint.
*/
struct jointData
{
	float x, y, z, confidence;
};

/**
*	An struct giving a vector of type jointData for each of the 15 joints.
*/

struct skeletonData
{
	vector<jointData> head;
	vector<jointData> left_shoulder;
	vector<jointData> left_elbow;
	vector<jointData> left_foot;
	vector<jointData> left_hand;
	vector<jointData> left_knee;
	vector<jointData> left_hip;
	vector<jointData> neck;
	vector<jointData> right_shoulder;
	vector<jointData> right_elbow;
	vector<jointData> right_foot;
	vector<jointData> right_hand;
	vector<jointData> right_knee;
	vector<jointData> right_hip;
	vector<jointData> torso;
};

class ScoreProcessor
{
private:
	Skeleton teacher; 				// raw teacher data
	Skeleton student; 				// raw student data
	Skeleton alignedTeacher; 			// aligned teacher data
	Skeleton alignedStudent; 			// aligned student data
	int windowLength; 				// the window length given as number of frames
	double xTranslationTeacher;
	double yTranslationTeacher;
	double zTranslationTeacher;
	double xTranslationStudent;
	double yTranslationStudent;
	double zTranslationStudent;	

	// Data members to add
	double headWeight;
	double armWeight;
	double legWeight;
	double hipWeight;
	double torsoWeight;

	mat coordinateScoreWindowed; 	// windowed score for every coordinate (10x60)
	mat jointScoreWindowed; 		// windowed score for each separate joint (10x15)
	mat avgScoreWindowed; 			// average score for each window (10x1)
	double avgTotalScore; 			// average simple score for the entire dance

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
	Skeleton translate(Skeleton data, int frame, bool isTeacher);
	void undoTranslate(void);

	// New functions
	int motionlessFrameOverall(Skeleton data, const int windowLen);
	int motionlessFrame(colvec coordData, const int windowLen);
	mat differenceMatrix(mat inputMatrix);
	int delayEstimate(Skeleton skeleton1, Skeleton skeleton2);
	void zeroPad(mat &inputSignal1, mat &inputSignal2);
	void align(Skeleton skeleton1, Skeleton skeleton2, int delayEstimate, mat &correctSignal1, mat &correctSignal2);
	void calculateAvgTotalScore(void);
	mat errorToScore(mat errorMat);
	double errorToScore(double error);
	mat removeConfidence(mat data);
	double penalise(int i);
	mat raiseToPower(double base, mat exponent);
	vec ScoreProcessor::weightVector(double headWeight, double armWeight, double legWeight, double hipWeight, double torsoWeight);

	// Conversion functions
	skeletonData convertSkeleton(mat inputData);

public:
	// Constructors to change
	ScoreProcessor(void);
	ScoreProcessor(Skeleton teacherSkeleton, Skeleton studentSkeleton);
	ScoreProcessor(const char *file_teach, const char *file_stud);
	ScoreProcessor(ifstream &file_teach, ifstream &file_stud);
	ScoreProcessor(const ScoreProcessor &c);

	// Constructors to make
	ScoreProcessor(Skeleton teacherSkeleton, Skeleton studentSkeleton, double headWeight, double armWeight, double legWeight, double hipWeight, double torsoWeight);
	ScoreProcessor(const char *file_teach, const char *file_stud,  double headWeight, double armWeight, double legWeight, double hipWeight, double torsoWeight);
	ScoreProcessor(ifstream &file_teach, ifstream &file_stud,  double headWeight, double armWeight, double legWeight, double hipWeight, double torsoWeight);

	// Destructor
	~ScoreProcessor(void);

	// Setters
	void setTeacher(Skeleton teach);
	void setTeacher(const char *file_teach);
	void setTeacher(ifstream &file_teach);
	void setStudent(Skeleton stud);
	void setStudent(const char *file_stud);
	void setStudent(ifstream &file_stud);
	void setJointWeights(double headWeight, double armWeight, double legWeight, double hipWeight, double torsoWeight);

	// Getters
	Skeleton getTeacher(void);
	Skeleton getStudent(void);
	Skeleton getAlignedTeacher(void);
	Skeleton getAlignedStudent(void);
	mat getCoordinateWindowedScore(void);
	mat getJointWindowedScore(void);
	mat getAvgWindowedScore(void);
	double getAvgTotalScore(void);
	int getWindowLength(void);

	// Conversion functions
	skeletonData convertAlignedTeacher(void);
	skeletonData convertAlignedStudent(void);

	// Assignment operator
	ScoreProcessor operator=(const ScoreProcessor &c);

	// Analyse
	void analyse();
};

#endif /* SCORE_PROC_H */
