SHELL = /bin/bash

HOMEDIR=/home/zhangfengli/cpp-sdk/examples

ALLLIBS: CLIENT_APP HELLOWORLD_APP MONITORING_APP SHOWTIME_APP

CLIENT_APP:
	${MAKE} -C $(HOMEDIR)/client_app

HELLOWORLD_APP:
	${MAKE} -C $(HOMEDIR)/helloworld_app

MONITORING_APP:
	${MAKE} -C $(HOMEDIR)/monitoring_app

SHOWTIME_APP:
	${MAKE} -C $(HOMEDIR)/showtime_app

.PHONY : clean
clean: 
	@${MAKE} clean -C $(HOMEDIR)/client_app
	@${MAKE} clean -C $(HOMEDIR)/helloworld_app
	@${MAKE} clean -C $(HOMEDIR)/monitoring_app
	@${MAKE} clean -C $(HOMEDIR)/showtime_app