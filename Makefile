# change this to your caffe installation path
# Don't forget to run `make distribute` in caffe installation directory
CAFFE_DIR := /home/sourabh/Work/caffe

# program config   -*-DO NOT EDIT-*-
PROJECT := CaffeModelParser
BUILD_DIR := build

CPU_ONLY := 1

CXX = g++ -std=c++11
CXXFLAGS = -c -O2 -Wall -Wno-sign-compare

ifeq ($(CPU_ONLY), 1)
	CXXFLAGS += -DCPU_ONLY
endif


INCLUDE_DIRS := $(CAFFE_DIR)/distribute/include ./include /usr/local/include /usr/include/hdf5/serial/
INC_PARAMS := $(foreach includedir, $(INCLUDE_DIRS), -I$(includedir))


LIBRARY_DIRS := $(CAFFE_DIR)/distribute/lib /usr/local/lib /usr/lib /usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/hdf5/serial/
LIBRARIES := glog gflags protobuf boost_system boost_filesystem m hdf5_hl hdf5 caffe
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir)) \
		$(foreach library,$(LIBRARIES),-l$(library))

VPATH := source

#all cpp files
FULL_CXX_SRCS := $(shell find source/ -name "*.cpp")
#get just file names
CXX_SRCS := $(notdir $(FULL_CXX_SRCS))

CXX_OBJS := $(addprefix $(BUILD_DIR)/, ${CXX_SRCS:.cpp=.o})
SRC_OBJS :=  $(CXX_OBJS)


#build targets
.PHONY: all $(PROJECT) objdir clean

all: $(PROJECT)

$(PROJECT): $(SRC_OBJS)
	$(CXX) $(SRC_OBJS) -o $(BUILD_DIR)/$(PROJECT) $(LDFLAGS) -Wl,-rpath $(CAFFE_DIR)/distribute/lib

$(SRC_OBJS): | objdir

objdir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
