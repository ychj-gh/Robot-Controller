#! /bin/bash
 g++ main_io.cpp -std=c++11 -o main_io -I/usr/xenomai/include -I../include -L/usr/xenomai/lib -lnative -lxenomai -lpthread_rt -lpthread