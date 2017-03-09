#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <iomanip>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <limits>
#include <map>
#include <math.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"


#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#define FULL_VERSION 1

/*
    Struct PathCost: describes a Path in an image
    std::vector<cv::Point2i> path: vector to store all Pixel coordinates P(y,x) of a Path
    int cost: the cost of the path
*/
typedef struct {
	std::vector<cv::Point2i> path;
	int cost = 0;
} PathCost;


/*
    TODO: Calculates the gradient magnitude for each pixel in an image:

    - convert the image into a grayscale image using CV_BGR2GRAY
    - use cv::Sobel to calculate a Sobel derivative image in x and 
      y direction.
    - Combine the Sobel derivatives to get the gradient magnitude matrix
      of the image. Assign it to abs_grad.

    @param image 	(in)   the image used to calculate the gradient magnitude
    @param abs_grad     (out)  the gradient magnitude matrix 
    @return             void    
*/
void calculateGradientMag(const cv::Mat &image, cv::Mat &abs_grad) {

	const int scale = 1;
	const int delta = 0;
	const int ddepth = CV_32FC1;

}

/*
    TODO: Calculates a vector of PathCost using the edge_costs image:

    - starting from row 1, find the minimum value in edge_cost below each pixel 
      in the pixel's Moore neighborhood
    - iterate over the cost_image rows rm_seam_count times and find the rm_seam_count minimum
      paths (= seams) and save them in vec_paths

    @param edge_costs 		(in)  image containing the cost of each pixel in the original image
    @param out_costImage	(out) image to store the normalized cost matrix (note that you should _not_ copy the infinity padding into this matrix!)
    @param rm_seam_count   	(in)  the number of PathCosts to compute
    @return             	a vector containing rm_seam_count number of PathCosts. Note that the vector should be sorted such that the 0th element should correspond
                         	to the path with lowest energy. Further, result[i].path should be ordered ascending by the y-coordinate such that result[i].path[0] should contain the coordinates
                            	for the 0th row, result[i].path[1] should contain the coordinates for the 1st row, ...
*/
std::vector<PathCost> calculateCostImage(const cv::Mat &edge_costs, cv::Mat &out_costImage, int rm_seam_count) {

    std::vector<PathCost> vec_paths;

    cv::Mat cost_image(edge_costs.rows, edge_costs.cols + 2, CV_32FC1, cv::Scalar::all(std::numeric_limits<float>::infinity()));
    cv::Mat prev_idx(edge_costs.rows, edge_costs.cols, CV_32SC1, cv::Scalar::all(-1));
    edge_costs.row(0).copyTo(cost_image.row(0).colRange(1, 1+edge_costs.cols));
    for (int row = 1; row < edge_costs.rows; row++)
    {
        for (int col = 0; col < edge_costs.cols; col++)
        {
        }
    }

	return vec_paths;
}


/*
    TODO: Highlights the calculated seams in an image:

    - iterate over the vector of PathCosts and color in every pixel in out_image
      the vector contains red

    @param vec_paths 		(in)  the vector containing all computed paths
    @param out_image    	(out) the image used to compute vec_paths before
    @param rm_seam_count  	(in)  the number of seams in vec_paths
    @return             	  void
*/
void highlightSeams(const std::vector<PathCost> &vec_paths, cv::Mat &out_image, int rm_seam_count) {

}


/*
    TODO: Adds a path to an image:

    - iterate over each row and each column in img_src and insert the corresponding
      pixel in path in the right place in img_out. 

    @param path 		(in)   the path being inserted
    @param img_src    		(in)   the image being inserted into
    @param img_out 		(out)  the resulting image
    @param offset    		(out)  the offset matrix indicating the offset for the path in each row
    @return             	void
*/
void addSeam(const PathCost &path, const cv::Mat &img_src, cv::Mat &img_out, cv::Mat &offset) {

}

/*
    TODO: Deletes a path from an image:

    - iterate over each row and each column in img_src and delete the corresponding
      pixel in min_path in the right place in img_out. 

    @param min_path 	(in)   the path being deleted
    @param img_src    	(in)   the image being deleted from
    @param img_out 	(out)  the resulting image
    @return             void
*/
void deleteMinPath(const PathCost &min_path, const cv::Mat &img_src, cv::Mat &img_out) {

}

/*
    TODO: Reduces an image's size rm_seam_count times:

    - calculate the gradient magnitude of the image using calculateGradientMag(...)
    - then calculate the paths using calculateCostImage(...)
    - then delete the minimum value path from the image using deleteMinPath(...)
    - do the above steps rm_seam_count times and save the result in output

    @param image 		(in)   the image to be reduced
    @param output    		(out)  the resulting image
    @param rm_seam_count 	(in)   the number of seams to be reduced from the image
    @return             	void
*/
void reduceImage(const cv::Mat &image, cv::Mat &output, int rm_seam_count) {

}

/*
    TODO: Enlarges an image's size add_seam_count times:

    - calculate the gradient magnitude of the image using calculateGradientMag(...)
    - then calculate the paths using calculateCostImage(...)
    - then delete the minimum path from image using deleteMinPath(...) 
    and use the result as the input image in the next iteration
    - and also add the minimum path to the image using addSeam(...)
    - do the above steps add_seam_count times and save the result in output_enlarge

    @param image 		(in)  the image to be enlarged
    @param output_enlarge	(out) the resulting image
    @param add_seam_count	(in)  the number of seams to be added to the image
    @return             	void
*/
void enlargeImage(cv::Mat &image, cv::Mat &output_enlarge, int add_seam_count) {

}

/*
    TODO: Calculates the localized Entropy of an image:

    - convert the image into a grayscale image using CV_BGR2GRAY
    - pad the image to accommodate the scanning windows 
    - then iterate over the original image's pixels and create a square
    region of interest around the pixel. 
    - use the ROI to calculate the probability of each color in the window to appear 
    when probing any random pixel in the window.
    - use the probability of the pixel in the center of the window to calculate the 
    local entropy at that pixel. 
    - save the results in entropy_array

    @param image 		(in)  the image of interest
    @param entropy_array	(out) the resulting localized entropy image
    @return             	void
*/
void calculateLocalEntropy(const cv::Mat &image, cv::Mat &entropy_array) {

	const int window_size = 5;
}

/*
    TODO: Reduces an image's size rm_entropy_count times:

    - calculate the local entropy of the image using calculateLocalEntropy(...)
    - then calculate the paths using calculateCostImage(...)
    - then delete the minimum value path from the image using deleteMinPath(...)
    - do the above steps rm_entropy_count times and save the result in output

    @param image 	     	(in)  the image to be reduced
    @param output        	(out) the resulting image
    @param rm_entropy_count 	(in)  the number of seams to be reduced from the image
    @return             	void
*/
void reduceEntropy(const cv::Mat &image, cv::Mat& output, int rm_entropy_count) {
}


//================================================================================
// main()
//
//================================================================================
int main(int argc, char *argv[]) {
	printf("CV/task1b framework version 1.0\n"); // DO NOT REMOVE THIS LINE!

	if (argc != 2) {
		std::cout << "Usage: ./cvtask1b <config-file>\n" << std::endl;
		return -1;
	}

	try {

		// Config and input parameters
		rapidjson::Document cfg;
		FILE* fp = fopen(argv[1], "r");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		cfg.ParseStream(is);
		assert(cfg.IsObject());

		// Input parameters
		const std::string image_path = cfg["image_path"].GetString();
    		const std::string output_path = cfg["output_dir"].GetString();
		const std::string name_image = cfg["name_image"].GetString();
		const int rm_seam_count = cfg["delete_seams_count"].GetInt();
		const int add_seam_count = cfg["enlarge_seams_count"].GetInt();
		const int rm_entropy_count = cfg["delete_entropy_count"].GetInt();

		// Output parameters
		const std::string out_grad_mag_filename = cfg["out_00_grad_mag"].GetString();
		const std::string out_costImage_filename = cfg["out_01_costImage"].GetString();
		const std::string out_seams_filename = cfg["out_02_seams"].GetString();
		const std::string out_vertical_filename = cfg["out_03_vertical"].GetString();
		const std::string out_horizontal_filename = cfg["out_04_horizontal"].GetString();
		const std::string out_enlarge_filename = cfg["out_05_enlarge"].GetString();
		const std::string out_entropy_filename = cfg["out_06_entropy"].GetString();
		const std::string out_bonus_filename = cfg["out_07_bonus"].GetString();

#if defined(_WIN32)
		_mkdir("./output/");
		_mkdir(output_path.c_str());
#else
		mkdir("./output/", 0777);
		mkdir(output_path.c_str(),0777);
#endif

		std::cout << "Running TC: " << argv[1] << std::endl;

		// Load input image
		std::string path = image_path + name_image + ".jpg";
		cv::Mat image = cv::imread(path);

		std::cout << "DONE" << std::endl;

		// Output images
		cv::Mat out_grad_mag = cv::Mat::zeros(image.size(), CV_32FC1);
		cv::Mat out_seams = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::Mat out_costImage = cv::Mat::zeros(image.rows, image.cols + 2, CV_32FC1);
		cv::Mat out_vertical = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::Mat out_horizontal = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::Mat out_enlarge = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::Mat out_entropy = cv::Mat::zeros(image.size(), CV_32FC1);
		cv::Mat out_bonus = cv::Mat::zeros(image.size(), CV_8UC3);

		/* TODO: calculate the Gradient Magnitude matrix of the image by
		** implementing the calculateGradientMag( ... ) methode
		**
		** save the resulting matrix in 'out_grad_mag'
		*/
		std::cout << "calculating gradient magnitude..." << std::endl;
		calculateGradientMag(image, out_grad_mag);
		std::cout << "DONE" << std::endl;

		/* TODO: calculate the cost of the 'out_grad_mag' image by
		** implementing the calculateCostImage( ... ) methode
		** The number of seams is stored in 'rm_seam_count'
		*/
		std::cout << "calculating all image cost..." << std::endl;
		std::vector<PathCost> vec_paths = calculateCostImage(out_grad_mag, out_costImage, rm_seam_count);

		std::cout << "DONE" << std::endl;

		/* TODO: highlight the seams you just calculated by
		** implementing the highlightSeams( ... ) methode
		** The number of seams is stored in 'rm_seam_count'
		**
		** save the resulting image in 'out_seams'
		*/
		std::cout << "highlighting seams..." << std::endl;
		highlightSeams(vec_paths, out_seams, rm_seam_count);
		std::cout << "DONE" << std::endl;

		/* TODO: reduce the image vertically and horizontally by
		** implementing the reduceImage( ... ) methode. The number of seams
		** to remove is stored in the 'rm_seam_count' variable.
		**
		** save the result in 'out_vertical' and 'out_horizontal' respectively
		**
		** Hint: there is no need to differentiate between horizontal and vertical
		** resizing. Use the OpenCV methode cv::transpose( ... ) to treat both cases equally.
		*/
		std::cout << "reducing images..." << std::endl;
		reduceImage(image, out_vertical, rm_seam_count);

		reduceImage(image, out_horizontal, rm_seam_count);

		std::cout << "DONE" << std::endl;

		/* TODO: enlarge the image vertically by
		** implementing the enlargeImage( ... ) methode. The number of seams
		** to add is stored in the 'add_seam_count' variable.
		**
		** save the result in 'out_enlarge'
		*/
		std::cout << "enlarging image..." << std::endl;
		enlargeImage(image, out_enlarge, add_seam_count);
		std::cout << "DONE" << std::endl;

		/* TODO: calculate the local entropy matrix of the image by 
		** implementing the calculateLocalEntropy( ...) methode.
		**
		** To display the image you have to normalize it first.
		** use cv::normalize( ... ) on the previously calculated local
		** entropy matrix and normalize the values between 0 and 255 
		** with normType cv::NORM_MINMAX and dtype CV_8UC1.
		**
		** save the result in 'out_entropy'
		*/
		std::cout << "calculating local entropy..." << std::endl;
		calculateLocalEntropy(image, out_entropy);
		cv::normalize(out_entropy, out_entropy, 0, 255, cv::NORM_MINMAX, CV_8UC1);
		std::cout << "DONE" << std::endl;

		/* TODO: reduce the image vertically by calculating the image entropy
		** instead of the gradient magnitude as the energy function. You should
		** implement the reduceEntropy( ... ) methode similar to reduceImage and use.
		** calculateLocalEntropy( ... ) instead of calculateGradientMag( ... ).
		** The number of seams to remove is stored in the 'rm_entropy_count' variable.
		**
		** save the result in 'out_bonus'
		*/
		std::cout << "reducing image via entropy..." << std::endl;
		reduceEntropy(image, out_bonus, rm_entropy_count);
		std::cout << "DONE" << std::endl;


		std::cout << "writing output...";
		imwrite(out_grad_mag_filename,out_grad_mag);
		imwrite(out_costImage_filename,out_costImage);
		imwrite(out_seams_filename,out_seams);
		imwrite(out_horizontal_filename,out_horizontal);
		imwrite(out_vertical_filename, out_vertical);
		imwrite(out_enlarge_filename,out_enlarge);
		imwrite(out_entropy_filename, out_entropy);
		imwrite(out_bonus_filename, out_bonus);
		std::cout << "DONE" << std::endl;

	}

	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Program exited with errors!" << std::endl;
		return -1;
	}
	std::cout << "Program exited normally!" << std::endl;
	return 0;
}
