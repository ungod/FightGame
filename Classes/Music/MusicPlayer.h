#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MusicInfo.h"
#include <map>
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

//ID and MusicInfo
typedef std::map<int, MusicInfo*> MusicMap;

class MusicPlayer : public Node
{
public:
    MusicPlayer();
    ~MusicPlayer();
    static MusicPlayer* getInstance();
    bool init();
    void end();
  
    
   void preloadEffect(int ID);
   void playEffect(int ID);//全功能
   
   void stopByMusicId(Integer* musicId);

    
    //@brief 播放器
   CC_SYNTHESIZE(SimpleAudioEngine*, m_player, Player);
private:
   MusicMap  m_musicMap;
   void play(MusicInfo* info);//没有延迟

};
