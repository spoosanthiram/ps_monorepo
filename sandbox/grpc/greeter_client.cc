#include "sandbox/grpc/helloworld.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

class GreeterClient
{
public:
  GreeterClient(std::shared_ptr<grpc::Channel> channel) : stub_{helloworld::Greeter::NewStub(channel)} {}

  std::string SayHello(const std::string& user);

private:
  std::unique_ptr<helloworld::Greeter::Stub> stub_;
};

std::string GreeterClient::SayHello(const std::string& user)
{
  helloworld::HelloRequest request;
  request.set_name(user);

  grpc::ClientContext context;
  helloworld::HelloReply reply;
  grpc::Status status = stub_->SayHello(&context, request, &reply);
  if (status.ok()) {
    return reply.message();
  }

  std::cout << status.error_code() << ": " << status.error_message() << '\n';
  return "gRPC failed";
}

int main(int argc, char** argv)
{
  std::string server_address = "localhost:50051";
  std::cout << "Client querying server address: " << server_address << '\n';

  GreeterClient greeter{grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials())};

  std::string reply = greeter.SayHello("world");
  std::cout << "Greeter received: " << reply << '\n';

  return 0;
}
