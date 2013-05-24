#include "ScoreProcessor.h"

ScoreProcessor::ScoreProcessor(void)
{
	this->teacher = Skeleton();
	this->student = Skeleton();
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(Skeleton teach, Skeleton stud)
{
	this->teacher = teach;
	this->student = stud;
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(const char *file_teach, const char *file_stud)
{
	this->teacher = Skeleton(file_teach);
	this->student = Skeleton(file_stud);
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(ifstream &file_teach, ifstream &file_stud)
{
	this->teacher = Skeleton(file_teach);
	this->student = Skeleton(file_stud);
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(const ScoreProcessor &c)
{
	this->teacher = c.teacher;
	this->student = c.student;
	this->alignedTeacher = c.alignedTeacher;
	this->alignedStudent = c.alignedStudent;
	this->coordinateScoreWindowed = c.coordinateScoreWindowed;
	this->jointScoreWindowed = c.jointScoreWindowed;
	this->avgTotalScore = c.avgTotalScore;
}

ScoreProcessor::~ScoreProcessor() {}

void ScoreProcessor::setTeacher(Skeleton teach)
{
	this->teacher = teach;
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setTeacher(const char *file_teach)
{
	this->teacher = Skeleton(file_teach);
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setTeacher(ifstream &file_teach)
{
	this->teacher = Skeleton(file_teach);
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(Skeleton stud)
{
	this->student = stud;
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(const char *file_stud)
{
	this->student = Skeleton(file_stud);
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(ifstream &file_stud)
{
	this->student = Skeleton(file_stud);
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

Skeleton ScoreProcessor::getTeacher(void)
{
	return this->teacher;
}

Skeleton ScoreProcessor::getStudent(void)
{
	return this->student;
}

Skeleton ScoreProcessor::getAlignedTeacher(void)
{
	return this->alignedTeacher;
}

Skeleton ScoreProcessor::getAlignedStudent(void)
{
	return this->alignedStudent;

}

mat ScoreProcessor::getCoordinateWindowedScore(void)
{
	return this->coordinateScoreWindowed;
}

mat ScoreProcessor::getJointWindowedScore(void)
{
	return this->jointScoreWindowed;
}

int ScoreProcessor::getAvgTotalScore(void)
{
	return this->avgTotalScore;
}

ScoreProcessor ScoreProcessor::operator=(const ScoreProcessor &c)
{
	if(this == &c)
	{
		return *this;
	}
	else
	{
		this->teacher = c.teacher;
		this->student = c.student;
		this->alignedTeacher = c.alignedTeacher;
		this->alignedStudent = c.alignedStudent;
		this->coordinateScoreWindowed = c.coordinateScoreWindowed;
		this->jointScoreWindowed = c.jointScoreWindowed;
		this->avgTotalScore = c.avgTotalScore;
		return *this;
	}
}

double ScoreProcessor::getScore(Skeleton teacherInterim, Skeleton studentInterim)
{
	// Align signals HERE

	// Truncate the longer signal to the length of the shorter one
	int length = this->findShorterLength(teacherInterim, studentInterim);
	teacherInterim = this->truncate(teacherInterim, length);
	studentInterim = this->truncate(studentInterim, length);

	// Get the scaling factor of error
	double scalingFactor = this->getScalingFactor(teacherInterim);

	// Find simple score  for the entire signal using error squared
	mat errorMat = teacherInterim.getData() - studentInterim.getData();
	errorMat = errorMat % errorMat;
	rowvec sumErrSqVec = sum(errorMat,0);
	sumErrSqVec = sumErrSqVec / (scalingFactor * length);

	// Score based on on position for each joint
	rowvec errorJointVec(15);
	double accumulate = 0;
	for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
	{
		accumulate  = sumErrSqVec(i+0);
		accumulate += sumErrSqVec(i+1);
		accumulate += sumErrSqVec(i+2);
		errorJointVec(i/4) = accumulate / 3;
	}

	return sum(errorJointVec)/15;
}

int ScoreProcessor::findShorterLength(Skeleton teacherInterim, Skeleton studentInterim)
{
	if(teacherInterim.getData().n_rows >= studentInterim.getData().n_rows)
	{
		return studentInterim.getData().n_rows;
	}
	else
	{
		return teacherInterim.getData().n_rows;
	}
}

Skeleton ScoreProcessor::truncate(Skeleton data, int length)
{
	return Skeleton(data.getData().submat(0,0,length-1,Skeleton::numberOfColumns-1));
}

double ScoreProcessor::getScalingFactor(Skeleton data)
{
	double accumulate = 0;

	for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
	{
		accumulate += mean(data.getJoint(i+0));
		accumulate += mean(data.getJoint(i+1));
		accumulate += mean(data.getJoint(i+2));
	}

	return abs(accumulate);
}