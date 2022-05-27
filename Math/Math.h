#pragma once


#include <cmath>
#include "Global.h"


inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


inline double Clamp(double x){
    return Clamp(x, 0.0, 1.0);
}

inline int DoubleToRGB8(double x){
    return int(std::pow(Clamp(x), 1.0/2.2) * 255 + 0.5);
}


inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

inline double RemapRange(double num, Range2d range){
    assert(range.left!=range.right);
    if(num>=range.right)
        return 1;
    if(num<=range.left)
        return 0;
    return (num - range.left) / (range.right - range.left);
}

inline void RemapColor(Color3d& color){
    //RGB重映射为灰度值
    auto grayScale = 0.299*color.r+0.587*color.g+0.114*color.b;

    grayScale = RemapRange(grayScale, Range2d(0.15,0.4));

    Color3d RGB;

    //灰度值重映射为热图
    if(grayScale <= 1.0 && grayScale>0.75){
        RGB.r = 1.0;
        RGB.g= 1.0 - RemapRange(grayScale, Range2d(0.75,1));
        RGB.b= 0;
    }else if(grayScale<=0.75 && grayScale > 0.5){
        RGB.r = RemapRange(grayScale, Range2d(0.5,0.75));
        RGB.g= 1.0;
        RGB.b= 0;
    }    else if(grayScale<=0.55 && grayScale > 0.25){
        RGB.r = 0;
        RGB.g= 1.0;
        RGB.b= 1.0 - RemapRange(grayScale, Range2d(0.25,0.5));
    }else if(grayScale <= 0.25 && grayScale >= 0.0){
        RGB.r = 0;
        RGB.g= RemapRange(grayScale, Range2d(0.0,0.25)) ;
        RGB.b= 1.0;
    }
    color = RGB;
}