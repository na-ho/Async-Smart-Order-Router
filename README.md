# Async Smart Order Router
Async Smart Order Router is a FIX protocol smart order router implement with asynchronous design and distributed system design.  
To archive ultra low latency, the project is a low-level implementation.

## Status
This project is in a proof of concept state.   
But can run to prove all of the designs.

## Design
The project is designed with low latency and scalability in mind.  
With distributed system design approach, each service communicates via a message broker for scalability and load balancing.  
At first, the project started with kernel bypass. F-Stack with Intel DPDK then Seastar framework.  
Due to time constraints, switch to Boost Asio and redesign architecture.  

## Services
Currently, it has 3 services.
1.	FIX Gateway, to communicate with clients
2.	SOR, as the main service to calculate routing of the orders
3.	Market Gateway, for connecting with various market venues

In the future will have custom API and REST API

![Image of System](https://raw.githubusercontent.com/na-ho/Async-Smart-Order-Router/master/Doc/SystemArchitecture.png)

## Distributed
As mention, all services are distributed systems.  
Fix Gateway, distributed connection among clients and send to SOR  
SOR, receive commands from Fix Gateway and Market Gateway (currently, from Fix Gateway that has load balancing)  
Market Gateway, can have multiple services as needed but have to consider the limit of target markets that depend on agreement with the markets

## Technology
1.	C++ for all services.
2.	NATS for the messaging system. 
	(As various benchmarks show low latency than other Message brokers including ZeroMQ, Kafka)
3.	Flatbuffers for serialization. 
	(As it seems the best performance serialization library(faster than Protocol buffers))
4.	Boost Asio for low-level networking.
5.	libcuckoo for concurrency hashmap.
	(From a benchmark, it is faster than Intel Threading Building Blocks and folly)
6.	hffix for high-performance FIX Parser library.

C++ : at least C++11 for lambda expression, the project is set at c++17  
Build tool : CMake  
Message Broker : NATS 2.0  
Serialization library : FlatBuffers  
Library : libcuckoo, hffix, fast_float  

## Running
1.	Start NATS server
2.	Start Fix Gateway
3.	Start SOR
4.	Start Market Gateway
5.	Testing with Mini-Fix for clientes and Market Gateway
