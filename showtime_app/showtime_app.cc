// ------------------------------------------------------------
// My Test || showtime
// ------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "showtime_app_server_impl.h"
#include "dapr/proto/runtime/v1/dapr.grpc.pb.h"

using dapr::proto::runtime::v1::Dapr;
using dapr::proto::runtime::v1::InvokeServiceRequest;
using dapr::proto::runtime::v1::PublishEventRequest;
using dapr::proto::common::v1::InvokeRequest;
using dapr::proto::common::v1::InvokeResponse;

using grpc::Channel;
using grpc::ClientContext;
using grpc::ServerBuilder;
using grpc::Status;
using grpc::Server;

using google::protobuf::Any;

namespace dapr_cpp_showtime_example {

const std::string PUBSUB_NAME = "pubsub";
const std::string TOPIC_NAME = "monitoring";

class ShowtimeApp {
  public:
    ShowtimeApp(std::string dapr_grpc_port, std::string app_port)
      : dapr_grpc_port_(dapr_grpc_port), app_port_(app_port) {}

    void ConnectToDapr() {
      // Connect to dapr grpc server.
      std::cout << "Connecting to " << dapr_grpc_endpoint() << "..." << std::endl;
      client_stub_ = Dapr::NewStub(grpc::CreateChannel(dapr_grpc_endpoint(), grpc::InsecureChannelCredentials()));
      service_->SetClientStub(client_stub_);
    }

    std::string CallMethod(
      const std::string app_id, const std::string method,
      const std::string message) {
      ClientContext context;
      InvokeServiceRequest request;
      InvokeResponse response;

      return "";
    }

    std::string PublishEvent() {
      ClientContext context;
      Empty response;
      PublishEventRequest request;

      std::string strData = "This is showtime event.";
      request.set_pubsub_name(PUBSUB_NAME);
      request.set_topic(TOPIC_NAME);
      request.set_data(strData);

      Status status = client_stub_->PublishEvent(&context, request, &response);
      if (status.ok()) {
        return "successful";
      }

      std::cout << "code:" << status.error_code() << std::endl;
      return "RPC Error : " + status.error_message() + ", " + status.error_details();
    }

    void StartAppServer() {
      std::string endpoint = showtime_app_endpoint();
      service_ = std::shared_ptr<ShowtimeAppServerImpl>(new ShowtimeAppServerImpl());

      grpc::EnableDefaultHealthCheckService(true);
      grpc::reflection::InitProtoReflectionServerBuilderPlugin();

      ServerBuilder builder;
      builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
      builder.RegisterService(service_.get());
      
      // Start synchronous gRPC server.
      app_server_ = builder.BuildAndStart();
      std::cout << "Server listening on " << endpoint << std::endl;
    }

    void WaitUntilServerIsDown() {
      app_server_->Wait();
    }

  private:
    std::string showtime_app_endpoint() {
      return std::string("127.0.0.1:") + app_port_;
    }

    std::string dapr_grpc_endpoint() {
      return std::string("127.0.0.1:") + dapr_grpc_port_;
    }

    std::string app_port_;
    std::string dapr_grpc_port_;
    std::shared_ptr<Dapr::Stub> client_stub_;
    std::unique_ptr<Server> app_server_;
    std::shared_ptr<ShowtimeAppServerImpl> service_;
};

} // namepsace dapr_cpp_showtime_example

std::string GetEnvironmentVariable(const std::string& var) {
  const char* val = std::getenv(var.c_str());
  return (val == nullptr) ? "": val;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "showtime_app <app_port>" << std::endl;
    return 0;
  }

  std::string grpc_port = GetEnvironmentVariable("DAPR_GRPC_PORT");
  std::string app_port = std::string(argv[1]);
  
  if (grpc_port == "") grpc_port = "50001";
  std::unique_ptr<dapr_cpp_showtime_example::ShowtimeApp> app(new dapr_cpp_showtime_example::ShowtimeApp(grpc_port, app_port));

  // Start App Server
  app->StartAppServer();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  app->ConnectToDapr();
  //std::cout << app->PublishEvent() << std::endl;

  // Wait until server is down
  app->WaitUntilServerIsDown();

  return 0;
}
