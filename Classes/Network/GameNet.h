#pragma once
#include "cocos2d.h"
USING_NS_CC;

#ifndef  CF_OPEN_SOURCE
#define  CF_OPEN_SOURCE
#endif

#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/RakNetStatistics.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNet/RakNetTypes.h"
#include <thread>
#ifdef _WIN32
#include "RakNet/Kbhit.h"
#include "RakNet/WindowsIncludes.h" // Sleep
#else
#include "RakNet/Kbhit.h"
#include <unistd.h> // usleep
#endif
#include "RakNet/Gets.h"
#include "RakNet/RakSleep.h"

#if LIBCAT_SECURITY==1
#include "RakNet/SecureHandshake.h" // Include header for secure handshake
#endif



class GameNet
{
public:
    GameNet();
    ~GameNet();
    static GameNet* getInstance();
    void stopNet();
    
    void test();


   CC_SYNTHESIZE(std::string, m_serverIP, ServerIP);
   CC_SYNTHESIZE(int, m_serverPort, ServerPort);
   CC_SYNTHESIZE(std::thread*, m_thread, Thread);
    
  static bool m_netOnFlag;

};
