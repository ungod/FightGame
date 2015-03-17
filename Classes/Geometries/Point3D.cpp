#include "Point3D.h"


//const Point3D Point3D::ZERO = Point3D(0, 0, 0);

Point3D::Point3D(void) : x(0), y(0),z(0)
{
}

Point3D::Point3D(float xx, float yy, float zz) : x(xx), y(yy), z(zz)
{
}

Point3D::Point3D(const Point3D& other) : x(other.x), y(other.y), z(other.z)
{
}


Point3D& Point3D::operator= (const Point3D& other)
{
    setPoint(other.x, other.y, other.z);
    return *this;
}



Point3D Point3D::operator+(const Point3D& right) const
{
    return Point3D(this->x + right.x, this->y + right.y, this->z + right.z);
}

Point3D Point3D::operator-(const Point3D& right) const
{
    return Point3D(this->x - right.x, this->y - right.y, this->z - right.z);
}

Point3D Point3D::operator-() const
{
	return Point3D(-x, -y, -z);
}

Point3D Point3D::operator*(float a) const
{
    return Point3D(this->x * a, this->y * a, this->z * a);
}

Point3D Point3D::operator/(float a) const
{
	CCASSERT(a!=0, "CCPoint3D division by 0.");
    return Point3D(this->x / a, this->y / a, this->z / a);
}

void Point3D::setPoint(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Point3D::equals(const Point3D& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
    && (fabs(this->y - target.y) < FLT_EPSILON
    && (fabs(this->z - target.z) < FLT_EPSILON) );
}





typedef std::vector<std::string> strArray;

// string toolkit
static inline void split(std::string src, const char* token, strArray& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
static bool splitWithForm(const char* pStr, strArray& strs)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!pStr);
        
        // string is empty
        std::string content = pStr;
        CC_BREAK_IF(content.length() == 0);
        
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        
        // don't have '{' and '}'
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        // '}' is before '{'
        CC_BREAK_IF(nPosLeft > nPosRight);
        
        std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        CC_BREAK_IF(pointStr.length() == 0);
        
        int nPos1 = pointStr.find('{');
        int nPos2 = pointStr.find('}');
        // contain '{' or '}'
        CC_BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);
        
        split(pointStr, ",", strs);
//        if (strs.size() != 3 || strs[0].length() == 0 || strs[1].length() == 0  || strs[2].length() == 0)
//        {
//            strs.clear();
//            break;
//        }
        
        bRet = true;
    } while (0);
    
    return bRet;
}


Point3D Point3DFromString(const char* pszContent)
{
    Point3D ret = Point3D(0,0,0);
    
    do
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));
        
       if (strs.size() != 3 || strs[0].length() == 0 || strs[1].length() == 0  || strs[2].length() == 0)
        {
            strs.clear();
            break;
        }
        
        float x = (float) atof(strs[0].c_str());
        float y = (float) atof(strs[1].c_str());
        float z = (float) atof(strs[2].c_str());
        ret = Point3D(x, y ,z);
    } while (0);
    
    return ret;
}



Point3DTime Point3DTimeFromString(const char* pszContent)
{
    Point3DTime result = {0, Point3D(0,0,0)};
    
    do
    {
        CC_BREAK_IF(!pszContent);
        std::string content = pszContent;
        
        // find the first '{' and the third '}'
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        for (int i = 1; i < 3; ++i)
        {
            if (nPosRight == (int)std::string::npos)
            {
                break;
            }
            nPosRight = content.find('}', nPosRight + 1);
        }
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        
        content = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        int nPointEnd = content.find('}');
        CC_BREAK_IF(nPointEnd == (int)std::string::npos);
        nPointEnd = content.find(',', nPointEnd);
        CC_BREAK_IF(nPointEnd == (int)std::string::npos);
        
        // get the point string and size string
        std::string timeStr = content.substr(0, nPointEnd);
        std::string pointStr  = content.substr(nPointEnd + 1, content.length() - nPointEnd);
        
        // split the string with ','
        strArray timeInfo;
        CC_BREAK_IF(!splitWithForm(timeStr.c_str(), timeInfo));
        if (timeInfo.size() != 1 || timeInfo[0].length() == 0)
        {
            timeInfo.clear();
            break;
        }
        
        
        strArray pointInfo;
        CC_BREAK_IF(!splitWithForm(pointStr.c_str(), pointInfo));
        if (pointInfo.size() != 3 || pointInfo[0].length() == 0 || pointInfo[1].length() == 0  || pointInfo[2].length() == 0)
        {
            pointInfo.clear();
            break;
        }
        
        float time = (float) atof(timeInfo[0].c_str());
        float x = (float) atof(pointInfo[0].c_str());
        float y = (float) atof(pointInfo[1].c_str());
        float z = (float) atof(pointInfo[2].c_str());
        
        result.time = time;
        result.point = Point3D(x, y, z);
    } while (0);
    
    return result;
}




