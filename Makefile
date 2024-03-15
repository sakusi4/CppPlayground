CXX = /usr/bin/g++
CHMOD=chmod
CP=cp
TARGET = playground
BIN=./bin

VCPKG_ROOT=/home/junpark/projects/vcpkg
VCPKG_INCLUDE=$(VCPKG_ROOT)/installed/x64-linux/include
VCPKG_LIB=$(VCPKG_ROOT)/installed/x64-linux/lib

CXXFLAGS = -g -Wno-deprecated

SRC_DIRS = . patterns tools
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

LIBS = -lcpp_redis -ltacopie -ljsoncpp -lcurl -lssl -lcrypto -lz
LDFLAGS = -I$(VCPKG_INCLUDE) -L$(VCPKG_LIB) $(LIBS)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -g -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -I$(VCPKG_INCLUDE) -c -O0 -o $@ $<

install: all
	$(CHMOD) 755 $(TARGET) 
	$(CP) $(TARGET) $(BIN)

clean :
	rm -f $(OBJS) $(TARGET)
