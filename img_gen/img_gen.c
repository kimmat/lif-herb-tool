#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/core.hpp>

#include <tinyxml.h>


void genImage(IplImage* img, int r, int g, int b, double alpha)
{
  uint8_t* img_ptr = (uint8_t*) img->imageData;
  
  IplImage *im_gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
  cvCvtColor(img,im_gray,CV_BGRA2GRAY);
  
  IplImage *im_bgr = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
  IplImage *im_hsv = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
  cvCvtColor(img,im_bgr,CV_BGRA2BGR);
  cvCvtColor(im_bgr,im_hsv,CV_BGR2HSV);
  
  uint8_t* gray_ptr = (uint8_t*) im_gray->imageData;
  uint8_t* hsv_ptr = (uint8_t*) im_hsv->imageData;
  
  //printf("Processing image %ix%i %i channels %i depth\n", img->width, img->height, img->nChannels, img->depth);
  
  for (int x=0;x<img->width;x++)
  {
    for (int y=0;y<img->height;y++)
    {
      int i_4 = img->nChannels*x + img->widthStep*y;
      int i_3 = im_hsv->nChannels*x + im_hsv->widthStep*y;
      int i_g = x + im_gray->widthStep*y;
      
      double blue  = (double) img_ptr[i_4];
      double green = (double) img_ptr[i_4+1];
      double red   = (double) img_ptr[i_4+2];
      
      double gray = 0.3*red + 0.59*green + 0.11*blue;
      
      //double alpha = 0.8;
      double beta = 255.0*(1.0-alpha);
      
      //img_ptr[i_4]   = (((int) gray_ptr[i_g])*b) >> 8;
      //img_ptr[i_4+1] = (((int) gray_ptr[i_g])*g) >> 8;
      //img_ptr[i_4+2] = (((int) gray_ptr[i_g])*r) >> 8;
      
      if ( hsv_ptr[i_3] > 12 && hsv_ptr[i_3] < 24 )
      {
	img_ptr[i_4]   = (uint8_t) ((beta+alpha*gray)*((double) b)/255.0);
	img_ptr[i_4+1] = (uint8_t) ((beta+alpha*gray)*((double) g)/255.0); 
	img_ptr[i_4+2] = (uint8_t) ((beta+alpha*gray)*((double) r)/255.0);
      }
    }
  }
  
  /* font
  CvPoint p;
  p.x = 1;
  p.y = 12;
  CvFont font;
  cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX_SMALL, 0.8, 0.8, 0.0, 1, 8 );
  cvPutText(img, "TTT", p, &font, CV_RGB(255,255,255));
  */
}

void genAllImage(IplImage* img, char* name)
{
  IplImage *img_color = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,4);
  char filename[512];
  
  /* gray */
  cvCopy(img, img_color);
  genImage(img_color, 255, 255, 255, 0.8);
  sprintf(filename,"../img/gray/%s", name);
  cvSaveImage(filename, img_color);
  
  /* red */
  cvCopy(img, img_color);
  genImage(img_color, 255, 102, 102, 0.8);
  sprintf(filename,"../img/red/%s", name);
  cvSaveImage(filename, img_color);
  
  /* green */
  cvCopy(img, img_color);
  genImage(img_color, 0, 255, 0, 0.8);
  sprintf(filename,"../img/green/%s", name);
  cvSaveImage(filename, img_color);
  
  /* blue */
  cvCopy(img, img_color);
  genImage(img_color, 102, 102, 255, 0.8);
  sprintf(filename,"../img/blue/%s", name);
  cvSaveImage(filename, img_color);
  
  /* cyan */
  cvCopy(img, img_color);
  genImage(img_color, 0, 255, 255, 0.8);
  sprintf(filename,"../img/cyan/%s", name);
  cvSaveImage(filename, img_color);
  
  /* magenta */
  cvCopy(img, img_color);
  genImage(img_color, 255, 0, 255, 0.8);
  sprintf(filename,"../img/magenta/%s", name);
  cvSaveImage(filename, img_color);
  
  /* yellow */
  cvCopy(img, img_color);
  genImage(img_color, 255, 255, 0, 0.8);
  sprintf(filename,"../img/yellow/%s", name);
  cvSaveImage(filename, img_color);
  

    /* orange */
  cvCopy(img, img_color);
  genImage(img_color, 255, 128, 0, 0.8);
  sprintf(filename,"../img/orange/%s", name);
  cvSaveImage(filename, img_color);
  
    /* darkrose */
  cvCopy(img, img_color);
  genImage(img_color, 255, 102, 179, 0.8);
  sprintf(filename,"../img/darkrose/%s", name);
  cvSaveImage(filename, img_color);
  
    /* chartreuse */
  cvCopy(img, img_color);
  genImage(img_color, 128, 255, 0, 0.8);
  sprintf(filename,"../img/chartreuse/%s", name);
  cvSaveImage(filename, img_color);
  
    /* springgreen */
  cvCopy(img, img_color);
  genImage(img_color, 0, 255, 128, 0.8);
  sprintf(filename,"../img/springgreen/%s", name);
  cvSaveImage(filename, img_color);
  
    /* darkviolet */
  cvCopy(img, img_color);
  genImage(img_color, 179, 102, 255, 0.6);
  sprintf(filename,"../img/darkviolet/%s", name);
  cvSaveImage(filename, img_color);
  
    /* manganeseblue */
  cvCopy(img, img_color);
  genImage(img_color, 102, 179, 255, 0.8);
  sprintf(filename,"../img/manganeseblue/%s", name);
  cvSaveImage(filename, img_color);
}

int main()
{
  char game_dir[] = "/media/minidisk/LiF/Life is Feudal Your Own";
  
  TiXmlDocument doc( "objects_types.xml" );
  bool fileLoaded = doc.LoadFile();
  
  if ( !fileLoaded )
    return 0;
  
  int c = 0;
  
  TiXmlHandle hDoc(&doc);
  
  int pid = 0;
  TiXmlElement *parent = doc.FirstChildElement("table");
  for( TiXmlElement *child = parent->FirstChildElement(); child ; child = child->NextSiblingElement() )
  {
    
    for( TiXmlElement *c1 = child->FirstChildElement(); c1 ; c1 = c1->NextSiblingElement() )
    {
      if ( strcmp(c1->Value(),"ParentID") == 0 )
      {
	pid = atoi(c1->GetText());
      }
      if ( pid == 666 && strcmp(c1->Value(),"FaceImage") == 0 )
      {
	char file[2048];
	sprintf(file, "%s/", game_dir);
	
	char text[512];
	strncpy(text,c1->GetText(),512);
	char* part = strtok(text, "\\");
	char* last;
	while ( part )
	{
	  sprintf(file, "%s/%s", file, part);
	  
	  last = part;
	  part = strtok(NULL, "\\");
	}
	
	IplImage* img = cvLoadImage(file,CV_LOAD_IMAGE_UNCHANGED);
	
	if ( img == NULL )
	{
	  printf("Error opening file\n");
	}
	
	genAllImage(img, last);
	
	cvReleaseImage(&img);
      }
    }
  }
  
}