#ifndef SKELETON_H
#define SKELETON_H
#include "armadillo"
using namespace std;
using namespace arma;

class Skeleton
{
private:
	mat data;

public:
	/**
	*	An enum used to get each joint of the data by specifying using
	*	their names and not numbers.
	*/
	typedef enum 
	{
		HEAD = 0,
		LEFT_SHOULDER = 4,
		LEFT_ELBOW = 8,
		RIGHT_SHOULDER = 12,
		RIGHT_ELBOW = 16,
		LEFT_HAND = 20,
		RIGHT_HAND = 24,
		TORSO = 28,
		LEFT_HIP = 32,
		RIGHT_HIP = 36,
		LEFT_KNEE = 40,
		LEFT_FOOT = 44,
		RIGHT_KNEE = 48,
		NECK = 52,
		RIGHT_FOOT = 56
	} Joint;

	// Get the next joint
	static const int nextJoint;
	static const int numberOfColumns;
	static const int numberOfJoints;

	// Constructors
	Skeleton(void);
	Skeleton(mat dataMat);
	Skeleton(const char *file);
	Skeleton(ifstream &file);
	Skeleton(const Skeleton &c);

	// Destructor
	~Skeleton(void);

	// Getters
	mat getData(void);

	// Setter
	void setData(mat dataMat);

	// Get joint functions
	colvec getJoint(int indexOfJoint);

	// Assignment operator
	Skeleton operator=(const Skeleton &c);
};

#endif /* SKELETON_H */