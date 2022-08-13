#! /bin/sh

HOME_DIR=/home/zhangfengli/cpp-sdk/examples
MONITORING_DIR=$HOME_DIR/monitoring_app
SHOWTIME_DIR=$HOME_DIR/showtime_app
HELLOWORLD_DIR=$HOME_DIR/helloworld_app
CLIENT_DIR=$HOME_DIR/client_app
LOGS_DIR=$HOME_DIR/logs

cd $HOME_DIR

make clean && make

echo $HOME_DIR
echo "Start All Service.........." | tee $LOGS_DIR/dapr.log

dapr run --app-id monitoring_app --components-path $HOME_DIR/components/ --app-protocol grpc --app-port 6000  $MONITORING_DIR/monitoring_app 6000 >> $LOGS_DIR/dapr.log 2>&1 &

dapr run --app-id showtime_app --components-path $HOME_DIR/components/ --app-protocol grpc --app-port 6100 $SHOWTIME_DIR/showtime_app 6100 >> $LOGS_DIR/dapr.log 2>&1 &

dapr run --app-id helloworld_app --components-path $HOME_DIR/components/ --app-protocol grpc --app-port 6200 $HELLOWORLD_DIR/helloworld_app 6200 >> $LOGS_DIR/dapr.log 2>&1 &

dapr run --app-id client_app --components-path $HOME_DIR/components/ --app-protocol grpc --app-port 6300 $CLIENT_DIR/client_app 6300
