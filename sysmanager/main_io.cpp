#include <native/heap.h>
#include <native/task.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "io.h"
using namespace std;

#define IO_TASK_NAME		"io_task"
#define IO_TASK_PRIORITY	96
RT_TASK 	io_task;
IOMem 		io_shm;
RT_HEAP 	ioconf_heap;
IOConfig 	*io_conf;


void sig_handler(int signo){
	if(signo == SIGINT){
		io_mem_unbind(&io_shm);
		io_conf_unbind(&ioconf_heap);
		rt_task_delete(&io_task);
		exit(0);
	}
}

static void io_update(void *cookie){
	io_conf_bind(&ioconf_heap,&io_conf);
	io_mem_bind(&io_shm);

	rt_task_set_periodic(NULL,TM_NOW,io_conf->update_interval);
	while(1){
		rt_task_wait_period(NULL);
		for(int i = 0; i < io_conf->typecount; ++i){
			if(io_conf->io_map[i].iotype == INPUT_IO && io_conf->io_map[i].datatype == DIGIT_IO){
				cout << "=============== Digit Input ==============" << endl;
				int size = io_conf->io_map[i].size;
				cout << "channel number = " << size << endl;
				for(int j = 0; j < size/8; ++j){
					int IO_ID = io_conf->io_map[i].id[j];
					cout << "id" << IO_ID << ":\t";
					char *addr = io_shm.base[0] + IO_ID*DIGITUNIT_SIZE;
						cout << (unsigned)(*addr) << endl;
				}

			}else if(io_conf->io_map[i].iotype == OUTPUT_IO && io_conf->io_map[i].datatype == ANALOG_IO){
				cout <<  "=============== Analog Output =============" << endl;
				int size = io_conf->io_map[i].size;
				cout << "channel number = " << size << endl;
				for(int j = 0; j < size/8; ++j){
					int IO_ID = io_conf->io_map[i].id[j];
					float* addr = (float *)(io_shm.base[1] + DIGIT_SIZE + (IO_ID-16)*ANALOGUNIT_SIZE);
					cout << "id: " << IO_ID;
					for(int port = 0; port < 8; ++port){
						cout << "\tport" << port << ": ";
						cout << *(addr+port) << endl;
					}
				}
			}
			// int IO_ID = io_conf->io_map[i].id;
			// if(IO_ID >= 1 && IO_ID <= 16 && io_conf->io_map[i].iotype == INPUT_IO){
			// 	cout << "============= Digit Input ================" << endl;
			// 	cout << "size = " << io_conf->io_map[i].size/8 << endl;
			// 	char *addr = io_shm.base[0] + (IO_ID - 1)* DIGITUNIT_SIZE;
			// 	for(int j = 0; j < io_conf->io_map[i].size / 8; ++j){
			// 		cout << (unsigned)(*(addr+j)) << endl;
			// 	}
			// }
			// if(IO_ID >= 17 && IO_ID <= 32 && io_conf->io_map[i].iotype == OUTPUT_IO){
			// 	cout << "============= Analog Output ===============" << endl;
			// 	float* addr = (float *)(io_shm.base[1] + DIGIT_SIZE + (IO_ID-17)*ANALOGUNIT_SIZE);
			// 	cout << "size = " << (unsigned)io_conf->io_map[i].size << endl;
			// 	for(int j = 0; j < io_conf->io_map[i].size; ++j)
			// 		cout << *(addr+j) << endl;
			// }
		}

	}
}

int  main(){
	if(signal(SIGINT, &sig_handler) == SIG_ERR)
		cout << "signal error" << endl;

	if(rt_task_create(&io_task,IO_TASK_NAME,0,IO_TASK_PRIORITY,T_JOINABLE) < 0)
		cout << "rt_task create error" << endl;
	if(rt_task_start(&io_task, &io_update, NULL) < 0)
		cout << "rt_task start error" << endl;

	rt_task_join(&io_task);
	return 0;
}
