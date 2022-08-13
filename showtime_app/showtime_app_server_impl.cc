// ------------------------------------------------------------
// My Test || showtime
// ------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>
#include <ctime>

#include "showtime_app_server_impl.h"
#include "dapr/proto/runtime/v1/dapr.grpc.pb.h"

using grpc::ServerContext;
using grpc::Status;

using google::protobuf::Any;
using google::protobuf::Empty;

using dapr::proto::common::v1::InvokeRequest;
using dapr::proto::common::v1::InvokeResponse;
using dapr::proto::runtime::v1::ListTopicSubscriptionsResponse;
using dapr::proto::runtime::v1::ListInputBindingsResponse;
using dapr::proto::runtime::v1::BindingEventRequest;
using dapr::proto::runtime::v1::BindingEventResponse;
using dapr::proto::runtime::v1::TopicEventRequest;
using dapr::proto::runtime::v1::TopicEventResponse;

namespace dapr_cpp_showtime_example {

const std::string PUBSUB_NAME = "pubsub";
const std::string TOPIC_NAME = "monitoring";

void ShowtimeAppServerImpl::SetClientStub(std::shared_ptr<Dapr::Stub> client) {
  client_stub_ = client;
}

std::string ShowtimeAppServerImpl::PublishEvent() {
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

Status ShowtimeAppServerImpl::OnInvoke(
  ServerContext* context,
  const InvokeRequest* request,
  InvokeResponse* response) {  
  std::cout << "OnInvoke() is called"  << std::endl;

  // 基于当前系统的当前日期/时间
   time_t now = time(0);
   
   // 把 now 转换为字符串形式
   char* dt = ctime(&now);
   std::string strTime = dt;
   response->mutable_data()->set_value(strTime);

  PublishEvent();
  return Status::OK;
}

Status ShowtimeAppServerImpl::ListTopicSubscriptions(
  ServerContext* context,
  const Empty* request,
  ListTopicSubscriptionsResponse* response)  {
  std::cout << "ListTopicSubscriptions() is called"  << std::endl;
  return Status::OK;
}

Status ShowtimeAppServerImpl::ListInputBindings(
  ServerContext* context,
  const Empty* request,
  ListInputBindingsResponse* response)  {
  std::cout << "ListInputBindings() is called" << std::endl;
  return Status::OK;
}

Status ShowtimeAppServerImpl::OnBindingEvent(
  ServerContext* context,
  const BindingEventRequest* request,
  BindingEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;
  return Status::OK;
}

Status ShowtimeAppServerImpl::OnTopicEvent(
  ServerContext* context,
  const TopicEventRequest* request,
  TopicEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;
  return Status::OK;
}

} // namespace dapr_cpp_showtime_example
