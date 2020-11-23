# Program 6 - Echo client/Server

## TOC
- [Program 6 - Echo client/Server](#program-6---echo-clientserver)
  - [TOC](#toc)
  - [Program Description](#program-description)
    - [TCP](#tcp)
    - [UDP](#udp)
  - [TCP - Iterative](#tcp---iterative)
    - [Output](#output)
      - [Client incorrect address](#client-incorrect-address)
      - [Successful echos](#successful-echos)
  - [TCP - Concurrent](#tcp---concurrent)
    - [Output](#output-1)
      - [Client incorrect address](#client-incorrect-address-1)
      - [Successful communication](#successful-communication)
      - [Multiple connections](#multiple-connections)
  - [UDP](#udp-1)
    - [Output](#output-2)
      - [Invalid arguments](#invalid-arguments)
      - [Working](#working)
      - [Invalid args](#invalid-args)

## Program Description

### TCP

The communication process is this minimal process:

1. Client sends string size to server
2. Client sends string to server
3. Server sends string back to client

The iterative and concurrent versions share the same client (As it is a design of the server)

### UDP

The communication process is this minimal process:
1. Client sends contant sized string
2. Server responds with string

The simplified model here is due to UDP being connectionless.

## TCP - Iterative

The server maintains one thread and responds with it. Multiple requests are queued for response, and dealt with in a FIFO manner.

### Output

#### Client incorrect address

Two cases are shown here:
1. Client cannot connect as server isn't running
2. Insufficient arguments provided

![Incorrect client](Screenshot%20from%202020-11-02%2015-31-05.png)


#### Successful echos

It can be seen that all the processes share the same pid, showing that the same process is being used

![Successful echoes](Screenshot%20from%202020-11-02%2015-28-47.png)

## TCP - Concurrent

The server forks to respond to the client. Additionally, a signal handler needs to be present, to remove the exit child processes after they have responded to the client. Although this allows communication with multiple clients at the same time, forking introduces a minimal amount of latency (the time taken for the program to fork).

### Output

#### Client incorrect address

Two cases are shown here:
1. Client cannot connect as server isn't running
2. Insufficient arguments provided

![Incorrect client](Screenshot%20from%202020-11-02%2015-31-05.png)

#### Successful communication

The different pids depict that the process forks in order to respond. This allows multiple clients to connect to the server and communicate with it at the same time.

![Concurrent successful](Screenshot%20from%202020-11-02%2015-37-36.png)

#### Multiple connections

The order of pids show that two or more connections can stay alive and the program can communicate with more than one client at the same time.

![Concurrent threads](Screenshot%20from%202020-11-09%2015-02-33.png)


## UDP

UDP's simple model implies that connection tracking is not done automatically. Hence, responses are send as soon as messages are received.

### Output

#### Invalid arguments

The client displays an error as the arguments are not provided.
UDP is connectionless, so presenting an invalid client will also work, but the server will not be able to respond.

![Invalid args](Screenshot%20from%202020-11-23%2014-17-07.png)

#### Working

The server echoes back the string to the client.

![Working response](Screenshot%20from%202020-11-23%2014-29-14.png)


#### Invalid args