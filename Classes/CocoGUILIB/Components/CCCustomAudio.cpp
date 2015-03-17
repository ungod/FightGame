/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCCustomAudio.h"
#include "SimpleAudioEngine.h"

NS_CC_EXT_BEGIN

CCCustomAudio::CCCustomAudio(void)
{
    _name = "Audio";
	m_bLoop = false;
}

CCCustomAudio::~CCCustomAudio(void)
{
    
}

bool CCCustomAudio::init()
{
    return true;
}

void CCCustomAudio::onEnter()
{
}

void CCCustomAudio::onExit()
{
    stopBackgroundMusic(true);
    stopAllEffects();
}

bool CCCustomAudio::isEnabled() const
{
    return _enabled;
}

void CCCustomAudio::setEnabled(bool b)
{
    _enabled = b;
}

CCCustomAudio* CCCustomAudio::create(void)
{
    CCCustomAudio * pRet = new CCCustomAudio();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void CCCustomAudio::end()
{
   CocosDenshion::SimpleAudioEngine::end();
}

void CCCustomAudio::preloadBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(pszFilePath);
}

void CCCustomAudio::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, bLoop);
}

void CCCustomAudio::playBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath);
}

void CCCustomAudio::stopBackgroundMusic(bool bReleaseData)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(bReleaseData);
}

void CCCustomAudio::stopBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void CCCustomAudio::pauseBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void CCCustomAudio::resumeBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void CCCustomAudio::rewindBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
}

bool CCCustomAudio::willPlayBackgroundMusic()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->willPlayBackgroundMusic();
}

bool CCCustomAudio::isBackgroundMusicPlaying()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

float CCCustomAudio::getBackgroundMusicVolume()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

void CCCustomAudio::setBackgroundMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

float CCCustomAudio::getEffectsVolume()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void CCCustomAudio::setEffectsVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

unsigned int CCCustomAudio::playEffect(const char* pszFilePath, bool bLoop)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, bLoop);
}

unsigned int CCCustomAudio::playEffect(const char* pszFilePath)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath);
}

void CCCustomAudio::pauseEffect(unsigned int nSoundId)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(nSoundId);
}

void CCCustomAudio::pauseAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void CCCustomAudio::resumeEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(nSoundId);
}

void CCCustomAudio::resumeAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void CCCustomAudio::stopEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(nSoundId);
}

void CCCustomAudio::stopAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void CCCustomAudio::preloadEffect(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(pszFilePath);
}

void CCCustomAudio::unloadEffect(const char *pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(pszFilePath);
}

void CCCustomAudio::setFile(const char* pszFilePath)
{
	m_strFilePath.assign(pszFilePath);
}

void CCCustomAudio::setLoop(bool bLoop)
{
	m_bLoop = bLoop;
}

const char* CCCustomAudio::getFile()
{
	return m_strFilePath.c_str();
}

bool CCCustomAudio::isLoop()
{
	return m_bLoop;
}

NS_CC_EXT_END
