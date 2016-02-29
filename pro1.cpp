#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "std_msgs/String.h"
//#include "geometry_msgs/Point32.msg"
#include <queue>
#include <sstream>

using namespace cv;
using namespace std;
cv::Mat image=imread("ps1.jpg",1);
int valid(int x,int y)
{
if(x<image.rows&&y<image.cols&&x>=0&&y>=0)
return 1;
else
return 0;
}
void def(int visit[][200],int xr,int yr,int xg,int yg)
{

int i,j,count=0;
int flag[200][200];
for(i=0;i<200;i++)
for(j=0;j<200;j++)
flag[i][j]=0;
queue<int> x;
queue<int> y;
x.push(xr);
y.push(yr);
visit[x.front()][y.front()]=0;
while(!x.empty())
{
if(flag[x.front()][y.front()]==0)
{
for(i=x.front()+1;i>=x.front()-1;i--)
for(j=y.front()+1;j>=y.front()-1;j--)
   {
   if(!(i==x.front()&&j==y.front())&&flag[i][j]==0&&valid(i,j)==1&&!(image.at<Vec3b>(i,j).val[0]==255&&image.at<Vec3b>(i,j).val  [1]==255&&image.at<Vec3b>(i,j).val[2]==255))
    {
    x.push(i);
    y.push(j);
    if((visit[x.front()][y.front()]+1)<visit[i][j])
       {visit[i][j]=visit[x.front()][y.front()]+1;}
   // ROS_INFO("%d %d %d %d",visit[i][j],i,j,count++);
    }
   }
flag[x.front()][y.front()]=1;
//ROS_INFO("%d %d %d ",x.front(),y.front(),visit[x.front()][y.front()]);
}
if(x.front()==xg&&y.front()==yg)
break;
x.pop();
y.pop();
}

}
int main(int argc, char **argv)
{

cv::namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
//cv::imshow( "Display window", image );                   // Show our image inside it

int i,j,count=0,sumx=0,sumy=0;
for(i=0;i<image.rows;i++)
{
for(j=0;j<image.cols;j++)
{
if(image.at<Vec3b>(i,j).val[2]==237)
{
count++;
sumx=sumx+i;
sumy=sumy+j;
}
}
}
sumx=sumx/count;
sumy=sumy/count;

count=0;
int sumx1=0,sumy1=0;
for(i=0;i<image.rows;i++)
{
for(j=0;j<image.cols;j++)
{
if(image.at<Vec3b>(i,j).val[1]==255&&image.at<Vec3b>(i,j).val[2]==0&&image.at<Vec3b>(i,j).val[0]==0)
{
count++;
sumx1=sumx1+i;
sumy1=sumy1+j;
}
}
}
sumx1/=count;
sumy1/=count;
int visited[200][200];
for(i=0;i<200;i++)
{
for(j=0;j<200;j++)
{
visited[i][j]=1000;
}}
def(visited,sumx,sumy,sumx1,sumy1);
ros::init(argc, argv, "talker");
ros::NodeHandle n;
ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
ros::Rate loop_rate(10);
i=sumx1;j=sumy1;

while(visited[i][j]!=0)
{

std_msgs::String msg;

    std::stringstream ss;
    ss <<i<<" "<<j<<" ";
    msg.data = ss.str();
 chatter_pub.publish(msg);
 ros::spinOnce();
 loop_rate.sleep();
//ROS_INFO("%d %d  %d",i,j,visited[i][j]);
//image.at<Vec3b>(i,j).val[0]=255;
//image.at<Vec3b>(i,j).val[1]=255;
//image.at<Vec3b>(i,j).val[2]=255;
if(visited[i+1][j+1]==(visited[i][j]-1))
{i++;j++;}
else if(visited[i+1][j-1]==(visited[i][j]-1))
{i++;j--;}
else if(visited[i-1][j+1]==(visited[i][j]-1))
{i--;j++;}
else if(visited[i-1][j-1]==(visited[i][j]-1))
{i--;j--;}
else if(visited[i][j+1]==(visited[i][j]-1))
{j++;}
else if(visited[i+1][j]==(visited[i][j]-1))
{i++;}
else if(visited[i][j-1]==(visited[i][j]-1))
{j--;}
else if(visited[i-1][j]==(visited[i][j]-1))
{i--;}

 }  
imshow( "Display window", image );   
  // cv::waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
