#include <GL\glut.h>
#include "SampleViewer.h"


#define GL_WIN_SIZE_X	1280
#define GL_WIN_SIZE_Y	1024
#define GL_WIN_LOCATION_X 0
#define GL_WIN_LOCATION_Y 0
#define TEXTURE_SIZE	512

#define DEFAULT_DISPLAY_MODE	DISPLAY_MODE_DEPTH

#define MIN_NUM_CHUNKS(data_size, chunk_size)	((((data_size)-1) / (chunk_size) + 1))
#define MIN_CHUNKS_SIZE(data_size, chunk_size)	(MIN_NUM_CHUNKS(data_size, chunk_size) * (chunk_size))

/***/

//struct jointData
//{
//	float x, y, z, confidence;
//};
//
//struct skeletonData
//{
//	vector<jointData> head;
//	vector<jointData> left_shoulder;
//	vector<jointData> left_elbow;
//	vector<jointData> left_foot;
//	vector<jointData> left_hand;
//	vector<jointData> left_knee;
//	vector<jointData> left_hip;
//	vector<jointData> neck;
//	vector<jointData> right_shoulder;
//	vector<jointData> right_elbow;
//	vector<jointData> right_foot;
//	vector<jointData> right_hand;
//	vector<jointData> right_knee;
//	vector<jointData> right_hip;
//	vector<jointData> torso;
// };
//
skeletonData skeletonDataObject_student;
skeletonData skeletonDataObject_teacher;
//skeletonData skeletonDataObject_temp_storage[10];

bool g_drawLiveStatusLabel = true;
bool g_drawLiveBackground = true;
bool g_drawLiveDepth = true;
bool g_drawLiveFrameId = true;
bool g_drawLiveNameStream = true;

bool g_drawRecordingCenterOfMass = false;
bool g_drawRecordingStatusLabel = true;
bool g_drawRecordingBackground = true;
bool g_drawRecordingDepth = true;
bool g_drawRecordingFrameId = true;
bool g_drawRecordingNameStream = true;

bool g_drawStudentSkeleton = true;
bool g_drawTeacherSkeleton = true;

bool g_startRecording = true;
bool g_stopRecording = false;
bool g_recordingInProgress = false;

bool g_rPressed = false;
bool g_pPressed = true;

float centreCoordinates_student[3] = {0};
float centreCoordinates_teacher[3] = {0};

bool calculatedCentreCoordinatesSkeleton_student = false;
bool calculatedCentreCoordinatesSkeleton_teacher = false;

// Standard Mode => 0, Side-by-Side mode => 1, Overlay Mode => 2
int skeletonMode = 1;

int noLinesSkeletonDataFile_student = 0;
int noLinesSkeletonDataFile_teacher = 0;

int liveWindow = 0;
int recordingWindow = 1;
int skeletonWindow = 2;

int skeletonFrameIndex = 1;

int numberOfFramesInRecording = 0;

int g_nLiveXRes = 0, g_nLiveYRes = 0, g_nRecordingXRes = 0, g_nRecordingYRes = 0, g_nSkeletonXRes = 0, g_nSkeletonYRes = 0;

void SampleViewer::renderOpenGL(int OptionSelectLocal, bool &error)
{
	if (OptionSelectLocal == 0)
	{
		this->DisplayLive(0, error);
		return;
	}
	else if (OptionSelectLocal == 1)
	{
		this->DisplayRecording(1, error);
		return;
	}
	else if (OptionSelectLocal == 2)
	{
		this->DisplaySkeleton(error);
		return;
	}
	else if (OptionSelectLocal == 3) 
	{
		this->DisplayOverlay(1, error);
		return;
	}
}

SampleViewer::SampleViewer() : m_LiveposeUser(0), m_RecordingposeUser(0)
{
}

SampleViewer::~SampleViewer()
{
	Finalize();
	delete[] m_pLiveTexMap;
	delete[] m_pRecordingTexMap;
}

void SampleViewer::Finalize()
{
	g_drawLiveStatusLabel = true;
	g_drawLiveBackground = true;
	g_drawLiveDepth = true;
	g_drawLiveFrameId = true;
	g_drawLiveNameStream = true;

	g_drawRecordingCenterOfMass = false;
	g_drawRecordingStatusLabel = true;
	g_drawRecordingBackground = true;
	g_drawRecordingDepth = true;
	g_drawRecordingFrameId = true;
	g_drawRecordingNameStream = true;

	g_drawStudentSkeleton = true;
	g_drawTeacherSkeleton = true;

	g_startRecording = true;
	g_stopRecording = false;
	g_recordingInProgress = false;

	g_rPressed = false;
	g_pPressed = true;

	skeletonMode = 1;
	noLinesSkeletonDataFile_teacher = 0;
	noLinesSkeletonDataFile_student = 0;
	calculatedCentreCoordinatesSkeleton_teacher = false;
	calculatedCentreCoordinatesSkeleton_student = false;

	/***/
	/*m_videostream.stop();
	m_videostream.destroy();*/

	delete m_pLiveUserTracker;
	delete m_pRecordingUserTracker;
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
}

string convertIntegerToString(int integer)
{
   stringstream ss;
   ss << integer;
   return ss.str();
}

void writeSkeletonDataFile(const nite::UserData& userData, const char* localUserTextFilename)
{
	ofstream fOut;
	fOut.open(localUserTextFilename, ios::app);
	fOut << userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_NECK).getPositionConfidence() << " "
		 << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().x << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().y << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().z << " " << userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPositionConfidence() << endl;
	fOut.close();
}

/***/
void SampleViewer::writeSkeletonDataToStorage(const nite::UserData& userData)
{
	int id = userData.getId();
	if (id <= 10)
	{
		jointData temp;

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_HEAD).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].head.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_shoulder.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_elbow.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_shoulder.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_elbow.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_hand.push_back(temp);
	
		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_hand.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_TORSO).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].torso.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_hip.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_hip.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_knee.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].left_foot.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_knee.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_NECK).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_NECK).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].neck.push_back(temp);

		temp.x = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().x;
		temp.y = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().y;
		temp.z = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPosition().z;
		temp.confidence = userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT).getPositionConfidence();
		m_skeletonDataObject_temp_storage[id-1].right_foot.push_back(temp);
	}
}

/***/
void SampleViewer::writeSkeletonDataFromStorageToFile(const char* localUserTextFilename, int id)
{
	ofstream fOut;
	fOut.open(localUserTextFilename);
	
	for (int it = 0; it < m_skeletonDataObject_temp_storage[id-1].head.size(); it++)
	{
		fOut << m_skeletonDataObject_temp_storage[id-1].head.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].head.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].head.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].head.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_shoulder.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_shoulder.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_shoulder.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_shoulder.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_elbow.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_elbow.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_elbow.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_elbow.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_shoulder.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_shoulder.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_shoulder.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_shoulder.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_elbow.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_elbow.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_elbow.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_elbow.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_hand.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_hand.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_hand.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_hand.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_hand.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_hand.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_hand.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_hand.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].torso.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].torso.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].torso.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].torso.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_hip.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_hip.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_hip.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_hip.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_hip.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_hip.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_hip.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_hip.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_knee.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_knee.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_knee.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_knee.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].left_foot.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].left_foot.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].left_foot.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].left_foot.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_knee.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_knee.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_knee.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_knee.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].neck.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].neck.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].neck.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].neck.at(it).confidence << " "
		 << m_skeletonDataObject_temp_storage[id-1].right_foot.at(it).x << " " << m_skeletonDataObject_temp_storage[id-1].right_foot.at(it).y << " " << m_skeletonDataObject_temp_storage[id-1].right_foot.at(it).z << " " << m_skeletonDataObject_temp_storage[id-1].right_foot.at(it).confidence << endl;
	}
	fOut.close();
}

/***/
void SampleViewer::clearSkeletonDataStorage(int id)
{
	if (m_skeletonDataObject_temp_storage[id].head.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].head.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_shoulder.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_shoulder.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_shoulder.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_shoulder.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_elbow.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_elbow.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_elbow.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_elbow.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_hand.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_hand.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_hand.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_hand.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].torso.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].torso.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_hip.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_hip.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_hip.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_hip.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_knee.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_knee.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_knee.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_knee.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].left_foot.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].left_foot.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].right_foot.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].right_foot.clear();
	}
	if (m_skeletonDataObject_temp_storage[id].neck.size() > 0)
	{
		m_skeletonDataObject_temp_storage[id].neck.clear();
	}
	return;
}

void readSkeletonDataFile(const char*inputSkeletonDataFile_first, int whichFile)
{
	cout << endl;
	if (whichFile == 0)
	{
		ifstream fInp;
		float tempx, tempy, tempz, tempc;
		jointData tempj;
		fInp.open(inputSkeletonDataFile_first);
		int a = 0;
		if(fInp.is_open() == true)
		{
			while(!fInp.eof())
			{
				fInp >> tempx >> tempy >> tempz >> tempc;
				tempj.x = tempx;
				tempj.y = tempy;
				tempj.z = tempz;
				tempj.confidence = tempc;
				switch(a%15)
				{
				case 0:
					skeletonDataObject_student.head.push_back(tempj);
					break;
				case 1:
					skeletonDataObject_student.left_shoulder.push_back(tempj);
					break;
				case 2:
					skeletonDataObject_student.left_elbow.push_back(tempj);
					break;
				case 3:
					skeletonDataObject_student.right_shoulder.push_back(tempj);
					break;
				case 4:
					skeletonDataObject_student.right_elbow.push_back(tempj);
					break;
				case 5:
					skeletonDataObject_student.left_hand.push_back(tempj);
					break;
				case 6:
					skeletonDataObject_student.right_hand.push_back(tempj);
					break;
				case 7:
					skeletonDataObject_student.torso.push_back(tempj);
					break;
				case 8:
					skeletonDataObject_student.left_hip.push_back(tempj);
					break;
				case 9:
					skeletonDataObject_student.right_hip.push_back(tempj);
					break;
				case 10:
					skeletonDataObject_student.left_knee.push_back(tempj);
					break;
				case 11:
					skeletonDataObject_student.left_foot.push_back(tempj);
					break;
				case 12:
					skeletonDataObject_student.right_knee.push_back(tempj);
					break;
				case 13:
					skeletonDataObject_student.neck.push_back(tempj);
					break;
				case 14:
					skeletonDataObject_student.right_foot.push_back(tempj);
					break;
				}
				a++;
				noLinesSkeletonDataFile_student++;
			}
			noLinesSkeletonDataFile_student = noLinesSkeletonDataFile_student / 15;
			fInp.close();
		}
		else
		{
		}
	}
	else if (whichFile == 1)
	{
		ifstream fInp;
		float tempx, tempy, tempz, tempc;
		jointData tempj;
		fInp.open(inputSkeletonDataFile_first);
		int a = 0;
		if(fInp.is_open() == true)
		{
			while(!fInp.eof())
			{
				fInp >> tempx >> tempy >> tempz >> tempc;
				tempj.x = tempx;
				tempj.y = tempy;
				tempj.z = tempz;
				tempj.confidence = tempc;
				switch(a%15)
				{
				case 0:
					skeletonDataObject_teacher.head.push_back(tempj);
					break;
				case 1:
					skeletonDataObject_teacher.left_shoulder.push_back(tempj);
					break;
				case 2:
					skeletonDataObject_teacher.left_elbow.push_back(tempj);
					break;
				case 3:
					skeletonDataObject_teacher.right_shoulder.push_back(tempj);
					break;
				case 4:
					skeletonDataObject_teacher.right_elbow.push_back(tempj);
					break;
				case 5:
					skeletonDataObject_teacher.left_hand.push_back(tempj);
					break;
				case 6:
					skeletonDataObject_teacher.right_hand.push_back(tempj);
					break;
				case 7:
					skeletonDataObject_teacher.torso.push_back(tempj);
					break;
				case 8:
					skeletonDataObject_teacher.left_hip.push_back(tempj);
					break;
				case 9:
					skeletonDataObject_teacher.right_hip.push_back(tempj);
					break;
				case 10:
					skeletonDataObject_teacher.left_knee.push_back(tempj);
					break;
				case 11:
					skeletonDataObject_teacher.left_foot.push_back(tempj);
					break;
				case 12:
					skeletonDataObject_teacher.right_knee.push_back(tempj);
					break;
				case 13:
					skeletonDataObject_teacher.neck.push_back(tempj);
					break;
				case 14:
					skeletonDataObject_teacher.right_foot.push_back(tempj);
					break;
				}
				a++;
				noLinesSkeletonDataFile_teacher++;
			}
			noLinesSkeletonDataFile_teacher = noLinesSkeletonDataFile_teacher / 15;
			fInp.close();
		}
		else
		{
		}
	}
}

void calculateCentreSkeleton(nite::UserTracker* pUserTracker, int whichSkeleton, int frameIndex, float& centreCoordinatesX, float& centreCoordinatesY, float& centreCoordinatesZ)
{
	// calculate centre of skeleton for student and teacher for their starting position with frame index = 0
	if (whichSkeleton == 0)
	{
		int i = 0;
		
		float coordinates[30] = {0};
		float xSum = 0, ySum = 0;

		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.head[i].x, skeletonDataObject_student.head[i].y, skeletonDataObject_student.head[i].z, &coordinates[0], &coordinates[1]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_shoulder[i].x, skeletonDataObject_student.left_shoulder[i].y, skeletonDataObject_student.left_shoulder[i].z, &coordinates[2], &coordinates[3]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_elbow[i].x, skeletonDataObject_student.left_elbow[i].y, skeletonDataObject_student.left_elbow[i].z, &coordinates[4], &coordinates[5]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_foot[i].x, skeletonDataObject_student.left_foot[i].y, skeletonDataObject_student.left_foot[i].z, &coordinates[6], &coordinates[7]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_hand[i].x, skeletonDataObject_student.left_hand[i].y, skeletonDataObject_student.left_hand[i].z, &coordinates[8], &coordinates[9]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_knee[i].x, skeletonDataObject_student.left_knee[i].y, skeletonDataObject_student.left_knee[i].z, &coordinates[10], &coordinates[11]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.left_hip[i].x, skeletonDataObject_student.left_hip[i].y, skeletonDataObject_student.left_hip[i].z, &coordinates[12], &coordinates[13]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.neck[i].x, skeletonDataObject_student.neck[i].y, skeletonDataObject_student.neck[i].z, &coordinates[14], &coordinates[15]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_shoulder[i].x, skeletonDataObject_student.right_shoulder[i].y, skeletonDataObject_student.right_shoulder[i].z, &coordinates[16], &coordinates[17]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_elbow[i].x, skeletonDataObject_student.right_elbow[i].y, skeletonDataObject_student.right_elbow[i].z, &coordinates[18], &coordinates[19]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_foot[i].x, skeletonDataObject_student.right_foot[i].y, skeletonDataObject_student.right_foot[i].z, &coordinates[20], &coordinates[21]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_hand[i].x, skeletonDataObject_student.right_hand[i].y, skeletonDataObject_student.right_hand[i].z, &coordinates[22], &coordinates[23]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_knee[i].x, skeletonDataObject_student.right_knee[i].y, skeletonDataObject_student.right_knee[i].z, &coordinates[24], &coordinates[25]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.right_hip[i].x, skeletonDataObject_student.right_hip[i].y, skeletonDataObject_student.right_hip[i].z, &coordinates[26], &coordinates[27]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_student.torso[i].x, skeletonDataObject_student.torso[i].y, skeletonDataObject_student.torso[i].z, &coordinates[28], &coordinates[29]);

		for (int j = 0; j < 30; j++)
		{
			if (j%2 == 0)
			{
				xSum += coordinates[j];
			}
			else if (j%2 == 1)
			{
				ySum += coordinates[j];
			}
		}

		centreCoordinatesX = xSum * GL_WIN_SIZE_X / g_nSkeletonXRes / 15;
		centreCoordinatesY = ySum * GL_WIN_SIZE_Y / g_nSkeletonYRes / 15;
		centreCoordinatesZ = 0.0;
	}
	else if (whichSkeleton == 1)
	{
		int i = 0;

		float coordinates[30] = {0};
		float xSum = 0, ySum = 0;

		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.head[i].x, skeletonDataObject_teacher.head[i].y, skeletonDataObject_teacher.head[i].z, &coordinates[0], &coordinates[1]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_shoulder[i].x, skeletonDataObject_teacher.left_shoulder[i].y, skeletonDataObject_teacher.left_shoulder[i].z, &coordinates[2], &coordinates[3]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_elbow[i].x, skeletonDataObject_teacher.left_elbow[i].y, skeletonDataObject_teacher.left_elbow[i].z, &coordinates[4], &coordinates[5]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_foot[i].x, skeletonDataObject_teacher.left_foot[i].y, skeletonDataObject_teacher.left_foot[i].z, &coordinates[6], &coordinates[7]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_hand[i].x, skeletonDataObject_teacher.left_hand[i].y, skeletonDataObject_teacher.left_hand[i].z, &coordinates[8], &coordinates[9]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_knee[i].x, skeletonDataObject_teacher.left_knee[i].y, skeletonDataObject_teacher.left_knee[i].z, &coordinates[10], &coordinates[11]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.left_hip[i].x, skeletonDataObject_teacher.left_hip[i].y, skeletonDataObject_teacher.left_hip[i].z, &coordinates[12], &coordinates[13]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.neck[i].x, skeletonDataObject_teacher.neck[i].y, skeletonDataObject_teacher.neck[i].z, &coordinates[14], &coordinates[15]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_shoulder[i].x, skeletonDataObject_teacher.right_shoulder[i].y, skeletonDataObject_teacher.right_shoulder[i].z, &coordinates[16], &coordinates[17]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_elbow[i].x, skeletonDataObject_teacher.right_elbow[i].y, skeletonDataObject_teacher.right_elbow[i].z, &coordinates[18], &coordinates[19]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_foot[i].x, skeletonDataObject_teacher.right_foot[i].y, skeletonDataObject_teacher.right_foot[i].z, &coordinates[20], &coordinates[21]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_hand[i].x, skeletonDataObject_teacher.right_hand[i].y, skeletonDataObject_teacher.right_hand[i].z, &coordinates[22], &coordinates[23]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_knee[i].x, skeletonDataObject_teacher.right_knee[i].y, skeletonDataObject_teacher.right_knee[i].z, &coordinates[24], &coordinates[25]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.right_hip[i].x, skeletonDataObject_teacher.right_hip[i].y, skeletonDataObject_teacher.right_hip[i].z, &coordinates[26], &coordinates[27]);
		pUserTracker->convertJointCoordinatesToDepth(skeletonDataObject_teacher.torso[i].x, skeletonDataObject_teacher.torso[i].y, skeletonDataObject_teacher.torso[i].z, &coordinates[28], &coordinates[29]);

		for (int j = 0; j < 30; j++)
		{
			if (j%2 == 0)
			{
				xSum += coordinates[j];
			}
			else if (j%2 == 1)
			{
				ySum += coordinates[j];
			}
		}

		centreCoordinatesX = xSum * GL_WIN_SIZE_X / g_nSkeletonXRes / 15;
		centreCoordinatesY = ySum * GL_WIN_SIZE_Y / g_nSkeletonYRes / 15;
		centreCoordinatesZ = 0.0;
	}
}

openni::Status SampleViewer::Init(int argc, char **argv)
{
	m_pLiveTexMap = NULL;
	m_pRecordingTexMap = NULL;

	m_pLiveUserTracker = new nite::UserTracker;
	m_pRecordingUserTracker = new nite::UserTracker;

	openni::Status rc = openni::OpenNI::initialize();
	if (rc != openni::STATUS_OK)
	{
		printf("Failed to initialize OpenNI\n%s\n", openni::OpenNI::getExtendedError());
		return rc;
	}

	const char* deviceUri = openni::ANY_DEVICE;
	for (int i = 1; i < argc-1; ++i)
	{
		if (strcmp(argv[i], "-device") == 0)
		{
			deviceUri = argv[i+1];
			break;
		}
	}

	nite::NiTE::initialize();

	if (OptionSelect == 0)
	{
		// open and check live device
		openni::Status rc5 = m_livedevice.open(deviceUri);
		if (rc5 != openni::STATUS_OK)
		{
			printf("Failed to open device\n%s\n", openni::OpenNI::getExtendedError());
			return rc5;
		}

		nite::Status rc_nite = m_pLiveUserTracker->create(&m_livedevice);
		if (rc_nite != nite::STATUS_OK)
		{
			return openni::STATUS_ERROR;
		}

		for (int i = 0; i < 10; i++)
		{
			clearSkeletonDataStorage(i);
		}

		/***/
		/*openni::SensorType sensorTypeForRecording = openni::SENSOR_DEPTH;
		if (m_livedevice.hasSensor(sensorTypeForRecording) == true)
		{
			openni::Status rc = m_videostream.create(m_livedevice, sensorTypeForRecording);
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to create video stream\n%s\n", openni::OpenNI::getExtendedError());
				return rc;
			}
		}

		openni::Status rc = m_videostream.start();
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to start video stream\n%s\n", openni::OpenNI::getExtendedError());
			return rc;
		}

		const char* newRecordingFilePath = userOniRecordingFile_student_record.c_str();
		openni::Status rc2 = m_recordingObject.create(newRecordingFilePath);
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to create recorder\n%s\n", openni::OpenNI::getExtendedError());
			return rc2;
		}
		
		openni::Status rc3 = m_recordingObject.attach(m_videostream);
		if (rc3 != openni::STATUS_OK)
		{
			printf("Failed to attach recorder to stream\n%s\n", openni::OpenNI::getExtendedError());
			return rc3;
		}*/
	}
	else if (OptionSelect == 1)
	{
		// open and check recording device
		string oniUserFilename = userOniRecordingFile_student_play;
		const char* recordingFilePath = oniUserFilename.c_str();
		openni::Status rc2 = m_recordingdevice.open(recordingFilePath);
		if (rc2 != openni::STATUS_OK)
		{
			printf("Failed to open device\n%s\n", openni::OpenNI::getExtendedError());
			return rc2;
		}

		openni::SensorType sensorTypeForRecording = openni::SENSOR_DEPTH;
		if (m_recordingdevice.getSensorInfo(sensorTypeForRecording) != NULL)
		{
			openni::Status rc = m_videostream.create(m_recordingdevice, sensorTypeForRecording);
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to create video stream\n%s\n", openni::OpenNI::getExtendedError());
				return rc;
			}
		}

		openni::Status rc3 = m_videostream.start();
		if (rc3 != openni::STATUS_OK)
		{
			printf("Failed to start video stream\n%s\n", openni::OpenNI::getExtendedError());
			return rc3;
		}

		//openni::PlaybackControl* playbackControlObject = m_recordingdevice.getPlaybackControl();
		m_playbackControlObject = m_recordingdevice.getPlaybackControl();
		numberOfFramesInRecording = m_playbackControlObject->getNumberOfFrames(m_videostream);

		nite::Status rc_nite = m_pRecordingUserTracker->create(&m_recordingdevice);
		if (rc_nite != nite::STATUS_OK)
		{
			return openni::STATUS_ERROR;
		}
	}
	else if (OptionSelect == 2)
	{
		// open and check recording device
		
		string oniUserFilename = userOniRecordingFile_student_skeleton;
		const char* recordingFilePath = oniUserFilename.c_str();
		rc = m_recordingdevice.open(recordingFilePath);
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to open device\n%s\n", openni::OpenNI::getExtendedError());
			return rc;
		}

		nite::Status rc_nite = m_pRecordingUserTracker->create(&m_recordingdevice);
		if (rc_nite != nite::STATUS_OK)
		{
			return openni::STATUS_ERROR;
		}

		// read skeleton data (generated by the intial recording) from the data text file
		const char* skeletonDataFile_student = userSkeletonDataFile_student_skeleton.c_str();
		readSkeletonDataFile(skeletonDataFile_student, 0);

		// read skeleton data (generated by the intial recording) from the data text file
		const char* skeletonDataFile_teacher = userSkeletonDataFile_teacher_skeleton.c_str();
		readSkeletonDataFile(skeletonDataFile_teacher, 1);
	}
	else if (OptionSelect == 3)
	{
		// open and check recording device
		string oniUserFilename = userOniRecordingFile_student_overlay;
		const char* recordingFilePath = oniUserFilename.c_str();
		rc = m_recordingdevice.open(recordingFilePath);

		openni::SensorType sensorTypeForRecording = openni::SENSOR_DEPTH;
		if (m_recordingdevice.getSensorInfo(sensorTypeForRecording) != NULL)
		{
			openni::Status rc = m_videostream.create(m_recordingdevice, sensorTypeForRecording);
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to create video stream\n%s\n", openni::OpenNI::getExtendedError());
				return rc;
			}
		}

		openni::Status rc = m_videostream.start();
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to start video stream\n%s\n", openni::OpenNI::getExtendedError());
			return rc;
		}

		//openni::PlaybackControl* playbackControlObject = m_recordingdevice.getPlaybackControl();
		m_playbackControlObject = m_recordingdevice.getPlaybackControl();
		numberOfFramesInRecording = m_playbackControlObject->getNumberOfFrames(m_videostream);

		if (rc != openni::STATUS_OK)
		{
			printf("Failed to open device\n%s\n", openni::OpenNI::getExtendedError());
			return rc;
		}

		nite::Status rc_nite = m_pRecordingUserTracker->create(&m_recordingdevice);
		if (rc_nite != nite::STATUS_OK)
		{
			return openni::STATUS_ERROR;
		}

		// read skeleton data (generated by the intial recording) from the data text file
		const char* skeletonDataFile_teacher = userSkeletonDataFile_teacher_overlay.c_str();
		readSkeletonDataFile(skeletonDataFile_teacher, 1);
	}
	return rc;
}

// 0 => Red, 1 => Green, 2 => Blue, 3 => Yellow, 4 => Cyan, 5 => Violet, 6 => White, 7 => Black
float RecordedColors[][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 0}};

float Colors[][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 1}};
int colorCount = 3;

#define MAX_USERS 10
bool g_visibleLiveUsers[MAX_USERS] = {false};
bool g_visibleRecordingUsers[MAX_USERS] = {false};
nite::SkeletonState g_skeletonLiveStates[MAX_USERS] = {nite::SKELETON_NONE};
nite::SkeletonState g_skeletonRecordingStates[MAX_USERS] = {nite::SKELETON_NONE};
char g_userLiveStatusLabels[MAX_USERS][100] = {{0}};
char g_userRecordingStatusLabels[MAX_USERS][100] = {{0}};

char g_generalMessage[100] = {0};

#define USER_MESSAGE_LIVE(msg) {\
	sprintf_s(g_userLiveStatusLabels[user.getId()],"%s", msg);\
	printf("[%08llu] Live User #%d:\t%s\n",ts, user.getId(),msg);}

#define USER_MESSAGE_RECORDING(msg) {\
	sprintf_s(g_userRecordingStatusLabels[user.getId()],"%s", msg);\
	printf("[%08llu] Recording User #%d:\t%s\n",ts, user.getId(),msg);}

void updateLiveUserState(const nite::UserData& user, uint64_t ts)
{
	if (user.isNew())
	{
		USER_MESSAGE_LIVE("New");
	}
	else if (user.isVisible() && !g_visibleLiveUsers[user.getId()])
		printf("[%08llu] Live User #%d:\tVisible\n", ts, user.getId());
	else if (!user.isVisible() && g_visibleLiveUsers[user.getId()])
		printf("[%08llu] Live User #%d:\tOut of Scene\n", ts, user.getId());
	else if (user.isLost())
	{
		USER_MESSAGE_LIVE("Lost");
	}
	g_visibleLiveUsers[user.getId()] = user.isVisible();

	if (g_skeletonLiveStates[user.getId()] != user.getSkeleton().getState())
	{
		switch(g_skeletonLiveStates[user.getId()] = user.getSkeleton().getState())
		{
		case nite::SKELETON_NONE:
			USER_MESSAGE_LIVE("Stopped tracking.")
			break;
		case nite::SKELETON_CALIBRATING:
			USER_MESSAGE_LIVE("Calibrating...")
			break;
		case nite::SKELETON_TRACKED:
			USER_MESSAGE_LIVE("Tracking!")
			break;
		case nite::SKELETON_CALIBRATION_ERROR_NOT_IN_POSE:
		case nite::SKELETON_CALIBRATION_ERROR_HANDS:
		case nite::SKELETON_CALIBRATION_ERROR_LEGS:
		case nite::SKELETON_CALIBRATION_ERROR_HEAD:
		case nite::SKELETON_CALIBRATION_ERROR_TORSO:
			USER_MESSAGE_LIVE("Calibration Failed... :-|")
			break;
		}
	}
}

void updateRecordingUserState(const nite::UserData& user, uint64_t ts)
{
	if (user.isNew())
	{
		USER_MESSAGE_RECORDING("New");
	}
	else if (user.isVisible() && !g_visibleRecordingUsers[user.getId()])
		printf("[%08llu] Recording User #%d:\tVisible\n", ts, user.getId());
	else if (!user.isVisible() && g_visibleRecordingUsers[user.getId()])
		printf("[%08llu] Recording User #%d:\tOut of Scene\n", ts, user.getId());
	else if (user.isLost())
	{
		USER_MESSAGE_RECORDING("Lost");
	}

	g_visibleRecordingUsers[user.getId()] = user.isVisible();

	if(g_skeletonRecordingStates[user.getId()] != user.getSkeleton().getState())
	{
		switch(g_skeletonRecordingStates[user.getId()] = user.getSkeleton().getState())
		{
		case nite::SKELETON_NONE:
			USER_MESSAGE_RECORDING("Stopped tracking.")
			break;
		case nite::SKELETON_CALIBRATING:
			USER_MESSAGE_RECORDING("Calibrating...")
			break;
		case nite::SKELETON_TRACKED:
			USER_MESSAGE_RECORDING("Tracking!")
			break;
		case nite::SKELETON_CALIBRATION_ERROR_NOT_IN_POSE:
		case nite::SKELETON_CALIBRATION_ERROR_HANDS:
		case nite::SKELETON_CALIBRATION_ERROR_LEGS:
		case nite::SKELETON_CALIBRATION_ERROR_HEAD:
		case nite::SKELETON_CALIBRATION_ERROR_TORSO:
			USER_MESSAGE_RECORDING("Calibration Failed... :-|")
			break;
		}
	}
}

#ifndef USE_GLES
void glPrintString(void *font, const char *str)
{
	int i,l = (int)strlen(str);

	for(i=0; i<l; i++)
	{   
		glutBitmapCharacter(font,*str++);
	}   
}
#endif

void DrawStatusLabel(nite::UserTracker* pUserTracker, const nite::UserData& user, int OptionSelectLocal)
{
	int color = user.getId() % colorCount;
	glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);

	float x,y;
	pUserTracker->convertJointCoordinatesToDepth(user.getCenterOfMass().x, user.getCenterOfMass().y, user.getCenterOfMass().z, &x, &y);

	if (OptionSelectLocal == 0)
	{
		x *= GL_WIN_SIZE_X/g_nLiveXRes;
		y *= GL_WIN_SIZE_Y/g_nLiveYRes;
		char *msg = g_userLiveStatusLabels[user.getId()];
		glRasterPos2i(x-((strlen(msg)/2)*8),y);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
	if (OptionSelectLocal == 1)
	{
		x *= GL_WIN_SIZE_X/g_nRecordingXRes;
		y *= GL_WIN_SIZE_Y/g_nRecordingYRes;
		char *msg = g_userRecordingStatusLabels[user.getId()];
		glRasterPos2i(x-((strlen(msg)/2)*8),y);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
}

void DrawNameStream(int OptionSelectLocal)
{
	if (OptionSelectLocal == 0)
	{
		char buffer[40] = "Streaming Live Content...";
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2i(500, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
	}
	if (OptionSelectLocal == 1)
	{
		char buffer[40] = "Streaming Recorded Content...";
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2i(500, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
	}
}

void DrawFrameId(int frameId)
{
	char buffer[80] = "";
	sprintf_s(buffer, "%d", frameId);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(20, 20);
	glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
}

void DrawNameSkeleton(int LiveOrRecordingLocal)
{
	if (LiveOrRecordingLocal == 0)
	{
		char buffer[40] = "Showing Student Skeleton...";
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2i(200, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
	}
	if (LiveOrRecordingLocal == 1)
	{
		char buffer[40] = "Showing Teacher Skeleton...";
		glColor3f(1.0f, 0.0f, 1.0f);
		glRasterPos2i(840, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
	}
}

void DrawSkeletonMode(int skeletonMode)
{
	if (skeletonMode%3 == 0)
	{
		char buffer[80] = "standard mode";
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2i(520, 25);
		glPrintString(GLUT_BITMAP_TIMES_ROMAN_24, buffer);
	}
	else if (skeletonMode%3 == 1)
	{
		char buffer[80] = "side-by-side mode";
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2i(520, 25);
		glPrintString(GLUT_BITMAP_TIMES_ROMAN_24, buffer);
	}
	else if (skeletonMode%3 == 2)
	{
		char buffer[80] = "overlay mode";
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2i(520, 25);
		glPrintString(GLUT_BITMAP_TIMES_ROMAN_24, buffer);
	}
}

void DrawRecordingLabel()
{
	char buffer[80] = "Recording...";
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(1040, 20);
	glPrintString(GLUT_BITMAP_HELVETICA_18, buffer);
}

void DrawCenterOfMass(nite::UserTracker* pUserTracker, const nite::UserData& user, int OptionSelectLocal)
{
	glColor3f(1.0f, 1.0f, 1.0f);

	float coordinates[3] = {0};

	pUserTracker->convertJointCoordinatesToDepth(user.getCenterOfMass().x, user.getCenterOfMass().y, user.getCenterOfMass().z, &coordinates[0], &coordinates[1]);

	if (OptionSelectLocal == 0)
	{
		coordinates[0] *= GL_WIN_SIZE_X/g_nLiveXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nLiveYRes;
	}
	if (OptionSelectLocal == 1)
	{
		coordinates[0] *= GL_WIN_SIZE_X/g_nRecordingXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nRecordingYRes;
	}

	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex3f(coordinates[0], coordinates[1], coordinates[2]);
	glEnd();
}

void DrawRecordedLimb(nite::UserTracker* pUserTracker, jointData joint1, jointData joint2, int color, int whichSkeleton, int frameIndex)
{
	if (whichSkeleton == 0)
	{
		float coordinates[6] = {0};
		pUserTracker->convertJointCoordinatesToDepth(joint1.x, joint1.y, joint1.z, &coordinates[0], &coordinates[1]);
		pUserTracker->convertJointCoordinatesToDepth(joint2.x, joint2.y, joint2.z, &coordinates[3], &coordinates[4]);
		
		if (!calculatedCentreCoordinatesSkeleton_student)
		{
			calculateCentreSkeleton(pUserTracker, whichSkeleton, frameIndex, centreCoordinates_student[0], centreCoordinates_student[1], centreCoordinates_student[2]);
			calculatedCentreCoordinatesSkeleton_student = true;
		}

		float translatedCoordinates[6] = {0};
		float newOrigin[3] = {0};

		coordinates[0] *= GL_WIN_SIZE_X/g_nSkeletonXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nSkeletonYRes;
		coordinates[2] = 0;
		coordinates[3] *= GL_WIN_SIZE_X/g_nSkeletonXRes;
		coordinates[4] *= GL_WIN_SIZE_Y/g_nSkeletonYRes;
		coordinates[5] = 0;


		// side-by-side mode
		if (skeletonMode%3 == 1)
		{
			newOrigin[0] = GL_WIN_SIZE_X/4;
			newOrigin[1] = 	GL_WIN_SIZE_Y/2;
			newOrigin[2] = 	0.0;
		}
		// overlay mode
		else if (skeletonMode%3 == 2)
		{
			newOrigin[0] = GL_WIN_SIZE_X/2;
			newOrigin[1] = 	GL_WIN_SIZE_Y/2;
			newOrigin[2] = 	0.0;
		}

		if (skeletonMode%3 != 0)
		{
			// translated coordiantes for joint1
			translatedCoordinates[0] = coordinates[0] - centreCoordinates_student[0] + newOrigin[0];
			translatedCoordinates[1] = coordinates[1] - centreCoordinates_student[1] + newOrigin[1];
			translatedCoordinates[2] = coordinates[2] - centreCoordinates_student[2] + newOrigin[2];
			// translated coordiantes for joint2
			translatedCoordinates[3] = coordinates[3] - centreCoordinates_student[0] + newOrigin[0];
			translatedCoordinates[4] = coordinates[4] - centreCoordinates_student[1] + newOrigin[1];
			translatedCoordinates[5] = coordinates[5] - centreCoordinates_student[2] + newOrigin[2];
		}
		else
		{
			translatedCoordinates[0] = coordinates[0];
			translatedCoordinates[1] = coordinates[1];
			translatedCoordinates[2] = coordinates[2];
			translatedCoordinates[3] = coordinates[3];
			translatedCoordinates[4] = coordinates[4];
			translatedCoordinates[5] = coordinates[5];
		}
	
		glPointSize(3);
		glBegin(GL_LINES);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[0], translatedCoordinates[1], translatedCoordinates[2]);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[3], translatedCoordinates[4], translatedCoordinates[5]);
		glEnd();
		
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[0], translatedCoordinates[1], translatedCoordinates[2]);
		glEnd();
	
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[3], translatedCoordinates[4], translatedCoordinates[5]);
		glEnd();
	}
	else if (whichSkeleton == 1)
	{
		float coordinates[6] = {0};
		pUserTracker->convertJointCoordinatesToDepth(joint1.x, joint1.y, joint1.z, &coordinates[0], &coordinates[1]);
		pUserTracker->convertJointCoordinatesToDepth(joint2.x, joint2.y, joint2.z, &coordinates[3], &coordinates[4]);

		if (!calculatedCentreCoordinatesSkeleton_teacher)
		{
			calculateCentreSkeleton(pUserTracker, whichSkeleton, frameIndex, centreCoordinates_teacher[0], centreCoordinates_teacher[1], centreCoordinates_teacher[2]);
			calculatedCentreCoordinatesSkeleton_teacher = true;
		}

		float translatedCoordinates[6] = {0};
		float newOrigin[3] = {0};
		
		coordinates[0] *= GL_WIN_SIZE_X/g_nSkeletonXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nSkeletonYRes;
		coordinates[2] = 0;
		coordinates[3] *= GL_WIN_SIZE_X/g_nSkeletonXRes;
		coordinates[4] *= GL_WIN_SIZE_Y/g_nSkeletonYRes;
		coordinates[5] = 0;

		// side-by-side mode
		if (skeletonMode%3 == 1)
		{
			newOrigin[0] = (3*GL_WIN_SIZE_X/4);
			newOrigin[1] = 	GL_WIN_SIZE_Y/2;
			newOrigin[2] = 	0.0;
		}
		// overlay mode
		else if (skeletonMode%3 == 2)
		{
			newOrigin[0] = GL_WIN_SIZE_X/2;
			newOrigin[1] = 	GL_WIN_SIZE_Y/2;
			newOrigin[2] = 	0.0;
		}

		if (skeletonMode%3 != 0)
		{
			// translated coordiantes for joint1
			translatedCoordinates[0] = coordinates[0] - centreCoordinates_teacher[0] + newOrigin[0];
			translatedCoordinates[1] = coordinates[1] - centreCoordinates_teacher[1] + newOrigin[1];
			translatedCoordinates[2] = coordinates[2] - centreCoordinates_teacher[2] + newOrigin[2];
			// translated coordiantes for joint2
			translatedCoordinates[3] = coordinates[3] - centreCoordinates_teacher[0] + newOrigin[0];
			translatedCoordinates[4] = coordinates[4] - centreCoordinates_teacher[1] + newOrigin[1];
			translatedCoordinates[5] = coordinates[5] - centreCoordinates_teacher[2] + newOrigin[2];
		}
		else
		{
			translatedCoordinates[0] = coordinates[0];
			translatedCoordinates[1] = coordinates[1];
			translatedCoordinates[2] = coordinates[2];
			translatedCoordinates[3] = coordinates[3];
			translatedCoordinates[4] = coordinates[4];
			translatedCoordinates[5] = coordinates[5];
		}
	
		glPointSize(3);
		glBegin(GL_LINES);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[0], translatedCoordinates[1], translatedCoordinates[2]);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[3], translatedCoordinates[4], translatedCoordinates[5]);
		glEnd();
		
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[0], translatedCoordinates[1], translatedCoordinates[2]);
		glEnd();
	
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(RecordedColors[color][0], RecordedColors[color][1], RecordedColors[color][2]);
		glVertex3f(translatedCoordinates[3], translatedCoordinates[4], translatedCoordinates[5]);
		glEnd();
	}
}

void DrawRecordedSkeleton(nite::UserTracker* pUserTracker, int frameIndex, int whichSkeleton)
{
	if (whichSkeleton == 0)
	{
		// set colour to yellow
		int color = 3;
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.head[frameIndex], skeletonDataObject_student.neck[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_shoulder[frameIndex], skeletonDataObject_student.left_elbow[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_elbow[frameIndex], skeletonDataObject_student.left_hand[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.right_shoulder[frameIndex], skeletonDataObject_student.right_elbow[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.right_elbow[frameIndex], skeletonDataObject_student.right_hand[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_shoulder[frameIndex], skeletonDataObject_student.right_shoulder[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_shoulder[frameIndex], skeletonDataObject_student.torso[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.right_shoulder[frameIndex], skeletonDataObject_student.torso[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.torso[frameIndex], skeletonDataObject_student.left_hip[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.torso[frameIndex], skeletonDataObject_student.right_hip[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_hip[frameIndex], skeletonDataObject_student.right_hip[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_hip[frameIndex], skeletonDataObject_student.left_knee[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.left_knee[frameIndex], skeletonDataObject_student.left_foot[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.right_hip[frameIndex], skeletonDataObject_student.right_knee[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_student.right_knee[frameIndex], skeletonDataObject_student.right_foot[frameIndex], color, whichSkeleton, frameIndex);
	}
	else if (whichSkeleton == 1)
	{
		// set colour to violet
		int color = 5;
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.head[frameIndex], skeletonDataObject_teacher.neck[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_shoulder[frameIndex], skeletonDataObject_teacher.left_elbow[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_elbow[frameIndex], skeletonDataObject_teacher.left_hand[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.right_shoulder[frameIndex], skeletonDataObject_teacher.right_elbow[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.right_elbow[frameIndex], skeletonDataObject_teacher.right_hand[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_shoulder[frameIndex], skeletonDataObject_teacher.right_shoulder[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_shoulder[frameIndex], skeletonDataObject_teacher.torso[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.right_shoulder[frameIndex], skeletonDataObject_teacher.torso[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.torso[frameIndex], skeletonDataObject_teacher.left_hip[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.torso[frameIndex], skeletonDataObject_teacher.right_hip[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_hip[frameIndex], skeletonDataObject_teacher.right_hip[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_hip[frameIndex], skeletonDataObject_teacher.left_knee[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.left_knee[frameIndex], skeletonDataObject_teacher.left_foot[frameIndex], color, whichSkeleton, frameIndex);

		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.right_hip[frameIndex], skeletonDataObject_teacher.right_knee[frameIndex], color, whichSkeleton, frameIndex);
		DrawRecordedLimb(pUserTracker, skeletonDataObject_teacher.right_knee[frameIndex], skeletonDataObject_teacher.right_foot[frameIndex], color, whichSkeleton, frameIndex);
	}
}

void DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, int color, int OptionSelectLocal)
{
	float coordinates[6] = {0};
	pUserTracker->convertJointCoordinatesToDepth(joint1.getPosition().x, joint1.getPosition().y, joint1.getPosition().z, &coordinates[0], &coordinates[1]);
	pUserTracker->convertJointCoordinatesToDepth(joint2.getPosition().x, joint2.getPosition().y, joint2.getPosition().z, &coordinates[3], &coordinates[4]);

	if (OptionSelectLocal == 0)
	{
		coordinates[0] *= GL_WIN_SIZE_X/g_nLiveXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nLiveYRes;
		coordinates[3] *= GL_WIN_SIZE_X/g_nLiveXRes;
		coordinates[4] *= GL_WIN_SIZE_Y/g_nLiveYRes;

		glPointSize(3);
		glBegin(GL_LINES);
		if (joint1.getPositionConfidence() == 1 && joint2.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else if (joint1.getPositionConfidence() < 0.5f || joint2.getPositionConfidence() < 0.5f)
		{
			glEnd();
			return;
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[0], coordinates[1], coordinates[2]);
		glVertex3f(coordinates[3], coordinates[4], coordinates[5]);
		glEnd();

		glPointSize(10);
		glBegin(GL_POINTS);
		if (joint1.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[0], coordinates[1], coordinates[2]);
		glEnd();

		glPointSize(10);
		glBegin(GL_POINTS);
		if (joint2.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[3], coordinates[4], coordinates[5]);
		glEnd();
	}
	else if (OptionSelectLocal == 1)
	{
		coordinates[0] *= GL_WIN_SIZE_X/g_nRecordingXRes;
		coordinates[1] *= GL_WIN_SIZE_Y/g_nRecordingYRes;
		coordinates[3] *= GL_WIN_SIZE_X/g_nRecordingXRes;
		coordinates[4] *= GL_WIN_SIZE_Y/g_nRecordingYRes;
		
		glPointSize(3);
		glBegin(GL_LINES);
		if (joint1.getPositionConfidence() == 1 && joint2.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else if (joint1.getPositionConfidence() < 0.5f || joint2.getPositionConfidence() < 0.5f)
		{
			glEnd();
			return;
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[0], coordinates[1], coordinates[2]);
		glVertex3f(coordinates[3], coordinates[4], coordinates[5]);
		glEnd();

		glPointSize(10);
		glBegin(GL_POINTS);
		if (joint1.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[0], coordinates[1], coordinates[2]);
		glEnd();
		
		glPointSize(10);
		glBegin(GL_POINTS);
		if (joint2.getPositionConfidence() == 1)
		{
			glColor3f(1.0f - Colors[color][0], 1.0f - Colors[color][1], 1.0f - Colors[color][2]);
		}
		else
		{
			glColor3f(.5, .5, .5);
		}
		glVertex3f(coordinates[3], coordinates[4], coordinates[5]);
		glEnd();
	}
}

void DrawSkeleton(nite::UserTracker* pUserTracker, const nite::UserData& userData, int OptionSelectLocal)
{
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_HEAD), userData.getSkeleton().getJoint(nite::JOINT_NECK), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW), userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData.getId() % colorCount, OptionSelectLocal);


	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE), userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT), userData.getId() % colorCount, OptionSelectLocal);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE), userData.getId() % colorCount, OptionSelectLocal);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT), userData.getId() % colorCount, OptionSelectLocal);
}

void SampleViewer::DisplayLive(int OptionSelectLocal, bool &error)
{
	nite::UserTrackerFrameRef userLiveTrackerFrame;
	openni::VideoFrameRef depthLiveFrame;

	nite::Status rcLive = m_pLiveUserTracker->readFrame(&userLiveTrackerFrame);
	if (rcLive != nite::STATUS_OK)
	{
		error = true;
		return;
	}

	depthLiveFrame = userLiveTrackerFrame.getDepthFrame();

	if (m_pLiveTexMap == NULL)
	{
		m_nLiveTexMapX = MIN_CHUNKS_SIZE(depthLiveFrame.getVideoMode().getResolutionX(), TEXTURE_SIZE);
		m_nLiveTexMapY = MIN_CHUNKS_SIZE(depthLiveFrame.getVideoMode().getResolutionY(), TEXTURE_SIZE);
		m_pLiveTexMap = new openni::RGB888Pixel[m_nLiveTexMapX * m_nLiveTexMapY];
	}

	const nite::UserMap& userLiveLabels = userLiveTrackerFrame.getUserMap();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, GL_WIN_SIZE_X, GL_WIN_SIZE_Y, 0, -1.0, 1.0);

	if (depthLiveFrame.isValid() && g_drawLiveDepth)
	{
		const openni::DepthPixel* pDepth = (const openni::DepthPixel*)depthLiveFrame.getData();
		int width = depthLiveFrame.getWidth();
		int height = depthLiveFrame.getHeight();
		
		memset(m_pLiveDepthHist, 0, MAX_DEPTH*sizeof(float));
		int restOfRow = depthLiveFrame.getStrideInBytes() / sizeof(openni::DepthPixel) - width;

		unsigned int nNumberOfPoints = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x, ++pDepth)
			{
				if (*pDepth != 0)
				{
					m_pLiveDepthHist[*pDepth]++;
					nNumberOfPoints++;
				}
			}
			pDepth += restOfRow;
		}
		for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
		{
			m_pLiveDepthHist[nIndex] += m_pLiveDepthHist[nIndex-1];
		}
		if (nNumberOfPoints)
		{
			for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
			{
				m_pLiveDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (m_pLiveDepthHist[nIndex] / nNumberOfPoints)));
			}
		}
	}

	memset(m_pLiveTexMap, 0, m_nLiveTexMapX*m_nLiveTexMapY*sizeof(openni::RGB888Pixel));

	float factor[3] = {1, 1, 1};
	
	if (depthLiveFrame.isValid() && g_drawLiveDepth)
	{
		const nite::UserId* pLabels = userLiveLabels.getPixels();

		const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)depthLiveFrame.getData();
		openni::RGB888Pixel* pTexRow = m_pLiveTexMap + depthLiveFrame.getCropOriginY() * m_nLiveTexMapX;
		int rowSize = depthLiveFrame.getStrideInBytes() / sizeof(openni::DepthPixel);

		for (int y = 0; y < depthLiveFrame.getHeight(); ++y)
		{
			const openni::DepthPixel* pDepth = pDepthRow;
			openni::RGB888Pixel* pTex = pTexRow + depthLiveFrame.getCropOriginX();

			for (int x = 0; x < depthLiveFrame.getWidth(); ++x, ++pDepth, ++pTex, ++pLabels)
			{
				if (*pDepth != 0)
				{
					if (*pLabels == 0)
					{
						if (!g_drawLiveBackground)
						{
							factor[0] = factor[1] = factor[2] = 0;
						}
						else
						{
							factor[0] = Colors[colorCount][0];
							factor[1] = Colors[colorCount][1];
							factor[2] = Colors[colorCount][2];
						}
					}
					else
					{
						factor[0] = Colors[*pLabels % colorCount][0];
						factor[1] = Colors[*pLabels % colorCount][1];
						factor[2] = Colors[*pLabels % colorCount][2];
					}
					int nHistValue = m_pLiveDepthHist[*pDepth];
					pTex->r = nHistValue*factor[0];
					pTex->g = nHistValue*factor[1];
					pTex->b = nHistValue*factor[2];

					factor[0] = factor[1] = factor[2] = 1;
				}
			}
			pDepthRow += rowSize;
			pTexRow += m_nLiveTexMapX;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nLiveTexMapX, m_nLiveTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pLiveTexMap);

	// Display the OpenGL texture map for Live Stream
	glColor4f(1,1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	g_nLiveXRes = depthLiveFrame.getVideoMode().getResolutionX();
	g_nLiveYRes = depthLiveFrame.getVideoMode().getResolutionY();

	// upper left
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	// upper right
	glTexCoord2f((float)g_nLiveXRes/(float)m_nLiveTexMapX, 0);
	glVertex2f(GL_WIN_SIZE_X, 0);
	// bottom right
	glTexCoord2f((float)g_nLiveXRes/(float)m_nLiveTexMapX, (float)g_nLiveYRes/(float)m_nLiveTexMapY);
	glVertex2f(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	// bottom left
	glTexCoord2f(0, (float)g_nLiveYRes/(float)m_nLiveTexMapY);
	glVertex2f(0, GL_WIN_SIZE_Y);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	const nite::Array<nite::UserData>& users = userLiveTrackerFrame.getUsers();
	
	for (int i = 0; i < users.getSize(); ++i)
	{
		const nite::UserData& user = users[i];

		updateLiveUserState(user, userLiveTrackerFrame.getTimestamp());

		/***/ // subtract .txt from userSkeletonDataFile_student_record
		/*string userSkeletonDataFile_student_recordNoExtension(userSkeletonDataFile_student_record);
		userSkeletonDataFile_student_recordNoExtension.erase(userSkeletonDataFile_student_recordNoExtension.size()-4, 4);
		string appendUserToTextFilename = userSkeletonDataFile_student_recordNoExtension + "_user" + convertIntegerToString(user.getId()) + ".txt";
		const char* localUserTextFilename = appendUserToTextFilename.c_str();*/

		if (user.isNew())
		{
			m_pLiveUserTracker->startSkeletonTracking(user.getId());
		}
		else if (!user.isLost())
		{
			if (g_drawLiveStatusLabel)
			{
				DrawStatusLabel(m_pLiveUserTracker, user, OptionSelectLocal);
			}
			if (users[i].getSkeleton().getState() == nite::SKELETON_TRACKED)
			{
				if (g_drawStudentSkeleton == true)
				{
					DrawSkeleton(m_pLiveUserTracker, user, OptionSelectLocal);
				}
				if (g_recordingInProgress == true)
				{
					writeSkeletonDataToStorage(user);
					//writeSkeletonDataFile(user, localUserTextFilename);
				}
			}
		}
	}

	if (g_drawLiveFrameId)
	{
		DrawFrameId(userLiveTrackerFrame.getFrameIndex());
	}

	if (g_drawLiveNameStream)
	{
		DrawNameStream(OptionSelectLocal);
	}

	if (g_recordingInProgress == true)
	{
		DrawRecordingLabel();
	}
	
	if (g_startRecording == true && g_rPressed == true)
	{
		/***/
		openni::SensorType sensorTypeForRecording = openni::SENSOR_DEPTH;
		if (m_livedevice.hasSensor(sensorTypeForRecording) == true)
		{
			openni::Status rc = m_videostream.create(m_livedevice, sensorTypeForRecording);
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to create video stream\n%s\n", openni::OpenNI::getExtendedError());
				error = true;
				return;
			}
		}

		openni::Status rc = m_videostream.start();
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to start video stream\n%s\n", openni::OpenNI::getExtendedError());
			error = true;
			return;
		}

		const char* newRecordingFilePath = userOniRecordingFile_student_record.c_str();
		rc = m_recordingObject.create(newRecordingFilePath);
		if (rc != openni::STATUS_OK)
		{
			printf("Failed to create recorder\n%s\n", openni::OpenNI::getExtendedError());
			error = true;
			return;
		}

		if (m_recordingObject.isValid() == true)
		{
			rc = m_recordingObject.attach(m_videostream);
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to attach recorder to stream\n%s\n", openni::OpenNI::getExtendedError());
				error = true;
				return;
			}

			openni::Status rc = m_recordingObject.start();
			if (rc != openni::STATUS_OK)
			{
				printf("Failed to start recording\n%s\n", openni::OpenNI::getExtendedError());
				error = true;
				return;
			}

			g_startRecording = false;
			g_recordingInProgress = true;
		}
		else
		{
			error = true;
			return;
		}
	}

	if (g_stopRecording == true && g_recordingInProgress == true)
	{
		m_recordingObject.stop();
		m_recordingObject.destroy();
		/***/
		m_videostream.stop();
		m_videostream.destroy();
		g_recordingInProgress = false;
		g_stopRecording = false;
		g_rPressed = false;

		for (int i = 1; i <= 10; i++)
		{
			if (m_skeletonDataObject_temp_storage[i-1].head.size() > 0)
			{
				string userSkeletonDataFile_student_recordNoExtension(userSkeletonDataFile_student_record);
				userSkeletonDataFile_student_recordNoExtension.erase(userSkeletonDataFile_student_recordNoExtension.size()-4, 4);
				string appendUserToTextFilename = userSkeletonDataFile_student_recordNoExtension + "_user" + convertIntegerToString(i) + ".txt";
				const char* localUserTextFilename = appendUserToTextFilename.c_str();

				writeSkeletonDataFromStorageToFile(localUserTextFilename, i);
			}
		}
	}

	if (g_generalMessage[0] != '\0')
	{
		char *msg = g_generalMessage;
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2i(100, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
}

void SampleViewer::DisplayRecording(int OptionSelectLocal, bool &error)
{	
	nite::UserTrackerFrameRef userRecordingTrackerFrame;
	openni::VideoFrameRef depthRecordingFrame;

	nite::Status rcRecording = m_pRecordingUserTracker->readFrame(&userRecordingTrackerFrame);
	if (rcRecording != nite::STATUS_OK)
	{
		printf("GetNextData::Recording failed\n");
		error = true;
		return;
	}

	depthRecordingFrame = userRecordingTrackerFrame.getDepthFrame();

	if (m_pRecordingTexMap == NULL)
	{
		m_nRecordingTexMapX = MIN_CHUNKS_SIZE(depthRecordingFrame.getVideoMode().getResolutionX(), TEXTURE_SIZE);
		m_nRecordingTexMapY = MIN_CHUNKS_SIZE(depthRecordingFrame.getVideoMode().getResolutionY(), TEXTURE_SIZE);
		m_pRecordingTexMap = new openni::RGB888Pixel[m_nRecordingTexMapX * m_nRecordingTexMapY];
	}

	const nite::UserMap& userRecordingLabels = userRecordingTrackerFrame.getUserMap();


	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, GL_WIN_SIZE_X, GL_WIN_SIZE_Y, 0, -1.0, 1.0);

	if (depthRecordingFrame.isValid() && g_drawRecordingDepth)
	{
		const openni::DepthPixel* pDepth = (const openni::DepthPixel*)depthRecordingFrame.getData();
		int width = depthRecordingFrame.getWidth();
		int height = depthRecordingFrame.getHeight();

		memset(m_pRecordingDepthHist, 0, MAX_DEPTH*sizeof(float));
		int restOfRow = depthRecordingFrame.getStrideInBytes() / sizeof(openni::DepthPixel) - width;

		unsigned int nNumberOfPoints = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x, ++pDepth)
			{
				if (*pDepth != 0)
				{
					m_pRecordingDepthHist[*pDepth]++;
					nNumberOfPoints++;
				}
			}
			pDepth += restOfRow;
		}
		for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
		{
			m_pRecordingDepthHist[nIndex] += m_pRecordingDepthHist[nIndex-1];
		}
		if (nNumberOfPoints)
		{
			for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
			{
				m_pRecordingDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (m_pRecordingDepthHist[nIndex] / nNumberOfPoints)));
			}
		}
	}

	memset(m_pRecordingTexMap, 0, m_nRecordingTexMapX*m_nRecordingTexMapY*sizeof(openni::RGB888Pixel));

	float factor[3] = {1, 1, 1};

	if (depthRecordingFrame.isValid() && g_drawRecordingDepth)
	{
		const nite::UserId* pLabels = userRecordingLabels.getPixels();

		const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)depthRecordingFrame.getData();
		openni::RGB888Pixel* pTexRow = m_pRecordingTexMap + depthRecordingFrame.getCropOriginY() * m_nRecordingTexMapX;
		int rowSize = depthRecordingFrame.getStrideInBytes() / sizeof(openni::DepthPixel);

		for (int y = 0; y < depthRecordingFrame.getHeight(); ++y)
		{
			const openni::DepthPixel* pDepth = pDepthRow;
			openni::RGB888Pixel* pTex = pTexRow + depthRecordingFrame.getCropOriginX();

			for (int x = 0; x < depthRecordingFrame.getWidth(); ++x, ++pDepth, ++pTex, ++pLabels)
			{
				if (*pDepth != 0)
				{
					if (*pLabels == 0)
					{
						if (!g_drawRecordingBackground)
						{
							factor[0] = factor[1] = factor[2] = 0;
						}
						else
						{
							factor[0] = Colors[colorCount][0];
							factor[1] = Colors[colorCount][1];
							factor[2] = Colors[colorCount][2];
						}
					}
					else
					{
						factor[0] = Colors[*pLabels % colorCount][0];
						factor[1] = Colors[*pLabels % colorCount][1];
						factor[2] = Colors[*pLabels % colorCount][2];
					}
					int nHistValue = m_pRecordingDepthHist[*pDepth];
					pTex->r = nHistValue*factor[0];
					pTex->g = nHistValue*factor[1];
					pTex->b = nHistValue*factor[2];

					factor[0] = factor[1] = factor[2] = 1;
				}
			}
			pDepthRow += rowSize;
			pTexRow += m_nRecordingTexMapX;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nRecordingTexMapX, m_nRecordingTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pRecordingTexMap);

	// Display the OpenGL texture map for Recording Stream
	glColor4f(1,1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	g_nRecordingXRes = depthRecordingFrame.getVideoMode().getResolutionX();
	g_nRecordingYRes = depthRecordingFrame.getVideoMode().getResolutionY();

	// upper left
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	// upper right
	glTexCoord2f((float)g_nRecordingXRes/(float)m_nRecordingTexMapX, 0);
	glVertex2f(GL_WIN_SIZE_X, 0);
	// bottom right
	glTexCoord2f((float)g_nRecordingXRes/(float)m_nRecordingTexMapX, (float)g_nRecordingYRes/(float)m_nRecordingTexMapY);
	glVertex2f(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	// bottom left
	glTexCoord2f(0, (float)g_nRecordingYRes/(float)m_nRecordingTexMapY);
	glVertex2f(0, GL_WIN_SIZE_Y);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	
	const nite::Array<nite::UserData>& users = userRecordingTrackerFrame.getUsers();

	for (int i = 0; i < users.getSize(); ++i)
	{	
		const nite::UserData& user = users[i];

		updateRecordingUserState(user, userRecordingTrackerFrame.getTimestamp());
		if (user.isNew())
		{
			m_pRecordingUserTracker->startSkeletonTracking(user.getId());
			/***/
		}
		else if (!user.isLost())
		{
			if (g_drawRecordingStatusLabel)
			{
				DrawStatusLabel(m_pRecordingUserTracker, user, OptionSelectLocal);
			}
			if (g_drawRecordingCenterOfMass)
			{
				DrawCenterOfMass(m_pRecordingUserTracker, user, OptionSelectLocal);
			}

			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED && g_drawStudentSkeleton)
			{
				DrawSkeleton(m_pRecordingUserTracker, user, OptionSelectLocal);
			}
		}
	}

	if (g_drawRecordingFrameId)
	{
		DrawFrameId(userRecordingTrackerFrame.getFrameIndex());
	}

	if (g_drawRecordingNameStream)
	{
		DrawNameStream(OptionSelectLocal);
	}

	if (g_generalMessage[0] != '\0')
	{
		char *msg = g_generalMessage;
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2i(100, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
}

void SampleViewer::DisplaySkeleton(bool &error)
{
	nite::UserTrackerFrameRef userRecordingTrackerFrame;
	openni::VideoFrameRef depthRecordingFrame;

	nite::Status rcLive = m_pRecordingUserTracker->readFrame(&userRecordingTrackerFrame);
	if (rcLive != nite::STATUS_OK)
	{
		printf("GetNextData::Live failed\n");
		error = true;
		return;
	}

	depthRecordingFrame = userRecordingTrackerFrame.getDepthFrame();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, GL_WIN_SIZE_X, GL_WIN_SIZE_Y, 0, -1.0, 1.0);

	g_nSkeletonXRes = depthRecordingFrame.getVideoMode().getResolutionX();
	g_nSkeletonYRes = depthRecordingFrame.getVideoMode().getResolutionY();

	/***/
	//skeletonFrameIndex = userRecordingTrackerFrame.getFrameIndex();
	skeletonFrameIndex++;

	if (g_drawLiveFrameId)
	{
		DrawFrameId(skeletonFrameIndex);
	}

	if (g_drawStudentSkeleton && (skeletonFrameIndex-1 < noLinesSkeletonDataFile_student))
	{
		DrawRecordedSkeleton(m_pRecordingUserTracker, skeletonFrameIndex-1, 0);
	}

	if (g_drawLiveNameStream && (skeletonFrameIndex-1 < noLinesSkeletonDataFile_student))
	{
		DrawNameSkeleton(0);
	}

	if (g_drawTeacherSkeleton && (skeletonFrameIndex-1 < noLinesSkeletonDataFile_teacher))
	{
		DrawRecordedSkeleton(m_pRecordingUserTracker, skeletonFrameIndex-1, 1);
	}

	if (g_drawRecordingNameStream && (skeletonFrameIndex-1 < noLinesSkeletonDataFile_teacher))
	{
		DrawNameSkeleton(1);
	}

	DrawSkeletonMode(skeletonMode);

	if (!(skeletonFrameIndex-1 < noLinesSkeletonDataFile_teacher) && !(skeletonFrameIndex-1 < noLinesSkeletonDataFile_student))
	{
		skeletonFrameIndex = 0;
	}
	
	if (g_generalMessage[0] != '\0')
	{
		char *msg = g_generalMessage;
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2i(100, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
}

void SampleViewer::DisplayOverlay(int OptionSelectLocal, bool &error)
{	
	nite::UserTrackerFrameRef userRecordingTrackerFrame;
	openni::VideoFrameRef depthRecordingFrame;

	nite::Status rcRecording = m_pRecordingUserTracker->readFrame(&userRecordingTrackerFrame);
	if (rcRecording != nite::STATUS_OK)
	{
		printf("GetNextData::Recording failed\n");
		error = true;
		return;
	}

	depthRecordingFrame = userRecordingTrackerFrame.getDepthFrame();

	int frameIndex = depthRecordingFrame.getFrameIndex();

	if (m_pRecordingTexMap == NULL)
	{
		// Recording Texture map init
		m_nRecordingTexMapX = MIN_CHUNKS_SIZE(depthRecordingFrame.getVideoMode().getResolutionX(), TEXTURE_SIZE);
		m_nRecordingTexMapY = MIN_CHUNKS_SIZE(depthRecordingFrame.getVideoMode().getResolutionY(), TEXTURE_SIZE);
		m_pRecordingTexMap = new openni::RGB888Pixel[m_nRecordingTexMapX * m_nRecordingTexMapY];
	}

	const nite::UserMap& userRecordingLabels = userRecordingTrackerFrame.getUserMap();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, GL_WIN_SIZE_X, GL_WIN_SIZE_Y, 0, -1.0, 1.0);


	if (depthRecordingFrame.isValid() && g_drawRecordingDepth)
	{
		const openni::DepthPixel* pDepth = (const openni::DepthPixel*)depthRecordingFrame.getData();
		int width = depthRecordingFrame.getWidth();
		int height = depthRecordingFrame.getHeight();
		
		memset(m_pRecordingDepthHist, 0, MAX_DEPTH*sizeof(float));
		int restOfRow = depthRecordingFrame.getStrideInBytes() / sizeof(openni::DepthPixel) - width;

		unsigned int nNumberOfPoints = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x, ++pDepth)
			{
				if (*pDepth != 0)
				{
					m_pRecordingDepthHist[*pDepth]++;
					nNumberOfPoints++;
				}
			}
			pDepth += restOfRow;
		}
		for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
		{
			m_pRecordingDepthHist[nIndex] += m_pRecordingDepthHist[nIndex-1];
		}
		if (nNumberOfPoints)
		{
			for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
			{
				m_pRecordingDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (m_pRecordingDepthHist[nIndex] / nNumberOfPoints)));
			}
		}
	}

	memset(m_pRecordingTexMap, 0, m_nRecordingTexMapX*m_nRecordingTexMapY*sizeof(openni::RGB888Pixel));

	float factor[3] = {1, 1, 1};

	if (depthRecordingFrame.isValid() && g_drawRecordingDepth)
	{
		const nite::UserId* pLabels = userRecordingLabels.getPixels();

		const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)depthRecordingFrame.getData();
		openni::RGB888Pixel* pTexRow = m_pRecordingTexMap + depthRecordingFrame.getCropOriginY() * m_nRecordingTexMapX;
		int rowSize = depthRecordingFrame.getStrideInBytes() / sizeof(openni::DepthPixel);

		for (int y = 0; y < depthRecordingFrame.getHeight(); ++y)
		{
			const openni::DepthPixel* pDepth = pDepthRow;
			openni::RGB888Pixel* pTex = pTexRow + depthRecordingFrame.getCropOriginX();

			for (int x = 0; x < depthRecordingFrame.getWidth(); ++x, ++pDepth, ++pTex, ++pLabels)
			{
				if (*pDepth != 0)
				{
					if (*pLabels == 0)
					{
						if (!g_drawRecordingBackground)
						{
							factor[0] = factor[1] = factor[2] = 0;
						}
						else
						{
							factor[0] = Colors[colorCount][0];
							factor[1] = Colors[colorCount][1];
							factor[2] = Colors[colorCount][2];
						}
					}
					else
					{
						factor[0] = Colors[*pLabels % colorCount][0];
						factor[1] = Colors[*pLabels % colorCount][1];
						factor[2] = Colors[*pLabels % colorCount][2];
					}
					
					int nHistValue = m_pRecordingDepthHist[*pDepth];
					pTex->r = nHistValue*factor[0];
					pTex->g = nHistValue*factor[1];
					pTex->b = nHistValue*factor[2];

					factor[0] = factor[1] = factor[2] = 1;
				}
			}
			pDepthRow += rowSize;
			pTexRow += m_nRecordingTexMapX;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nRecordingTexMapX, m_nRecordingTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pRecordingTexMap);

	// Display the OpenGL texture map for Recording Stream
	glColor4f(1,1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	g_nRecordingXRes = depthRecordingFrame.getVideoMode().getResolutionX();
	g_nRecordingYRes = depthRecordingFrame.getVideoMode().getResolutionY();

	g_nSkeletonXRes = g_nRecordingXRes;
	g_nSkeletonYRes = g_nRecordingYRes;

	// upper left
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	// upper right
	glTexCoord2f((float)g_nRecordingXRes/(float)m_nRecordingTexMapX, 0);
	glVertex2f(GL_WIN_SIZE_X, 0);
	// bottom right
	glTexCoord2f((float)g_nRecordingXRes/(float)m_nRecordingTexMapX, (float)g_nRecordingYRes/(float)m_nRecordingTexMapY);
	glVertex2f(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	// bottom left
	glTexCoord2f(0, (float)g_nRecordingYRes/(float)m_nRecordingTexMapY);
	glVertex2f(0, GL_WIN_SIZE_Y);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	const nite::Array<nite::UserData>& users = userRecordingTrackerFrame.getUsers();

	for (int i = 0; i < users.getSize(); ++i)
	{
		const nite::UserData& user = users[i];

		updateRecordingUserState(user, userRecordingTrackerFrame.getTimestamp());

		if (user.isNew())
		{
			m_pRecordingUserTracker->startSkeletonTracking(user.getId());
			m_pRecordingUserTracker->startPoseDetection(user.getId(), nite::POSE_CROSSED_HANDS);
		}
		else if (!user.isLost())
		{
			if (g_drawRecordingStatusLabel)
			{
				DrawStatusLabel(m_pRecordingUserTracker, user, OptionSelectLocal);
			}
			if (g_drawRecordingCenterOfMass)
			{
				DrawCenterOfMass(m_pRecordingUserTracker, user, OptionSelectLocal);
			}

			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED && g_drawStudentSkeleton)
			{
				DrawSkeleton(m_pRecordingUserTracker, user, OptionSelectLocal);
			}
		}
	}

	if (g_drawTeacherSkeleton && (userRecordingTrackerFrame.getFrameIndex()-1 < noLinesSkeletonDataFile_teacher))
	{
		DrawRecordedSkeleton(m_pRecordingUserTracker, userRecordingTrackerFrame.getFrameIndex()-1, 1);
	}

	if (g_drawRecordingFrameId)
	{
		DrawFrameId(userRecordingTrackerFrame.getFrameIndex());
	}

	if (g_drawRecordingNameStream)
	{
		DrawNameStream(OptionSelectLocal);
	}

	if (g_generalMessage[0] != '\0')
	{
		char *msg = g_generalMessage;
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2i(100, 20);
		glPrintString(GLUT_BITMAP_HELVETICA_18, msg);
	}
}