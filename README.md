## Port Scanner using C++ and Linux Sockets
This simple port scanner written in C++ utilizes Linux sockets to scan a range of ports on a specified host. It allows you to specify the start and end port range as command-line arguments.
### Usage
```
./port_scanner <host> <start_port> <end_port>
```
<host>: The IP address or domain name to scan.
<start_port>: The starting port number of the range.
<end_port>: The ending port number of the range.


### Example
```
./port_scanner example.com 80 100
```

### Dependencies
- C++11 or higher
- Linux environment
- Standard C++ libraries
