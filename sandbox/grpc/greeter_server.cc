#include "sandbox/grpc/helloworld.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>

class GreeterServiceImpl : public helloworld::Greeter::Service
{
public:
  grpc::Status SayHello(grpc::ServerContext* context,
                        const helloworld::HelloRequest* request,
                        helloworld::HelloReply* reply)
  {
    std::string prefix{"Hello "};
    reply->set_message(prefix + request->name());
    return grpc::Status::OK;
  }
};

int main(int argc, char** argv)
{
  std::string server_address = "0.0.0.0:50051";

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  GreeterServiceImpl service;
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
  std::cout << "Server listening on " << server_address << '\n';

  server->Wait();
}
