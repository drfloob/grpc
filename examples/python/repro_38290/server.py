from concurrent import futures
import grpc
from helloworld_pb2 import HelloReply
import helloworld_pb2_grpc


class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, context):
        reply = HelloReply()
        reply.message = "Hello, " + request.name
        return reply


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=5))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()


if __name__ == "__main__":
    serve()
