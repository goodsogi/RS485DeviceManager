#ifndef WNAME_SPACE_BY_HSHAN
#define WNAME_SPACE_BY_HSHAN

/*
#include <qevent.h>
#include <qobject.h>
#include <qvaluelist.h> 
#include <qstring.h>
#include <qdatetime.h> 
*/
class Wall
{
public:

	// type of log
	enum LogType
	{	
		LOG_ERR		= 0x00000001,	// Log (critical)errors
		LOG_SOAP		= 0x00000002,	// Log warnings but not critical
		LOG_INF		= 0x00000004,	// Log informational events
		LOG_SRC		= 0x00000008,	// Log source level
		
		LOG_VDP		= 0x00000010,	// Log VDP specific
		LOG_UPNP		= 0x00000020,	// Log UPNP Specific
		LOG_TEST		= 0x00000040,	// Log Test (this code may be deleted later)
		LOG_SHT		= 0x00000080,	// Log SHT11

		//LOG_GUI= 0x00000100,	// Log GUI
		//LOG_BLF= 0x00000200,	// Log BLACKFIN
		//LOG_MSM= 0x00000400,	// Log MSM7731
		
		LOG_RFM 		= 0x00000100,   	// Log RF MODULE
		LOG_LG485 		= 0x00000200, 	// Log 엘지 [시스템 에어컨]
		LOG_HAMUN 		= 0x00000400,	// Log 하문 [시스템 에어컨]
		LOG_CON		= 0x00000800,	// Log Configure manager
		
		LOG_APP		= 0x00001000,	// Log Application specific
		LOG_Z256 		= 0x00002000,	// Log Z256 specific 
		LOG_FAT		= 0x00003000,	// Log Fatal error
		LOG_LNCP 		= 0x00004000,   	// Log LG Lncp
		LOG_RS485		= 0x00005000,  	// Log RS 485
		LOG_PRM		= 0x00006000,    	// Log PACKET ROUTER MANAGER
		LOG_PCM		= 0x00007000,    	// Log PACKET CONVERTER MANAGER
		LOG_MGR		= 0x00008000,    	// Log DEVICE DRIVER MANAGER

		LOG_HNA 		= 0x00010000, 	// 표준프로토콜
		LOG_SEND		= 0x00020000,	// Log warnings but not critical
		LOG_READ		= 0x00040000,	// Log informational events
		LOG_DOOR		= 0x00080000,	//Log SmartDoorPhone

		LOG_LED 		= 0x00100000,	// Log LED PANEL specific 
		LOG_EMS		= 0x00200000,	// Log EnergyMonitoring
		LOG_WEATHER	= 0x00400000,
		
		LOG_ZWAVE		= 0x02000000,	// Z-Wave		

		LOG_ALL		= 0x10000000,	// Log all informaton
		LOG_SEP		= 0x20000000,   	// Separator

	};

	// View top, bottom
	enum SideBar
	{
		Hide,
		View
	};

	// sound play request
	enum SndReq
	{
		SndIntro,
		SndOutro,
		SndBtn,
		SndBarUp,
		SndBarDown,
		SndBellPrivate,
		SndBellPublic,
		SndBellGuard,
		SndError,
		SndNotify,
		SndOk,
		SndCapture,
		SndTick,
		SndNone
	};

	enum SndUser
	{
		SndUserBtn1=0,
		SndUserBtn2,
		SndUserBtn3,
		SndUserBell1,
		SndUserBell2,
		SndUserNone
	};
	
	// Image Capture
	enum CapImageType
	{
		CapPrivate	= 0x01,	// 개별현관
		CapPublic	= 0x02,	// 공동현관
		CapDica		= 0x04,	// 디카
		CapSave		= 0x08,	// 저장 (리스트 추가 및 파일에 저장 시)
		CapByUser	= 0x10,	// 사용자에 의한 capture
		CapBySystem = 0x20  // 시스템에 의한 capture
	};

	enum JPEGScale
	{
		ScaleLarge	= 0,	// Jpeg size 640 x 480
		ScaleMedium,		// Jpeg size 320 x 240
		ScaleSmall			// Jpeg size 160 x 112
	};

	enum AudioPath
	{
		AudioAc97 = 1,
		AudioOki  = 2,
		AudioBt   = 3
	};

	enum AudioAmp
	{
		AudioOff  = 0,
		AudioOn	  = 1
	};


	enum ZvPath
	{
		ZvVideo	= 0,
		ZvDecoder
	};

	enum VideoSrc
	{
		VideoCmos = 1,
		VideoDoor = 2
	};

	enum ZvStatus
	{
		ZvOff = 0,
		ZvOn
	};

	enum Codec
	{
		DoNothing = 0,
		Encode,
		Decode
	};

	// capture 영상의 최대 저장 파일 과
	// 건 당 최대 저장 파일 수
	enum CapMax
	{
		VDPMaxCap			= 300,
		VDPMaxCapPerEvent	= 30,
		DicaMaxCap			= 300
	};

	// 방문자 / 디카 영상 앨범
	// VDP , Dica 영상을 하나의 앨범에서 보여주기때문에 프래그 구분이 필요하며
	// full 인지 thumbnail 인지 구분 하여야 한다.
	enum ViewAlbum
	{
		GroupImage	= 1,
		SingleImage	= 2,
		Thumbnail	= 4,
		Full		= 8
	};
	
	// 페이지 당 이미지 수
	enum AlbumImagesPerPage 
	{
		ThumbIpp	= 6,	// thumbname images per page
		FullIpp		= 1		// full image per page
	};
};


#endif //WNAME_SPACE_BY_HSHAN

