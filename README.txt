to run chatserve enter the following:
    python chatserve.py "portnumber"
where "portnumber" is the port on which the server will be listening
enter "\quit" to end the current connection and resume listening on "portnumber"
use "Ctrl+c" to stop the server running

 compile chatclient first with the following command:
    make chatclient
to run chatclient enter the following:
    chatclient "hostname" "portnumber"
where "hostname" is where chatserve is currently running and "portnumber" is the port chatserve is listening on
enter "\quit" to end the connection and exit chatclient

chatserve was tested using flip2.engr.oregonstate.edu
chatclient was tested using flip3.engr.oregonstate.edu