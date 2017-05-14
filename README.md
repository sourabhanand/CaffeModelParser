# CaffeModelParser
C++ Caffe Model Parser

This project contains apis to read and parse Caffe's model file and prototxt file.
It is a standalone project and requires Caffe to be installed in the system.

*Before building this project make sure you make two changes:*

- change the value of *CAFFE_DIR* in Makefile to your Caffe installation path
- In main.cpp file change the value of *modelParamFile* and *modelWeightsFile* to your specific model
