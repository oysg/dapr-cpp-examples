// ------------------------------------------------------------------------
// My Test || helloworld
// ------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>

#include "helloworld_app_server_impl.h"

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

namespace dapr_cpp_helloworld_example {

Status HelloworldAppServerImpl::OnInvoke(
  ServerContext* context,
  const InvokeRequest* request,
  InvokeResponse* response) {
  
  std::cout << "OnInvoke() is called"  << std::endl;

  if (request->method() == "helloworld") {
    std::cout << "client request: " << request->data().value() << std::endl;
    std::string resp_str = "This is helloworld server.";
    response->mutable_data()->set_value(resp_str);
  }

  return Status::OK;
}

Status HelloworldAppServerImpl::ListTopicSubscriptions(
  ServerContext* context,
  const Empty* request,
  ListTopicSubscriptionsResponse* response)  {
  std::cout << "ListTopicSubscriptions() is called"  << std::endl;
  return Status::OK;
}

Status HelloworldAppServerImpl::ListInputBindings(
  ServerContext* context,
  const Empty* request,
  ListInputBindingsResponse* response)  {
  std::cout << "ListInputBindings() is called" << std::endl;
  return Status::OK;
}

Status HelloworldAppServerImpl::OnBindingEvent(
  ServerContext* context,
  const BindingEventRequest* request,
  BindingEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;
  return Status::OK;
}

Status HelloworldAppServerImpl::OnTopicEvent(
  ServerContext* context,
  const TopicEventRequest* request,
  TopicEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;
  return Status::OK;
}

} // namespace dapr_cpp_helloworld_example
