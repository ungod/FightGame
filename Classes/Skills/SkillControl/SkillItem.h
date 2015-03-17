#pragma once
#include "cocos2d.h"
#include "../Skill.h"

USING_NS_CC;

/*
 技能按键
 
 */
class Skill;


class SkillItem : public MenuItemImage
{
public:
    SkillItem();
    ~SkillItem();

    /** Creates an MenuItemImage. */
    static SkillItem* create();
    /** creates a menu item with a normal and selected image*/
    static SkillItem* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static SkillItem* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with a callable object */
    static SkillItem* create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback);
    /** creates a menu item with a normal,selected  and disabled image with a callable object */
    static SkillItem* create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback);
    
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_strName, Name);//技能名称
    CC_SYNTHESIZE(float, m_skillCDTime, SkillCDTime); //冷却时间
    
    //为菜单设置技能
    virtual void setSkill(Skill* skill);
    virtual bool setSkill(string skillFile);
    virtual Skill* getSkill();
    
    
    //技能使用启动
    virtual void onSkillStarted();
    
    //技能使用完成
    virtual void onSkillFinished();
    
    virtual void onSkillCDFinished();//CD解冻

    void setEnableIcon(string icon);
    void setDisableIcon(string icon);
    
    string getEnableIcon(){return m_enableIcon;}
    string getDisableIcon(){return m_disableIcon;}
        
    
protected:
    Skill* m_skill;
    string m_enableIcon;
    string m_disableIcon;

};
