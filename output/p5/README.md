# Program 5 - chat server&client

## TOC

- [Program 5 - chat server&client](#program-5---chat-serverclient)
  - [TOC](#toc)
  - [Program description](#program-description)
    - [Output](#output)
      - [Invalid arguments](#invalid-arguments)
      - [Working input - one client](#working-input---one-client)
      - [Working input - multiple clients](#working-input---multiple-clients)

## Program description

The communication process follows a minimal process:
1. Party 1 sends the size of string to be sent as an unsigned 16 bit integer
2. Party 2 recieves the size of string to be received as an unsigned 16 bit integer 
3. Party 1 sends the string
4. Party 2 receives the string

The server is designed to be concurrent, and both the server and client operate with two threads per operation being done. 
The client is divided into two processes where:
1. Reader - Reads from the TCP connection and prints messages from the server
2. Writer - Writes data from stdin onto the TCP connection.
A similar paradigm is used in the server to maintain the I/O

### Output

#### Invalid arguments

The server does not receive the connection as the client cannot establish a connection without a provided address.

![Invargs](Screenshot%20from%202020-11-23%2016-34-49.png)

#### Working input - one client

One client can communicate with the server, and both the server handle input and output independently.

![Single client-server](Screenshot%20from%202020-11-23%2016-32-04.png)

#### Working input - multiple clients

Multiple clients can communicate with server.
The server can send inputs in a FIFO manner to each client too.

![MC](Screenshot%20from%202020-11-23%2016-29-24.png)