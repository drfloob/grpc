import time
import traceback
import grpc
from helloworld_pb2 import HelloRequest
import helloworld_pb2_grpc


def main():
    channel = grpc.insecure_channel("localhost:50051")
    stub = helloworld_pb2_grpc.GreeterStub(channel)
    message = HelloRequest()
    message.name = "arst"
    while True:
        try:
            reply = stub.SayHello(message)
            print(reply.message)
        except Exception:
            print(traceback.format_exc())
        time.sleep(0.1)


if __name__ == "__main__":
    main()
