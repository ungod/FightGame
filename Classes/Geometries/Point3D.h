#pragma once
#include "cocos2d.h"
USING_NS_CC;


/*用来模拟角色3d行走的接口
 
 
 
 */




class Point3D
{
public:
    Point3D();

    
public:
    Point3D(float x, float y, float z);
    Point3D(const Point3D& other);
    Point3D& operator= (const Point3D& other);
    Point3D operator+(const Point3D& right) const;
    Point3D operator-(const Point3D& right) const;
    Point3D operator-() const;
    Point3D operator*(float a) const;
    Point3D operator/(float a) const;
    void setPoint(float x, float y, float z);
    bool equals(const Point3D& target) const;

    //static const Point3D ZERO;
public:
    float x;
    float y;
    float z;

};



Point3D Point3DFromString(const char* pszContent);


typedef struct
{
   float time;
   Point3D point;
}Point3DTime;


Point3DTime Point3DTimeFromString(const char* pszContent);
