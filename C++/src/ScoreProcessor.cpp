#include "ScoreProcessor.h"

ScoreProcessor::ScoreProcessor(void)
{
	this->teacher = mat(0,0);
	this->student = mat(0,0);
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(mat teach, mat stud)
{
	this->teacher = teach;
	this->student = stud;
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(string file_teach, string file_stud)
{
	this->teacher.load(file_teach);
	this->student.load(file_stud);
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(ifstream &file_teach, ifstream &file_stud)
{
	this->teacher.load(file_teach, raw_ascii);
	this->student.load(file_stud, raw_ascii);
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
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

void ScoreProcessor::setTeacher(mat teach)
{
	this->teacher = teach;
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setTeacher(string file_teach)
{
	this->teacher.load(file_teach);
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setTeacher(ifstream &file_teach)
{
	this->teacher.load(file_teach, raw_ascii);
	// Since the teacher has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(mat stud)
{
	this->student = stud;
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(string file_stud)
{
	this->student.load(file_stud);
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

void ScoreProcessor::setStudent(ifstream &file_stud)
{
	this->student.load(file_stud, raw_ascii);
	// Since the student has changed, reset all members which contain results of data analyis
	this->alignedTeacher = mat(0,0);
	this->alignedStudent = mat(0,0);
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

mat ScoreProcessor::getTeacher(void)
{
	return this->teacher;
}

mat ScoreProcessor::getStudent(void)
{
	return this->student;
}

mat ScoreProcessor::getAlignedTeacher(void)
{
	return this->alignedTeacher;
}

mat ScoreProcessor::getAlignedStudent(void)
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