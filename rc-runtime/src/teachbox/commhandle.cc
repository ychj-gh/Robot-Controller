#include "rclinterface.h"
#include "../opmanager.hh"

#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>


string projectDir = "./rc-runtime/test/";
string currentPro ;




int getAskForTransFile(){
	return 0;
}
int getMotionSignal(int axisIndex){
	if(axisIndex == 0) {
		rc_core.jog_startup = 0;
		std::cout << "press released" << std::endl;
		return 0;
	}
	axisIndex -= 1;
	std::cout << "coming in jog motion" << std::endl;
	if(SHM_PLC_START_GET(rc_shm) == 0) {
		// send_warm(1, "", "servo is poweroff");
		std::cout << "power is off" << std::endl;
	} else if(rc_core.mode != OP_TEACH) {
		// send_warm(1, "", "system is not in teach mode");
		std::cout << "mode is not OP_TEACH" << std::endl;
	} else if(rc_core.startup == 1) {
		// send_warm(1, "", "robot is running");
		std::cout << "sys is startup" << std::endl;
		std::cout << "rc_core.startup = " << rc_core.startup << std::endl;
	} else if(rc_core.jog_mode == 1) {
		std::cout << "sys is in jog mode" << std::endl;
	} else {
		std::cout << "jog start" << std::endl;

		rc_core.prog_ready = 0;
		rc_core.jog_mode = 1;
		rc_core.jog_startup = 1;
		rc_core.procedure = JOG_INCONSTACC;

		if(rc_core.interp_status == 0) {
			ROBOT_INST temp_inst;
			if(rc_core.coordinate == 0) {
				temp_inst.ri_type = JOINTJOG;
			} else {
				temp_inst.ri_type = CARTJOG;
			} 
			
			// first point
			size_t n = pRobot->getRobotAxisNum();
			Position_ACS_deg p1(n);
			pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
			std::cout << "Axis Position = "  << p1.transpose() << std::endl;
			// Position_MCS_rad pos(6);
		 	// pRobot->getActualTCPPos(rc_shm,&rc_mutex_desc,pos);
		 	// std::cout << "TCP Posture = " << pos.transpose() << std::endl;
			temp_inst.args[0].apv = p1;
			temp_inst.args[0].jjp.jointindex = axisIndex / 2;
			temp_inst.args[0].jjp.direction = axisIndex % 2;
			inst_buffer_write(temp_inst);
		} else {

		}
	}
	
	return 0;
}

int replyPositionRequest(){
	// std::cout << "teach terminal request postion info" << std::endl;
	size_t n = pRobot->getRobotAxisNum();
	Position_ACS_deg p(n);
	Position_MCS_deg Outpos(6);
	pRobot->getActualPoses(rc_shm,&rc_mutex_desc,p,Outpos);
	std::cout << "Axis Position = "  << p.transpose() << std::endl;
	std::cout << "TCP Posture = " << Outpos.transpose() << std::endl;
	std::vector<double> curpos;
	for(int i = 0; i < 6; i ++) {
		curpos.push_back(p[i]);
		curpos.push_back(Outpos[i]);
		curpos.push_back(0);
	}
	send_position_info(curpos);
	return 0;
}


//初始化客户端
int initClient(){
	vector<string> prolist;
	DIR *dir;
	struct dirent *ptr;
	dir = opendir("./rc-runtime/test");
	while((ptr = readdir(dir)) != NULL){
		string proname(ptr->d_name);
		if(proname != "." && proname != "..")
			prolist.push_back(proname);
	}
	send_prolist(prolist.size(), prolist);
	closedir(dir);
	return 0;
}

int replyFileAndNames(const string& proname){
	vector<FileInfo> filelist;
	DIR *dir;
	struct dirent *ptr;
	string prodir = string("./rc-runtime/test/") + proname;
	rc_core.cur_project = prodir;
	currentPro = proname;
	dir = opendir(prodir.c_str());
	if(dir == NULL) {				// project not found, Then create a new project
		int status = mkdir(prodir.c_str(), S_IRWXU);
		send_filelist(filelist.size(), filelist);
		return -1;
	}
	while((ptr = readdir(dir)) != NULL){
		FileInfo cur;
		cur.proname = proname;
		cur.filename = string(ptr->d_name);
		if(cur.filename != "." && cur.filename != "..")
			filelist.push_back(cur);
	}
	send_filelist(filelist.size(), filelist);
	vector<string> filenamelist;
	for(int i = 0; i < filelist.size(); i ++) {
		string filedir = prodir + "/" + filelist[i].filename;
		std::cout << filedir << std::endl;
		sendFile(filedir);
		filenamelist.push_back(filedir);
	}
	// transFileList(filenamelist);
	return 0;
}



int importFileChanged(const string& filename){
	DIR *dir;
	struct dirent *ptr;

	string fn = filename.substr(0, filename.find_last_of("."));
	rc_core.cur_program = rc_core.cur_project + "/" + fn;
	std::cout << rc_core.cur_program << std::endl;

	dir = opendir(rc_core.cur_project.c_str());
	if(dir == NULL) {
		std::cout << "dir is NULL" << std::endl; 
		return -1;
	}
	bool flag = true;
	while((ptr = readdir(dir)) != NULL) {
		string str = ptr->d_name;
		if(str == filename) {
			flag = false;
		}
	}

	if(flag) {
		string tempname = rc_core.cur_program + ".tip";
		std::cout << tempname << std::endl;
		int fd = open(tempname.c_str(),O_CREAT | O_RDWR, S_IRWXU);
		close(fd);
		tempname = rc_core.cur_program + ".tid";
		fd = open(tempname.c_str(),O_CREAT | O_RDWR, S_IRWXU);
		close(fd);
	}
	return 0;
}




int resetPointer(int curPointer,int totalline) {
	std::cout << "[RC PC RESET : PC = 1]" << std::endl;
	
	std::cout << "interp_start flag = " << SHM_INTERP_START_GET(rc_shm) << std::endl;
	std::cout << "interp status flag = " << SHM_INTERP_STATUS_GET(rc_shm) << std::endl;
	SHM_INTERP_START_CLR(rc_shm);
	rc_core.startup = 0;
	rc_core.cur_linenum = 1;
	rc_core.prog_ready = 1;

	// if(rc_core.exec_run_mode) {
		send_cmd_to_exec(CMD_RESET);
	// }	
	// if(rc_core.interp_status) {
	// 	send_cmd_to_interp(2);  // 2 --> reset cmd
	// }
	send_filename_and_ptr(1, rc_core.cur_program);
	return 0;
}


int startKeyDown() {
	// std::cout << "start key down" << std::endl;
	if(SHM_PLC_START_GET(rc_shm) == 0) {
		// send_warm(1, "", "servo is poweroff");
		std::cout << "power is off" << std::endl;
	} else if(rc_core.jog_mode == 1) {
		std::cout << "sys is in jog mode" << std::endl;
	} else if(rc_core.prog_ready == 0) {
		std::cout << "program has changed, you need reset program pointer" << std::endl;
	} else {
		std::cout << " robot movement start up " << std::endl;
		rc_core.startup = 1;
		// if(rc_core.interp_status) {
		// 	rc_shm->interp_startup_flag = 1;
		// } else {
		// 	if(rc_core.exec_run_mode == 0) {
		// 		rc_core.startup = 1;
		// 	}
			send_cmd_to_exec(CMD_START);
		// }
	}

	return 0;
}


int startKeyUp() {
	// std::cout << "start key up" << std::endl;
	if(rc_core.mode == OP_TEACH && RSIStopFlag) {
	// 	rc_shm->interp_startup_flag = 0;
		SHM_INTERP_STATUS_CLR(rc_shm);
		// rc_shm->interp_status = 0;
		// rc_core.startup = 0;
		// send_cmd_to_rsi(2);
	}
	
	return 0;
}

#include <fstream>
std::ofstream outfile;

int stopKeyDown() {
	// std::cout << "stop key down" << std::endl;
	outfile.open("/home/seu/workspace/logfile/plcloginfo.txt",ios::app);
	if(SHM_INTERP_STATUS_GET(rc_shm)){
		SHM_INTERP_START_CLR(rc_shm);
		SHM_INTERP_STATUS_CLR(rc_shm);
		send_cmd_to_interp(2);
	}
	// rc_shm->interp_startup_flag = 0;
	// rc_shm->interp_status = 0;
	rc_core.startup = 0;
	send_cmd_to_rsi(2);
	outfile << "RC STOP KEY DOWN" << std::endl;
	outfile.close();
	return 0;
}

//type表示状态类型：
//1: 单步（0）连续（1） 状态
//2: 示教（0）再现（1）状态
//3: 坐标系：关节（0）世界（1）工具（2）
//6: 速度
int statusChange(int type ,int value) {
	std::cout << "statusChange" << std::endl;
	switch(type) {
		case 1: {		//1: 单步（0）连续（1） 状态
			std::cout << "step/continus" << std::endl;
			// if(rc_core.startup == 0) {
			// 	rc_core.stepflag = !value; 
			// 	sendStatusChange(type, value);
			// } else {
			// 	sendStatusChange(type, !value);
			// }
			break;
		}
		case 2: {		//2: 示教（0）再现（1）状态
			std::cout << "teach/rerun" << std::endl;
			// if(rc_core.startup == 0) {
			// 	rc_core.stepflag = value; 
			// 	sendStatusChange(type, value);
			// } else {
			// 	sendStatusChange(type, !value);
			// }
			break;
		} 
		case 3: {		//3: 坐标系：关节（0）世界（1）工具（2）
			std::cout << "axes change" << std::endl;
			if(rc_core.startup == 0) {
				rc_core.coordinate = value; 
				std::cout << value << std::endl;
				sendStatusChange(type, value);
			} 
			break;
		}
		case 6: {		//6: 速度
			std::cout << "speed change : " << value << std::endl;
			break;
		}
		default:
			break;
	}
	return 0;
}


