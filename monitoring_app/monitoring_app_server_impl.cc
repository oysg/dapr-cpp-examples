// ------------------------------------------------------------------------
// My Test || monitoring
// ------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>

#include "monitoring_app_server_impl.h"

using grpc::ServerContext;
using grpc::Status;

using google::protobuf::Any;
using google::protobuf::Empty;
using google::protobuf::Metadata;

using dapr::proto::common::v1::InvokeRequest;
using dapr::proto::common::v1::InvokeResponse;
using dapr::proto::runtime::v1::ListTopicSubscriptionsResponse;
using dapr::proto::runtime::v1::TopicSubscription;
using dapr::proto::runtime::v1::ListInputBindingsResponse;
using dapr::proto::runtime::v1::BindingEventRequest;
using dapr::proto::runtime::v1::BindingEventResponse;
using dapr::proto::runtime::v1::TopicEventRequest;
using dapr::proto::runtime::v1::TopicEventResponse;

namespace dapr_cpp_monitoring_example {

const std::string PUBSUB_NAME = "pubsub";
const std::string TOPIC_NAME = "monitoring";

Status MonitoringAppServerImpl::OnInvoke(
  ServerContext* context,
  const InvokeRequest* request,
  InvokeResponse* response) {
  std::cout << "OnInvoke() is called"  << std::endl;
  return Status::OK;
}

Status MonitoringAppServerImpl::ListTopicSubscriptions(
  ServerContext* context,
  const Empty* request,
  ListTopicSubscriptionsResponse* response)  {
  std::cout << "ListTopicSubscriptions() is called"  << std::endl;

  TopicSubscription *topic = response->add_subscriptions();

  topic->set_pubsub_name(PUBSUB_NAME);
  topic->set_topic(TOPIC_NAME);

  return Status::OK;
}

Status MonitoringAppServerImpl::ListInputBindings(
  ServerContext* context,
  const Empty* request,
  ListInputBindingsResponse* response)  {
  std::cout << "ListInputBindings() is called" << std::endl;
  return Status::OK;
}

Status MonitoringAppServerImpl::OnBindingEvent(
  ServerContext* context,
  const BindingEventRequest* request,
  BindingEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;
  return Status::OK;
}

Status MonitoringAppServerImpl::OnTopicEvent(
  ServerContext* context,
  const TopicEventRequest* request,
  TopicEventResponse* response)  {
  std::cout << "OnBindingEvent() is called"  << std::endl;

  if (request->pubsub_name() == "pubsub")
  {
    if (request->topic() == "monitoring")
    {
      std::cout << "OnTopicEvent:" << request->data() << std::endl;
    }
  }
  return Status::OK;
}

} // namespace dapr_cpp_monitoring_example
