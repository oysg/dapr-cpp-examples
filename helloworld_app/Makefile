# ------------------------------------------------------------
# My Test || helloworld
# ------------------------------------------------------------

HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11 -I ../../src 
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -lgrpc++_reflection\
           -ldl\
           -lstdc++
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl\
           -lstdc++
endif

DAPR_SRC_ROOT = ../../src/dapr/proto

all: helloworld_app

helloworld_app: $(DAPR_SRC_ROOT)/common/v1/common.pb.o $(DAPR_SRC_ROOT)/runtime/v1/dapr.pb.o $(DAPR_SRC_ROOT)/runtime/v1/dapr.grpc.pb.o $(DAPR_SRC_ROOT)/runtime/v1/appcallback.pb.o $(DAPR_SRC_ROOT)/runtime/v1/appcallback.grpc.pb.o helloworld_app_server_impl.o helloworld_app.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o helloworld_app
