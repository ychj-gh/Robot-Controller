#ifndef RCINTERFACEE_H
#define RCINTERFACEE_H
#include <string>
#include <vector>
using namespace std;

extern string currentPro;
extern string projectDir;
struct IOInfo
{
    int num;
    int type; //0:Din 1:Dout 2:Ain 3:Aout
    string truevalue;
    string simvalue;
};

struct Pos
{
    double axe1_value;
    double axe2_value;
    double axe3_value;
    double axe4_value;
    double axe5_value;
    double axe6_value;
};

struct PosInfo
{
   int axenum;
   int axetype;//0: axe 1: world 2:tool
   string value;
   int status;
};

struct WarmInfo
{
    int warmtype;
    string warmtime;
    string warmvalue;
};

struct DataInfo
{
    int type;
    string proname;
    string name;
    string value;
};

struct FileInfo
{
    string proname;
    string filename;
};

extern int send_position_info(vector<double> pos);   //发送位置信息
extern int send_filelist(int len ,vector<FileInfo> filelist);      //发送文件列表
extern int send_prolist(int len,vector<string> prolist);  //发送工程列表
extern int send_iolist(int len,vector<IOInfo>iolist); //发送IO列表
extern int send_datalist(int len,vector<DataInfo>datalist);//发送数据列表
extern int send_warm(int wtype,const string &wtime,const string &wvalue);                         //发送报警信息
extern int send_ioinfo(int num,int type,const string &truevlaue,const string &simuvalue);                       //发送io信息
extern int send_filename_and_ptr(int ptrnum,const string &str);                         //发送当前程序指针
extern int respondeTransFile(int isok); //通知客户端是否可以传文件，0表示不允许 ，1表示允许
extern int sendFile(const string& filename);//
extern int transFileList(vector<string> filelistt);//传输多个文件
extern int sendStatusChange(int kind,int value);//状态改变通知


//extern int send_pos_toclient(double a1,double a2,double a3,double a4,double a5,double a6);         //从共享内存读取位姿(zuofei)
extern int upload_pos_toServer(double a1,double a2,double a3,double a4,double a5,double a6);       //写入位姿到共享内存  **daishixian(zuofei)
extern int send_termaxis(float term[][4] ,int len);                       //发送中断位姿矩阵
extern int start_client_service(int argc, char **argv);                //启动控制器服务程序
extern int write_ForceData(float f1,float f2,float f3,float f4,float f5,float f6);//发送力控数据
extern int send_ForceInfo(char type,const string &arg1); //上传力控信息
extern int send_ForceStatus(const string &str);                 //力控状态
extern int send_ForceRecordOrder(const string & str);             //力控记录序列
extern int send_ForceCollectionOrder(const string & str);        //力控采集序列
extern int send_ForceHistoryTime(const string & str);            //力控历史时间
extern int send_ForceInfoMessage(const string & str);           //力控提示信息
extern int send_VisualInfo(char type,const string &str);     //上传视觉信息
extern int send_VisualNum(int i);                            //发送视觉作业号
extern int send_VisualOffset(float xpos,float ypos,float zpos,float xoff,float yoff,float zoff);//发送当前偏移量
extern int send_VisualCommand(const string & str);               //视觉请求信息
extern int send_VisualResult(const string & str);                //视觉分析结果
extern int send_VisualImage(const string & filename);           //发送照片，filename为照片的完整路径名称，一般设置为本目录下
//extern int transprogramfile();
extern int virtualinitserver();
//extern int continueexecute();                   //连续取插补序列
//extern int stepexecute();                       //单步取插补序列


//...................edit by yaoshun....................//

extern int getAskForTransFile();
extern int getMotionSignal(int i); //除二的余数表示增减，除二的值表示第几个轴
extern int replyPositionRequest(); //发送位姿数据到示教盒
extern int initClient();//初始化客户端
extern int replyFileAndNames(const string& proname);//
extern int importFileChanged(const string& filename);//导入文件变动
extern int resetPointer(int curPointer,int totalline);//重置程序指针
extern int startKeyDown();
extern int startKeyUp();
extern int stopKeyDown();
extern int statusChange(int type ,int value);//type表示状态类型：
//1: 单步（0）连续（1） 状态
//2: 示教（0）再现（1）状态
//3: 坐标系：关节（0）世界（1）工具（2）
//6: 点动速度
//extern int normalKeyUp();
#endif // CTRLINTERFACEE_H
