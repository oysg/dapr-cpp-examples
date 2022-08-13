#! /bin/sh

HOME_DIR=/home/zhangfengli/cpp-sdk/examples
MONITORING_DIR=$HOME_DIR/monitoring_app
SHOWTIME_DIR=$HOME_DIR/showtime_app
HELLOWORLD_DIR=$HOME_DIR/helloworld_app
CLIENT_DIR=$HOME_DIR/client_app
LOGS_DIR=$HOME_DIR/logs

dapr stop --app-id client_app
dapr stop --app-id helloworld_app
dapr stop --app-id showtime_app
dapr stop --app-id monitoring_app

echo "Stop All Service.........." | tee $LOGS_DIR/dapr.log