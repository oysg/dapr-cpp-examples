# dapr-cpp-examples

一.使用dapr对服务接口进行访问

1.启动服务

dapr run --app-id helloworld_app --components-path ../components/ --app-protocol grpc --app-port 6200 ./helloworld_app 6200

2.使用dapr调用helloworld服务

dapr invoke --app-id helloworld_app --method helloworld_app

