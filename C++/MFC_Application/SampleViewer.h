#ifndef _NITE_USER_VIEWER_H_
#define _NITE_USER_VIEWER_H_

#include "NiTE.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define MAX_DEPTH 10000

extern int userInput;
extern int OptionSelect;
extern int skeletonFrameIndex;
extern int skeletonMode ;
extern string userSkeletonDataFile_student_skeleton;
extern string userSkeletonDataFile_teacher_skeleton;
extern string userOniRecordingFile_student_skeleton;
extern string userOniRecordingFile_teacher_skeleton;
extern string userSkeletonDataFile_student_record;
extern string userOniRecordingFile_student_record;
extern string userOniRecordingFile_student_play;
extern string userSkeletonDataFile_teacher_overlay;
extern string userOniRecordingFile_student_overlay;
extern bool checkUserInput;
extern bool g_drawStudentSkeleton ;
extern bool g_drawTeacherSkeleton ;
extern bool g_drawLiveFrameId ;
extern bool g_drawRecordingCenterOfMass;
extern bool g_drawRecordingStatusLabel;
extern bool g_drawRecordingBackground;
extern bool g_drawRecordingDepth;
extern bool g_drawRecordingFrameId;
extern bool g_drawRecordingNameStream;
extern bool g_drawLiveStatusLabel;
extern bool g_drawLiveBackground;
extern bool g_drawLiveDepth;
extern bool g_drawLiveFrameId;
extern bool g_drawLiveNameStream;
extern bool g_startRecording;
extern bool g_stopRecording;
extern bool g_recordingInProgress;
extern bool g_rPressed;
extern bool g_pPressed;
extern bool g_pauseStream;
extern bool g_playStream;

struct jointData
{
	float x, y, z, confidence;
};

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

class SampleViewer
{

public:
	SampleViewer();
	virtual ~SampleViewer();

	virtual openni::Status Init(int argc, char **argv);
	
	void renderOpenGL(int OptionSelectLocal, bool &error);

	void Finalize();
	
private:
	/***/
	skeletonData m_skeletonDataObject_temp_storage[10];

	SampleViewer(const SampleViewer&);

	float				m_pLiveDepthHist[MAX_DEPTH];
	float				m_pRecordingDepthHist[MAX_DEPTH];

	openni::RGB888Pixel*		m_pLiveTexMap;
	unsigned int		m_nLiveTexMapX;
	unsigned int		m_nLiveTexMapY;

	openni::RGB888Pixel*		m_pRecordingTexMap;
	unsigned int		m_nRecordingTexMapX;
	unsigned int		m_nRecordingTexMapY;

	openni::Device		m_livedevice;
	openni::Device		m_recordingdevice;

	/***/
	openni::VideoStream m_videostream;
	//openni::VideoFrameRef m_frame;
	openni::Recorder m_recordingObject;
	openni::PlaybackControl* m_playbackControlObject;

	nite::UserTracker* m_pLiveUserTracker;
	nite::UserTracker* m_pRecordingUserTracker;

	nite::UserId m_LiveposeUser;
	nite::UserId m_RecordingposeUser;

	uint64_t m_LiveposeTime;
	uint64_t m_RecordingposeTime;

	virtual void DisplayLive(int OptionSelectLocal, bool &error);
	virtual void DisplayRecording(int OptionSelectLocal, bool &error);
	virtual void DisplaySkeleton(bool &error);
	virtual void DisplayOverlay(int OptionSelectLocal, bool &error);

	void writeSkeletonDataToStorage(const nite::UserData& userData);
	void writeSkeletonDataFromStorageToFile(const char* localUserTextFilename, int id);
	void clearSkeletonDataStorage(int id);
};

#endif // _NITE_USER_VIEWER_H_