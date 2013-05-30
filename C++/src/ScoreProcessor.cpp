#include "ScoreProcessor.h"

/************************************************
** Constructors
*************************************************/

ScoreProcessor::ScoreProcessor(void)
{
	this->teacher = Skeleton();
	this->student = Skeleton();
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->windowLength = 1;
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

ScoreProcessor::ScoreProcessor(Skeleton teacherSkeleton, Skeleton studentSkeleton)
{
	this->teacher = teacherSkeleton;
	this->student = studentSkeleton;
	this->alignedTeacher = Skeleton();
	this->alignedStudent = Skeleton();
	this->windowLength = 1;	
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
	this->windowLength = 1;	
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
	this->windowLength = 1;	
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
	this->windowLength = c.windowLength;
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
	this->windowLength = 1;
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
	this->windowLength = 1;
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
	this->windowLength = 1;
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
	this->windowLength = 1;
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
	this->windowLength = 1;
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
	this->windowLength = 1;
	this->coordinateScoreWindowed = mat(0,0);
	this->jointScoreWindowed = mat(0,0);
	this->avgTotalScore = NULL;
}

/************************************************
** Getters
*************************************************/

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

skeletonData ScoreProcessor::convertSkeleton(mat inputData)
{
	skeletonData dataStruct;
	jointData frame;

	for(int i = 0; i < inputData.n_rows; i++)
	{
		frame.x = float(inputData.at(i, Skeleton::HEAD+0));
		frame.y = float(inputData.at(i, Skeleton::HEAD+1));
		frame.z = float(inputData.at(i, Skeleton::HEAD+2));
		frame.confidence = float(inputData.at(i, Skeleton::HEAD+3));
		dataStruct.head.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_SHOULDER+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_SHOULDER+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_SHOULDER+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_SHOULDER+3));
		dataStruct.left_shoulder.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_ELBOW+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_ELBOW+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_ELBOW+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_ELBOW+3));
		dataStruct.left_elbow.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_HAND+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_HAND+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_HAND+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_HAND+3));
		dataStruct.left_hand.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_FOOT+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_FOOT+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_FOOT+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_FOOT+3));
		dataStruct.left_foot.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_HIP+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_HIP+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_HIP+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_HIP+3));
		dataStruct.left_hip.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::LEFT_KNEE+0));
		frame.y = float(inputData.at(i, Skeleton::LEFT_KNEE+1));
		frame.z = float(inputData.at(i, Skeleton::LEFT_KNEE+2));
		frame.confidence = float(inputData.at(i, Skeleton::LEFT_KNEE+3));
		dataStruct.left_knee.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::TORSO+0));
		frame.y = float(inputData.at(i, Skeleton::TORSO+1));
		frame.z = float(inputData.at(i, Skeleton::TORSO+2));
		frame.confidence = float(inputData.at(i, Skeleton::TORSO+3));
		dataStruct.torso.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::NECK+0));
		frame.y = float(inputData.at(i, Skeleton::NECK+1));
		frame.z = float(inputData.at(i, Skeleton::NECK+2));
		frame.confidence = float(inputData.at(i, Skeleton::NECK+3));
		dataStruct.neck.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_SHOULDER+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_SHOULDER+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_SHOULDER+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_SHOULDER+3));
		dataStruct.right_shoulder.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_ELBOW+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_ELBOW+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_ELBOW+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_ELBOW+3));
		dataStruct.right_elbow.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_HAND+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_HAND+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_HAND+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_HAND+3));
		dataStruct.right_hand.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_FOOT+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_FOOT+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_FOOT+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_FOOT+3));
		dataStruct.right_foot.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_KNEE+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_KNEE+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_KNEE+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_KNEE+3));
		dataStruct.right_knee.push_back(frame);

		frame.x = float(inputData.at(i, Skeleton::RIGHT_HIP+0));
		frame.y = float(inputData.at(i, Skeleton::RIGHT_HIP+1));
		frame.z = float(inputData.at(i, Skeleton::RIGHT_HIP+2));
		frame.confidence = float(inputData.at(i, Skeleton::RIGHT_HIP+3));
		dataStruct.right_hip.push_back(frame);
	}

	return dataStruct;
}

skeletonData ScoreProcessor::convertAlignedTeacher(void)
{
	return this->convertSkeleton(this->alignedTeacher.getData());
}

skeletonData ScoreProcessor::convertAlignedStudent(void)
{
	return this->convertSkeleton(this->alignedStudent.getData());
}

mat ScoreProcessor::getCoordinateWindowedScore(void)
{
	return this->coordinateScoreWindowed;
}

mat ScoreProcessor::getJointWindowedScore(void)
{
	return this->jointScoreWindowed;
}

mat ScoreProcessor::getAvgWindowedScore(void)
{
	return this->avgScoreWindowed;
}

double ScoreProcessor::getAvgTotalScore(void)
{
	return this->avgTotalScore;
}

int ScoreProcessor::getWindowLength(void)
{
	return this->windowLength;
}

/************************************************
** Operators
*************************************************/

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

/************************************************
** Analysis Methods
*************************************************/

/**
*	Calculates simple (error) score for the whole signal. Not windowed.
*/

double ScoreProcessor::calculateScore(Skeleton teacherInterim, Skeleton studentInterim, int delay)
{
	// Align signals
	mat alignedTeacher, alignedStudent;
	this->align(teacherInterim, studentInterim, delay, alignedTeacher, alignedStudent);
	teacherInterim.setData(alignedTeacher);
	studentInterim.setData(alignedStudent);

	// Truncate the longer signal to the length of the shorter one
	int length = this->findShorterLength(teacherInterim, studentInterim);
	teacherInterim = this->truncate(teacherInterim, length);
	studentInterim = this->truncate(studentInterim, length);

	// Find simple score  for the entire signal using error squared
	mat errorMat = teacherInterim.getData() - studentInterim.getData();
	errorMat = errorMat % errorMat;
	rowvec sumErrSqVec = sum(errorMat,0);
	sumErrSqVec = sumErrSqVec / length;

	// Score based on on position for each joint
	rowvec errorJointVec(Skeleton::numberOfJoints);
	double accumulate = 0;
	for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
	{
		accumulate  = sumErrSqVec(i+0);
		accumulate += sumErrSqVec(i+1);
		accumulate += sumErrSqVec(i+2);
		errorJointVec(i/4) = accumulate / 3;
	}

	return sum(errorJointVec)/Skeleton::numberOfJoints;
}

/**
*	Calculates score for each coordinate in a windowed manner.
* Returns a 10x60 Matrix.
*/

mat ScoreProcessor::calculateCoordinateScoreWindow(Skeleton teacherInterim, Skeleton studentInterim)
{
	int length = this->findShorterLength(teacherInterim, studentInterim);
	teacherInterim = this->truncate(teacherInterim, length);
	studentInterim = this->truncate(studentInterim, length);

	this->windowLength = int(length/NUM_WINDOWS); // floor

	mat coordinateError(NUM_WINDOWS,Skeleton::numberOfColumns);
	mat errorMat;
	rowvec errorVec(Skeleton::numberOfColumns);
	rowvec currentVec(Skeleton::numberOfColumns);
	double oldMean;
	double currentMean;

	for(int i = 0; i < NUM_WINDOWS; i++)
	{
		oldMean = LONG_MAX;
		for(int j = -10; j < 11; j++)
		{
			if(i*this->windowLength+j < 0 || (i+1)*this->windowLength-1+j > length-1)
			{
				continue;
			}
			errorMat = teacherInterim.getData()( span(i*this->windowLength , (i+1)*this->windowLength-1 ) , span::all ) -
				studentInterim.getData()( span( i*this->windowLength+j , (i+1)*this->windowLength-1+j ) , span::all );
			errorMat = errorMat % errorMat;
			errorVec = sum(errorMat,0);
			currentVec = errorVec / (SCALING_FACTOR * this->windowLength);
			currentMean = mean(mean(this->removeConfidence(currentVec)));
			if(currentMean*this->penalise(j) < oldMean)
			{
				oldMean = currentMean*this->penalise(j);
				coordinateError.row(i) = currentVec*this->penalise(j);
			}
		}
	}

	return coordinateError;
}

mat ScoreProcessor::removeConfidence(mat data)
{
	int rows = data.n_rows;
	int cols = data.n_cols;
	mat output(rows, 45);

	int j = 0;
	for(int i = 0; i < Skeleton::numberOfColumns; i++)
	{
		if(i % 4 != 3)
		{
			output.col(j) = data.col(i);
			j++;
		}
	}

	return output;
}

double ScoreProcessor::penalise(int i)
{
	return -0.5*exp(-std::pow(0.3*i,2)/2) + 1.5;
}

/**
*	Calculates score for each joint in a windowed manner.
* Returns a 10x15 Matrix.
*/

mat ScoreProcessor::calculateJointScoreWindow(mat coordinateScore)
{
	mat jointError(NUM_WINDOWS,Skeleton::numberOfJoints);
	colvec sumError(NUM_WINDOWS);

	for(int i = 0; i < Skeleton::numberOfColumns; i = i + Skeleton::nextJoint)
	{
		sumError  = coordinateScore.col(i+0);
		sumError += coordinateScore.col(i+1);
		sumError += coordinateScore.col(i+2);
		jointError.col(i/4) = sumError/3;
	}

	return jointError;
}

/**
*	Calculates average score for each window.
* Returns a 10x1 Matrix.
*/

colvec ScoreProcessor::calculateAvgScoreWindow(mat jointScore)
{
	return colvec(sum(jointScore,1)/Skeleton::numberOfJoints);
}

/**
*	Returns the length of the shortest data signal corresponding to the two skeletons.
*/

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

/**
*	Truncates the signal so that it is the length provided and returns it.
*/

Skeleton ScoreProcessor::truncate(Skeleton data, int length)
{
	return Skeleton(data.getData().submat( 0 , 0 , length-1 , Skeleton::numberOfColumns-1 ));
}

/**
*	Returns a Skeleton that is translated in such a way that the torso is given as the origin.
*/

Skeleton ScoreProcessor::translate(Skeleton skeleton1, int frame, bool isTeacher)
{
	mat dataMat = skeleton1.getData();
	dataMat = dataMat.submat( frame , 0 , skeleton1.getData().n_rows-1 , Skeleton::numberOfColumns-1 ); //they might return either a FRAME NUMBER or index of the frame, in which case it will be frame-1

	if(isTeacher)
	{
		this->xTranslationTeacher = dataMat.at(0 , Skeleton::TORSO+0);
		this->yTranslationTeacher = dataMat.at(0 , Skeleton::TORSO+1);
		this->zTranslationTeacher = dataMat.at(0 , Skeleton::TORSO+2);

		for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
		{
			dataMat.col(i+0) -= this->xTranslationTeacher;
			dataMat.col(i+1) -= this->yTranslationTeacher;
			dataMat.col(i+2) -= this->zTranslationTeacher;
		}
	}
	else
	{
		this->xTranslationStudent = dataMat.at(0 , Skeleton::TORSO+0);
		this->yTranslationStudent = dataMat.at(0 , Skeleton::TORSO+1);
		this->zTranslationStudent = dataMat.at(0 , Skeleton::TORSO+2);

		for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
		{
			dataMat.col(i+0) -= this->xTranslationStudent;
			dataMat.col(i+1) -= this->yTranslationStudent;
			dataMat.col(i+2) -= this->zTranslationStudent;
		}
	}

	return Skeleton(dataMat);
}

/**
*	Returns a Skeleton that is translated back to the original signal's position.
*/

void ScoreProcessor::undoTranslate(void)
{
	mat teacherData = this->alignedTeacher.getData();
	mat studentData = this->alignedStudent.getData();

	for(int i = 0; i < Skeleton::numberOfColumns; i = i+Skeleton::nextJoint)
	{
		teacherData.col(i+0) += this->xTranslationTeacher;
		teacherData.col(i+1) += this->yTranslationTeacher;
		teacherData.col(i+2) += this->zTranslationTeacher;

		studentData.col(i+0) += this->xTranslationStudent;
		studentData.col(i+1) += this->yTranslationStudent;
		studentData.col(i+2) += this->zTranslationStudent;
	}

	this->alignedTeacher.setData(teacherData);
	this->alignedStudent.setData(studentData);
}

/**
*	Returns a matrix that has the same number of columns as the input matrix and one less row. 
* Represents the difference of rows in series.
*/

mat ScoreProcessor::differenceMatrix(mat inputMatrix)
{
	// Get length of the input matrix
	int numRows = inputMatrix.n_rows;
	int numCols = inputMatrix.n_cols;

	if(numRows == 1)
	{
		inputMatrix = inputMatrix.t();
		int temp = numRows;
		numRows = numCols;
		numCols = temp;
	}

	// Difference array will have one less element.
	mat differenceMat = zeros(numRows-1, numCols);
	for(int i = 0; i < numRows-1; i++)
	{
		for(int j = 0; j < numCols; j++)
		{
			differenceMat(i,j) = inputMatrix(i,j) - inputMatrix(i+1,j);
			if(differenceMat(i,j) == 0)
			{
				differenceMat(i,j) = 100000;
			}
		}
	}

	return differenceMat;
}

/**
*	Returns the frame which corresponds to corresponds to motionless activity for 
* a single coordinate. 
* The larger the window length, the longer the student must stand still but the
* more accurate the result.
*/

int ScoreProcessor::motionlessFrame(colvec coordData, const int windowLen)
{
	// Find the number of frames left after windowing the data.
	int numFrameLeft = coordData.n_elem % windowLen;
	// Remove the last frames in order to have an exact fit of windows.
	coordData = coordData.rows(0, coordData.n_elem - 1 - numFrameLeft);

	int minWindowIndex = 0;
	double minCost = 0;

	const int numFramesInitInterv = 150; // Number of frames in 5 seconds, assuming 30fps.
	int numWindowsInitInterv = (int)(numFramesInitInterv/windowLen);
	int numWindows = coordData.n_elem/windowLen;
	// For each window in the data for 15 seconds.
	for(int i = 0; i < min(numWindowsInitInterv, numWindows); i++)
	{
		// Get the new window.
		colvec currentWindow = coordData.rows(i*windowLen, ((i+1)*windowLen-1));
		// Get cost of window.
		rowvec costVec = sum(abs(differenceMatrix(currentWindow)));
		double cost = sum(costVec);

		// Find minimum window cost.
		if(i == 0)
		{
			minCost = cost;
		}
		else
		{
			if(cost < minCost)
			{
				minCost = cost;
				minWindowIndex = i;
			}
		}
	}

	// Return the index of the frame with the lowest cost.
	return minWindowIndex * windowLen;
}

/**
*	Returns the frame which corresponds to corresponds to motionless activity for 
* the whole Skeleton. 
* The larger the window length, the longer the student must stand still but the
* more accurate the result.
*/

int ScoreProcessor::motionlessFrameOverall(Skeleton data, const int windowLen)
{
	/* Find the motionless frame using function motionlessframe() on limb joints
	and finding the value with highest absolute frequency
	*/

	const int numCoords = 3; // total number of coords x,y,z.					
	const int numJointsCoords = 24;
	vec values = zeros(numJointsCoords);

	// Find motionless frame for subset of joints
	// for all coordinates
	mat inputSignal = data.getData();
	for(int i = 0; i < numCoords; i++)
	{
		// left elbow
		values(i) = motionlessFrame(inputSignal.col(Skeleton::LEFT_ELBOW + i),windowLen);
		// right elbow
		values(i+3) = motionlessFrame(inputSignal.col(Skeleton::RIGHT_ELBOW + i),windowLen);
		// left hand
		values(i+6) = motionlessFrame(inputSignal.col(Skeleton::LEFT_HAND + i),windowLen);
		// right hand
		values(i+9) = motionlessFrame(inputSignal.col(Skeleton::RIGHT_HAND + i),windowLen);
		// left knee
		values(i+12) = motionlessFrame(inputSignal.col(Skeleton::LEFT_KNEE + i),windowLen);
		// left foot
		values(i+15) = motionlessFrame(inputSignal.col(Skeleton::LEFT_FOOT + i),windowLen);
		// right knee
		values(i+18) = motionlessFrame(inputSignal.col(Skeleton::RIGHT_KNEE + i),windowLen);
		// right foot
		values(i+21) = motionlessFrame(inputSignal.col(Skeleton::RIGHT_FOOT + i),windowLen);
	}

	// Get unique frame indices.
	vec uniqueValues = unique(values);

	// Get frequency count of each value.
	uvec freqCount = histc(values,uniqueValues);

	// Get the most frequently occuring frame's index.
	uword maxFreqIndex;
	freqCount.max(maxFreqIndex);

	return int(uniqueValues(maxFreqIndex));
}

/**
*	Returns the estimated delay between the two input signals as a number of frames.
*/

int ScoreProcessor::delayEstimate(Skeleton skeleton1, Skeleton skeleton2)
{
	/**
	* Align signals with zero padding 
	* and reverse the second signal in order
	* to calculate the cross-correlation using
	* the convolution.
	*/

	// Align signals by zero padding the shortest.
	mat inputSignal1 = skeleton1.getData();
	mat inputSignal2 = skeleton2.getData();

	this->zeroPad(inputSignal1, inputSignal2);
	// Reverse signal.
	mat inputSignal2Reversed = flipud(inputSignal2);

	vec xcorrResult;
	vec delayJoints = zeros(Skeleton::numberOfColumns);
	for(int i = 0; i < Skeleton::numberOfColumns; i++)
	{
		// Skip z-coordinate and confidence level
		if(i % 4 == 2 || i % 4 == 3)
		{
			continue;
		}
		// Calculate the cross-correlation of the signals.
		xcorrResult = conv(inputSignal1.col(i),inputSignal2Reversed.col(i));
		// Collect the delay between two signals for all coordinates.
		uword maxIndex = 0;
		xcorrResult.max(maxIndex);
		delayJoints(i) =  maxIndex;
	}

	//const int numJoints = 15;
	vec xDelay = zeros(Skeleton::numberOfJoints);
	vec yDelay = zeros(Skeleton::numberOfJoints);	


	// Extract delays for x and y coordinates for all joints.
	for(Skeleton::Joint i = Skeleton::HEAD; i <= Skeleton::RIGHT_FOOT; i = (Skeleton::Joint) (i + Skeleton::nextJoint))
	{
		xDelay(i/4) = delayJoints(i+0);
		yDelay(i/4) = delayJoints(i+1);
	}

	// Subtract the cross correlation offset.
	int xcorrLen = xcorrResult.n_elem;
	int offsetPoint = int(xcorrLen/2 + 0.5);

	xDelay = xDelay - offsetPoint;
	yDelay = yDelay - offsetPoint;

	/* Calculate the mean and standard deviation of delay offsets,
	and use them later to estimate the delay only using values
	which lie within one standard deviation from the mean, 
	i.e. eliminate outliers
	*/
	double xMean = mean(xDelay);
	double yMean = mean(yDelay);
	double xStd = stddev(xDelay);
	double yStd = stddev(yDelay);

	// Identify outliers, accumulate the delays
	// which are within one standard deviation from mean
	double delaySum = 0;
	double elementsCount = 0;
	for(int i = 0; i < Skeleton::numberOfJoints; i++)
	{
		if( xMean - xStd < xDelay(i) && xDelay(i) < xMean + xStd)
		{
			delaySum = delaySum + xDelay(i);
			elementsCount++;
		}

		if( yMean - yStd < yDelay(i) && yDelay(i) < yMean + yStd)
		{
			delaySum = delaySum + yDelay(i);
			elementsCount++;
		}
	}

	// Estimate the frame shift by averaging.
	int delayEstimate = 0;
	if(elementsCount != 0)
	{
		delayEstimate = int( delaySum/elementsCount + 0.5);
	}

	return delayEstimate;
}

/**
*	Zero pads the matrix with the least frames.
*/

void ScoreProcessor::zeroPad( mat &inputSignal1, mat &inputSignal2 )
{
	// Calculate the difference in number of frames of two signals.
	int diffNumFrames = inputSignal1.n_rows - inputSignal2.n_rows;

	// Zero pad the shorter signal.
	if( 0 < diffNumFrames )
	{
		mat zeroMat = zeros(diffNumFrames,inputSignal1.n_cols);
		inputSignal2 = join_cols(inputSignal2, zeroMat);
	}
	else if( diffNumFrames < 0)
	{
		mat zeroMat = zeros( -diffNumFrames,inputSignal1.n_cols);
		inputSignal1 = join_cols(inputSignal1, zeroMat);	
	}
}

/**
*	Aligns the two signals and returns them in the two input matrices 
* passed by reference. The delay estimate is used as the number of 
* frames that they are out of sync. 
*/

void ScoreProcessor::align(Skeleton skeleton1, Skeleton skeleton2, int delayEstimate, mat &correctSignal1, mat &correctSignal2)
{
	mat inputSignal1 = skeleton1.getData();
	mat inputSignal2 = skeleton2.getData();
	// If delay is positive, shift the first signal and vice versa.
	if(0 < delayEstimate)
	{
		correctSignal1 = inputSignal1.rows(delayEstimate, inputSignal1.n_rows-1);
		correctSignal2 = inputSignal2;
	}
	else if(delayEstimate < 0)
	{
		correctSignal2 = inputSignal2.rows(-delayEstimate, inputSignal2.n_rows-1);
		correctSignal1 = inputSignal1;
	}
	else
	{
		correctSignal1 = inputSignal1;
		correctSignal2 = inputSignal2;
	}
}

/**
*	Returns the score of a whole matrix based on the score function. 
*/

mat ScoreProcessor::errorToScore(mat errorMat)
{
	mat score = -this->raiseToPower(2, 6.652410119*(0.3*errorMat+0.8))+140;

	for(int i = 0; i < score.n_rows; i++)
	{
		for(int j = 0; j < score.n_cols; j++)
		{
			if(score(i,j) < 0)
			{
				score(i,j) = 0;
			}
		}
	}

	return score;
}

/**
*	Returns the score of a single value based on the score function. 
*/

double ScoreProcessor::errorToScore(double errorMat)
{
	double score = -std::pow(2,6.652410119*(0.3*errorMat+0.8))+140;
	return (score > 0) ? score : 0;
}

mat ScoreProcessor::raiseToPower(double base, mat exponent)
{
	mat output(exponent.n_rows, exponent.n_cols);

	for(int i = 0; i < exponent.n_rows; i++)
	{
		for(int j = 0; j < exponent.n_cols; j++)
		{
			output.at(i,j) = std::pow(base,exponent.at(i,j));
		}
	}

	return output;
}

/**
*	Calculates the average total score. 
*/

void ScoreProcessor::calculateAvgTotalScore(void)
{
	this->avgTotalScore = mean(this->errorToScore(this->avgScoreWindowed).col(0));
}

/**
*	A wrapper function that can be used to set all the member variables. 
*/

void ScoreProcessor::analyse()
{
	int teachMotionless = this->motionlessFrameOverall(this->teacher, 30);
	int studeMotionless = this->motionlessFrameOverall(this->student,30);

	Skeleton teacherInterim = this->translate(this->teacher, teachMotionless, 1);
	Skeleton studentInterim = this->translate(this->student, studeMotionless, 0);

	int delayEstimate = this->delayEstimate(teacherInterim, studentInterim);

	mat teacherAligned, studentAligned;
	this->align(teacherInterim, studentInterim, delayEstimate, teacherAligned, studentAligned);
	teacherInterim.setData(teacherAligned);
	studentInterim.setData(studentAligned);

	rowvec errorArr(21);
	for(int delay = -10; delay < 11; delay++)
	{
		errorArr(delay+10) = this->calculateScore(teacherInterim, studentInterim, delay);
	}

	uword index;
	errorArr.min(index);
	index = index - 10;

	mat optTeacher, optStudent;
	this->align(teacherInterim, studentInterim, index, optTeacher, optStudent);
	this->alignedTeacher.setData(optTeacher);
	this->alignedStudent.setData(optStudent);

	this->coordinateScoreWindowed = this->calculateCoordinateScoreWindow(alignedTeacher, alignedStudent);
	this->jointScoreWindowed = this->calculateJointScoreWindow(this->coordinateScoreWindowed);
	this->avgScoreWindowed = this->calculateAvgScoreWindow(this->jointScoreWindowed);

	this->coordinateScoreWindowed = errorToScore(this->coordinateScoreWindowed);
	this->jointScoreWindowed = errorToScore(this->jointScoreWindowed);
	this->avgScoreWindowed = errorToScore(this->avgScoreWindowed);

	this->calculateAvgTotalScore();
	this->undoTranslate();
}