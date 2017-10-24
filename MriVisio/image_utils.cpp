#include "image_utils.h"
#include <cmath>


namespace deprecated 
{
	image_t integral_dst1(image_t image)
	{
		image_t dst = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst2 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst3 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);

		cvIntegral(image, dst, dst2, dst3);// dst2, dst3);
		return dst;
	}

	image_t integral_dst2(image_t image)
	{
		image_t dst = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst2 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst3 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);

		cvIntegral(image, dst, dst2, dst3);// dst2, dst3);
		return dst2;
	}

	image_t integral_dst3(image_t image)
	{
		image_t dst = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst2 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);
		image_t dst3 = cvCreateImage(cvSize(image->width + 1, image->height + 1), IPL_DEPTH_64F, image->nChannels);

		cvIntegral(image, dst, dst2, dst3);// dst2, dst3);
		return dst3;
	}
}

image_t image_utils::read_image(const std::string& full_file_path)
{
	return cvLoadImage(full_file_path.c_str());
}

void image_utils::save_image(image_t image, const std::string& full_file_path)
{
	cvSaveImage(full_file_path.c_str(), image);
}

int image_utils::parameters::depth(image_t image)
{
	return image->depth;
}

CvSize image_utils::parameters::size(image_t image)
{
	return CvSize(image->width, image->height);
}

int image_utils::parameters::channels(image_t image)
{
	return image->nChannels;
}

image_t image_utils::clone(image_t image)
{
	IplImage* dst = 0;
	dst = cvCloneImage(image);
	return dst;
}

image_t image_utils::clone(scope_image image)
{
	IplImage* dst = 0;
	dst = cvCloneImage(*image);
	return dst;
}

image_t image_utils::create(CvSize size, int depth, int nChannels)
{
	return cvCreateImage(size, depth, nChannels);
}

image_t image_utils::canny(image_t img, int size)
{
	IplImage* dst = 0;
	dst = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCanny(img, dst, 10, 100, size);
	return dst;
}

image_t image_utils::create_by_template(image_t image)
{
	return cvCreateImage(cvSize(image->width, image->height), image->depth, image->nChannels);
}

image_t image_utils::lightening(image_t image, float factor)
{
	float kernel[9];
	kernel[0] = -0.1 ;
	kernel[1] = 0.2* factor;
	kernel[2] = -0.1 ;

	kernel[3] = 0.2* factor;
	kernel[4] = 3 * factor;
	kernel[5] = 0.2* factor;

	kernel[6] = -0.1 ;
	kernel[7] = 0.2* factor;
	kernel[8] = -0.1 ;

	CvMat kernel_matrix = cvMat(3, 3, CV_32FC1, kernel);

	image_t dst = clone(image);
	cvFilter2D(image, dst, &kernel_matrix, cvPoint(-1, -1));
	return dst;
}

image_t image_utils::blackout(image_t image, float factor)
{
	float kernel[9];
	kernel[0] = -0.1 * factor;
	kernel[1] = 0.1;
	kernel[2] = -0.1 * factor;

	kernel[3] = 0.1;
	kernel[4] = 0.5;
	kernel[5] = 0.1;

	kernel[6] = -0.1 * factor;
	kernel[7] = 0.1;
	kernel[8] = -0.1 * factor;

	CvMat kernel_matrix = cvMat(3, 3, CV_32FC1, kernel);

	image_t dst = clone(image);
	cvFilter2D(image, dst, &kernel_matrix, cvPoint(-1, -1));
	return dst;
}

image_t image_utils::laplace(image_t image, int aperture)
{
	image_t dst = clone(image);

	cvLaplace(image, dst, aperture);
	return dst;
}

image_t image_utils::sobel(image_t image, int xorder, int xorder_max, int yorder, int yorder_max, int aperture)
{
	image_t dst = clone(image);
	cvSobel(image, dst, xorder, yorder, aperture);
	return dst;
}

image_t image_utils::to_8bit(image_t image)
{
	image_t dst = create_by_template(image);
	cvConvertScale(image, dst);
	return dst;
}


image_t image_utils::threshold(image_t image, int min, int max)
{
	cv::Mat bin_mat;
	image_t dst = image_utils::create_by_template(image);
	cvThreshold(image, dst, min, max, CV_THRESH_BINARY_INV);
	return dst;
}



contour_container image_utils::find_countour(image_t image, contour_filter_container filters)
{
	image_t gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	image_t bin = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

	cvCvtColor(image, gray, CV_RGB2GRAY);

	cvInRangeS(gray, cvScalar(40), cvScalar(150), bin); // atoi(argv[2])

	CvMemStorage* storage = cvCreateMemStorage(0);
	contour contours = 0;
	
	cvFindContours(bin, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	return contour_container(contours, filters);

}

image_t image_utils::contour_to_image(contour_container conts, CvSize size, int depth, int channels)
{
	image_t dst = image_utils::create(size, depth, channels);
	cvZero(dst);

	while(!conts.is_end())
		cvDrawContours(dst, conts.get(), CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);

	return dst;
}

image_t image_utils::contour_to_image(contour_container conts, image_t image)
{
	return contour_to_image(conts, CvSize(image->width, image->height), image->depth, image->nChannels);
}

image_t image_utils::contour_to_image(contour cont, image_t image)
{
	image_t dst = image_utils::create(CvSize(image->width, image->height), image->depth, image->nChannels);
	cvZero(dst);

	cvDrawContours(dst, cont, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
	return dst;
}

image_t image_utils::contour_to_image(contour cont, CvSize size, int depth, int channels)
{
	if (cont == NULL)
		return NULL;

	image_t dst = image_utils::create(size, depth, channels);
	cvZero(dst);
	cvDrawContours(dst, cont, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
	return dst;
}

contour image_utils::find_max_contour(contour_container cont)
{
	contour max_contour = NULL;
	double max_d = 0;
	
	cont.reset();
	
	while (!cont.is_end())
	{
		contour current = cont.get();
		if (current == NULL)
		{
			// TODO: Trash!
			break;
		}
		CvRect rect = get_bounding_rect_image(current);
		double sqr = std::sqrt(rect.height * rect.height + rect.width*rect.width);
		if (sqr > max_d)
		{
			max_d = sqr;
			max_contour = current;
		}

	}
	return max_contour;
}

CvRect image_utils::get_bounding_rect_image(contour cont)
{
	return cvBoundingRect(cont);
}

image_t image_utils::smooth(image_t image, int x, int y)
{
	image_t dst = image_utils::clone(image);
	cvSmooth(image, dst, CV_BLUR, x, y);
	return dst;
}

image_t image_utils::cut_rect_from_image(image_t image, CvRect rect)
{
	scope_image copy_image = clone(image);	
	cvSetImageROI(*copy_image, rect);
	return clone(*copy_image);
}

image_t image_utils::draw_contour_on_image(contour_container cont, image_t image)
{
	cont.reset();
	image_t dst = clone(image);
	while (!cont.is_end())
	{
		contour current = cont.get();
		if (current == NULL)
			break;

		dst = draw_contour_on_image(current, dst);
	}
	return dst;
}

image_t image_utils::draw_contour_on_image(contour cont, image_t image)
{
	if (cont == NULL)
		return NULL;

	image_t dst = image_utils::clone(image);	
	cvDrawContours(dst, cont, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
	return dst;
}