#include "Skeleton.h"

const int Skeleton::nextJoint = 4;
const int Skeleton::numberOfColumns = 60;
const int Skeleton::numberOfJoints = 15;

Skeleton::Skeleton(void)
{
	this->data = mat(0,0);
}

Skeleton::Skeleton(mat dataMat)
{
	this->data = dataMat;
}

Skeleton::Skeleton(const char *file)
{
	this->data.load(file);
}

Skeleton::Skeleton(ifstream &file)
{
	this->data.load(file, raw_ascii);
}

Skeleton::Skeleton(const Skeleton &c)
{
	this->data = c.data;
}

Skeleton::~Skeleton(void) {}

mat Skeleton::getData(void)
{
	return this->data;
}

Skeleton Skeleton::operator=(const Skeleton &c)
{
	if(this == &c)
	{
		return *this;
	}
	else
	{
		this->data = c.data;
	}

	return *this;
}

colvec Skeleton::getJoint(int indexOfJoint)
{
	return this->data.col(indexOfJoint);
}