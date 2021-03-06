#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
class FaceSwapper
{
public:
    // Initialize face swapped with landmarks
    FaceSwapper();
    ~FaceSwapper();

    //Swaps faces in rects on frame
    void swapFaces(cv::Mat frame, cv::Rect2i rect_ann, cv::Rect2i rect_bob, vector<cv::Point2i> vector1, vector<cv::Point2i> vector2);

private:
    // Returns minimal Mat containing both faces
    cv::Mat getMinFrame(cv::Mat frame, cv::Rect2i rect_ann, cv::Rect2i rect_bob, vector<cv::Point2i> vector1, vector<cv::Point2i> vector2);

    // Finds facial landmarks on faces and extracts the useful points
    void getFacePoints(const cv::Mat &frame);

    // Calculates transformation matrices based on points extracted by getFacePoints
    void getTransformationMatrices();

    // Creates masks for faces based on the points extracted in getFacePoints
    void getMasks();

    // Creates warpped masks out of masks created in getMasks to switch places
    void getWarppedMasks();

    // Returns Mat of refined mask such that warpped mask isn't bigger than original mask
    cv::Mat getRefinedMasks();

    // Extracts faces from images based on masks created in getMasks
    void extractFaces();

    // Creates warpped faces out of faces extracted in extractFaces
    cv::Mat getWarppedFaces();

    // Matches Ann face color to Bob face color and vice versa
    void colorCorrectFaces();

    // Blurs edges of mask
    void featherMask(const cv::Mat &refined_masks);

    // Pastes faces on original frame
    void pasteFacesOnFrame();

    // Calculates source image histogram and changes target_image to match source hist
    void specifiyHistogram(const cv::Mat source_image, cv::Mat target_image, cv::Mat mask);

    cv::Rect rect_ann, rect_bob;
    cv::Rect big_rect_ann, big_rect_bob;

    cv::Point2f affine_transform_keypoints_ann[3], affine_transform_keypoints_bob[3];

    cv::Mat refined_ann_and_bob_warpped, refined_bob_and_ann_warpped;
    cv::Mat warpped_face_ann, warpped_face_bob;
    
    vector<cv::Point2i> points_ann, points_bob;
    cv::Mat trans_ann_to_bob, trans_bob_to_ann;
    cv::Mat mask_ann, mask_bob;
    cv::Mat warpped_mask_ann, warpped_mask_bob;
    cv::Mat refined_masks;
    cv::Mat face_ann, face_bob;
    cv::Mat warpped_faces;

    cv::Mat small_frame;

    cv::Size frame_size;

    cv::Size feather_amount;

    uint8_t LUT[3][256];
    int source_hist_int[3][256];
    int target_hist_int[3][256];
    float source_histogram[3][256];
    float target_histogram[3][256];
};

