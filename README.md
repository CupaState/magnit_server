# magnit_server
Client reads .csv file, and send the data to server. Server receives the data from client, process it, writes protocol file and returns to client number of writes in source data. Client writes it number to protocol file

## build
In root directory:
- cmake .
- make -j10

## run
**Server**
In server directory:
- ./server

**Client**
In client directory:
- ./client <path_to_file.csv>
