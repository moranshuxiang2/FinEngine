//
// Created by iFinVer on 2016/12/13.
//

#include "UnityTransfer.h"

UnityTransfer::UnityTransfer() {
    this->mUnityMsg = new UnityMsg();
}

void UnityTransfer::setTransferByUnity(UnityTransfer::Transfer transfer) {
    this->mTransfer = transfer;
}

void UnityTransfer::transformToUnity(jbyte *yuvData, int width, int height, int degree,jboolean mirror) {
    //宽高改变时重新初始化
    if(mUnityMsg->uvPtr == nullptr || mUnityMsg->width != width || mUnityMsg->height != height){
        mUnityMsg->width = width;
        mUnityMsg->height = height;
        if(mUnityMsg->uvPtr != nullptr){
            delete[] mUnityMsg->uvPtr;
        }
        mUnityMsg->uvPtr = new unsigned char[width * height * 3 / 4];
    }
    //处理uv通道
    int yLen = width * height;
    int yuvLen =yLen * 3 / 2;
    int dstPtr = 0;
    for (int i = yLen; i < yuvLen; i += 2) {
        mUnityMsg->uvPtr[dstPtr++] = (unsigned char) (yuvData[i] & 0xFF);
        mUnityMsg->uvPtr[dstPtr++] = (unsigned char) (yuvData[i + 1] & 0xFF);
        mUnityMsg->uvPtr[dstPtr++] = 0;
    }
    //y通道赋值
    mUnityMsg->yPtr = yuvData;
    //旋转角度
    mUnityMsg->degree = degree;
    //翻转控制
//    mUnityMsg->mirror = mirror ? 1 : 0;
    //传送给Unity
    transform();
}



