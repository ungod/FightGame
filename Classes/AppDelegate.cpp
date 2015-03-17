#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "Scenes/Game/GameScene.h"
#include "SimpleAudioEngine.h"
#include "Config.h"


USING_NS_CC;
using namespace CocosDenshion;



AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// deal with path in different platforms
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	FileUtils::getInstance()->addSearchPath("maps");
	FileUtils::getInstance()->addSearchPath("cocosgui");
#endif
	Config::initConfig();

	FileUtils::getInstance()->addSearchPath("skill");

    // initialize director
    Director *pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    EGLView::getInstance()->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_HEIGHT);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
	Scene *pScene = GameScene::create(1);

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
