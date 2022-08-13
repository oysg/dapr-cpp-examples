// ------------------------------------------------------------
// My Test || showtime
// ------------------------------------------------------------

#include <grpcpp/grpcpp.h>

#include "dapr/proto/common/v1/common.pb.h"
#include "dapr/proto/runtime/v1/appcallback.grpc.pb.h"
#include "dapr/proto/runtime/v1/dapr.grpc.pb.h"

using grpc::ClientContext;
using grpc::ServerContext;
using grpc::Status;

using google::protobuf::Any;
using google::protobuf::Empty;

using dapr::proto::common::v1::InvokeRequest;
using dapr::proto::common::v1::InvokeResponse;
using dapr::proto::runtime::v1::AppCallback;
using dapr::proto::runtime::v1::ListTopicSubscriptionsResponse;
using dapr::proto::runtime::v1::ListInputBindingsResponse;
using dapr::proto::runtime::v1::BindingEventRequest;
using dapr::proto::runtime::v1::BindingEventResponse;
using dapr::proto::runtime::v1::TopicEventRequest;
using dapr::proto::runtime::v1::TopicEventResponse;

using dapr::proto::runtime::v1::Dapr;
using dapr::proto::runtime::v1::PublishEventRequest;


namespace dapr_cpp_showtime_example {
  
class ShowtimeAppServerImpl final : public AppCallback::Service {
  public:
    Status OnInvoke(ServerContext* context, const InvokeRequest* request, InvokeResponse* response) override;
    Status ListTopicSubscriptions(ServerContext* context, const Empty* request, ListTopicSubscriptionsResponse* response) override;
    Status ListInputBindings(ServerContext* context, const Empty* request, ListInputBindingsResponse* response) override;
    Status OnBindingEvent(ServerContext* context, const BindingEventRequest* request, BindingEventResponse* response) override;
    Status OnTopicEvent(ServerContext* context, const TopicEventRequest* request, TopicEventResponse* response) override;

    void SetClientStub(std::shared_ptr<Dapr::Stub> client);
    std::string PublishEvent();
  private:
    std::shared_ptr<Dapr::Stub> client_stub_;
};

} // namespace dapr_cpp_showtime_example
