#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using std::string;

#define FULL_VERSION 1


/*
    TODO: Applies the oil painting effect on the original image:

    - for each pixel create an intensity histogram, and histograms for red,
      green and blue as specified in the assignment document
    - get the bin and value of the most common bin found in the intensity
      histogram
    - use the previous findings to calculate the color of a given pixel

    @param original_image    (in)  the original image
    @param radius            (in)  the search window for neighbourhood pixels
    @param levels            (in)  the amount of levels used in the oil
                                   painting effect algorithm
    @return                        the image with the effect applied
*/

cv::Mat getFilteredImage(const cv::Mat &original_image,
                         int radius,
                         int levels)
{

    cv::Mat output = cv::Mat::zeros(original_image.size(),
                                    original_image.type());


    return output;
}


/*
    TODO: Computes a binary mask for foreground segmentation in the specified
    location:

    - convert the original image into the HSV color space using CV_BGR2HSV
    - use the value of H and the given threshold to create the binary
      foreground mask in the specified location
    - use dilation to expand the mask, for the structuring element use
      cv::MORPH_ELLIPSE and dilation_size

    @param original_image        (in)  the original image
    @param location              (in)  the location bounding box where the 
                                       segmentation needs to be performed
    @param threshold             (in)  threshold for the H channel used during
                                       the segmentation
    @return                            a binary mask where a logic 1 represents
                                       the foreground, while a logic 0
                                       represents the background
*/

cv::Mat getForegroundMask(const cv::Mat &original_image,
                          const cv::Rect &location,
                          int threshold,
                          int dilation_size)
{
    cv::Mat foreground_mask = cv::Mat::zeros(original_image.size(), CV_8UC1);


    return foreground_mask;
}


/*
    TODO: Combines the oil-painted image and the original image using the
    foreground segmentation mask:

    - combine the filtered image and the original image using the
      foreground mask
    - for the combined image: if a pixel in the foreground mask is set to 1
      use the original image, otherwise use the filtered image

    @param original_image         (in) the original image
    @param filtered_image         (in) the filtered image
    @param foreground_mask        (in) the binary segmentation mask
    @return                       the combined image
*/

cv::Mat combineImages(const cv::Mat &original_image,
                      const cv::Mat &filtered_image,
                      const cv::Mat &foreground_mask)
{
    cv::Mat output = cv::Mat::zeros(original_image.size(),
                                    original_image.type());


    return output;
}

/*
    Prints the usage message to std::cout. Do not change!
    @return always 1
*/
int readme()
{
    std::cout << "Usage: ./cvtask1a <config-file>" << std::endl;
    return 1;
}

/*
    Framework main method. Do not change!
    @return program status
*/
int main(int argc, char** argv)
{
    // DO NOT REMOVE THIS LINE!!!
    std::cout << "CV/task1a framework version 1.0" << std::endl;
    if (argc != 2)
        return readme();

    try
    {

    rapidjson::Document cfg;
    FILE* fp = fopen(argv[1], "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    cfg.ParseStream(is);
    assert(cfg.IsObject());

    //param parsing
    string input_path = cfg["input_path"].GetString();
    string output_path = cfg["output_path"].GetString();
    int radius = cfg["radius"].GetInt();
    int levels = cfg["levels"].GetInt();
    int threshold =  cfg["threshold"].GetInt();
    int dilation_size =  cfg["dilation_size"].GetInt();
    int label_x = cfg["label_x"].GetInt();
    int label_y = cfg["label_y"].GetInt();
    int label_width = cfg["label_width"].GetInt();
    int label_height = cfg["label_height"].GetInt();

#if defined(_WIN32)
    _mkdir("./output/");
    _mkdir(output_path.c_str());
#else
     mkdir("./output/", 0777);
     mkdir(output_path.c_str(),0777);
#endif

     std::cout << "Running TC: " << argv[1] << std::endl;

     cv::Mat original_image = cv::imread(input_path, CV_LOAD_IMAGE_COLOR);
     cv::Mat foreground_mask =  getForegroundMask(original_image,
                                              cv::Rect(label_x,
                                                       label_y,
                                                       label_width,
                                                       label_height),
                                              threshold,
                                              dilation_size);

     cv::Mat filtered_image = getFilteredImage(original_image,
                                               radius,
                                               levels);

     cv::Mat final_image = combineImages(original_image,
                                     filtered_image,
                                     foreground_mask);

     cv::imwrite(output_path + "filtered.png", filtered_image);
     cv::imwrite(output_path + "mask.png", foreground_mask * 255);
     cv::imwrite(output_path + "final.png", final_image);


    }
    catch (std::exception &ex)
    {
        std::cout << "An exception occured:" << std::endl;
        std::cout << ex.what() << std::endl;
        return -2;
    }
    return 0;
}

