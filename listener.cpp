#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "geometry_msgs/Point32.msg"
#include "std_msgs/String.h"
#include <sstream>
using namespace cv;
using namespace std;
struct point
{
int x;
int y;
} corr[200];
cv::Mat image=imread("ps1.jpg",1);

void fuc(int x,int y)  //fuction for changing path point into blue and displaying them
{

image.at<Vec3b>(x,y).val[0]=255;
image.at<Vec3b>(x,y).val[1]=0;
image.at<Vec3b>(x,y).val[2]=0; 
imshow( "Display window1", image );  
}
void chatterCallback(const std_msgs::String::ConstPtr& msg)  //i have taken input as string
{                                                              //extracting x and y coordinate from string message
 //ROS_INFO("I heard: [%s]", msg->data.c_str());

int i=0;int x=0;char c;int y=0; 
do{
 c= msg->data.c_str()[i++];
if(c=='0')
x=x*10;
else if(c=='1')
x=x*10+1;
else if(c=='2')
x=x*10+2;
else if(c=='3')
x=x*10+3;
else if(c=='4')
x=x*10+4;
else if(c=='5')
x=x*10+5;
else if(c=='6')
x=x*10+6;
else if(c=='7')
x=x*10+7;
else if(c=='8')
x=x*10+8;
else if(c=='9')
x=x*10+9;
}while(c!=' ');

do{
 c= msg->data.c_str()[i++];
if(c=='0')
y=y*10;
else if(c=='1')
y=y*10+1;
else if(c=='2')
y=y*10+2;
else if(c=='3')
y=y*10+3;
else if(c=='4')
y=y*10+4;
else if(c=='5')
y=y*10+5;
else if(c=='6')
y=y*10+6;
else if(c=='7')
y=y*10+7;
else if(c=='8')
y=y*10+8;
else if(c=='9')
y=y*10+9;
}while(c!=' ');

fuc(x,y);  
            
}

int main(int argc, char **argv)
{
namedWindow( "Display window1", CV_WINDOW_AUTOSIZE );// Create a window for display.
cvStartWindowThread();
ros::init(argc, argv, "listener");
ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
 ros::spin();
 cv::destroyWindow("Display window1");
//imshow("Display window1",image);

  return 0;
}

