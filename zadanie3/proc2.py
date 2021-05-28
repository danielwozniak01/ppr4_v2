from spyne import Application, rpc, ServiceBase,String
from spyne.protocol.soap import Soap11
from spyne.server.wsgi import WsgiApplication
import socket
import sys
import time

class HelloWorldService(ServiceBase):
    @rpc(String ,  _returns=String)
    def say_hello(ctx, msg):
        print( msg )
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_address = ('localhost', 12345)
            sock.connect(server_address)
            sock.sendall(msg.encode('ascii'))         
            sock.close()
        except:
            print ('error:',sys.exc_info()[1])    
        return ''

application = Application([HelloWorldService],
    tns='ppr.hello',
    in_protocol=Soap11(),
    out_protocol=Soap11()
)
if __name__ == '__main__':
    # You can use any Wsgi server. Here, we chose
    # Python's built-in wsgi server but you're not
    # supposed to use it in production.
    from wsgiref.simple_server import make_server
    wsgi_app = WsgiApplication(application)
    server = make_server('0.0.0.0', 8080, wsgi_app)
    server.serve_forever()
