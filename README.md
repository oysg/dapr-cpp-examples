# dapr-cpp-examples

一.使用dapr对服务接口进行访问

1.启动服务

dapr run --app-id helloworld_app --components-path ../components/ --app-protocol grpc --app-port 6200 ./helloworld_app 6200

2.使用dapr调用helloworld服务

dapr invoke --app-id helloworld_app --method helloworld_app


二.使用http方式对服务接口进行访问

1.启动服务

dapr run --app-id monitoring_app --components-path ../components/ --dapr-http-port 6500 --app-port 6000  ./monitoring_app 6000

注：报错：state store is not configured，要配置该文件statestore.yaml

2.使用dapr调用monitoring服务

  保存状态

  curl -X POST -H "Content-Type: application/json" -d '[{ "key": "name", "value": "Bruce Wayne"}]' http://localhost:6500/v1.0/state/statestore

  获取状态

  curl http://localhost:6500/v1.0/state/statestore/name
