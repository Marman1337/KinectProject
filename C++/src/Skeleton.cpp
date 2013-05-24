#include "Skeleton.h"

const int Skeleton::nextJoint = 4;

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

Skeleton::Skeleton(Skeleton &c)
{
	this->data = c.data;
}

Skeleton::~Skeleton(void) {}

mat Skeleton::getData(void)
{
	return this->data;
}

Skeleton Skeleton::operator=(Skeleton &c)
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

mat Skeleton::getJoint(int indexOfJoint)
{
	return this->data.col(indexOfJoint);
}