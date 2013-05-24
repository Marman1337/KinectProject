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

ScoreProcessor::ScoreProcessor(ScoreProcessor &c)
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

ScoreProcessor ScoreProcessor::operator=(ScoreProcessor &c)
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
	}
}