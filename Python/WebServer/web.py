import socket

HOST = '127.0.0.1'
PORT = 8080

def HTTP_Request_GET( request ) :
    path = request[0].split(' ')[1]
    if path == '/' :
        path = './index.html'
    else :
        path = '.' + path
    try :
        html_file = open(path, 'r', encoding = 'utf-8' )
        html_data = html_file.read()
        response = request[0].split(' ')[2] + ' 200 OK\r\n'
        index = 0
        for header in request :
            if index != 0 and index != 1 :
                response = response + '\r\n' + header 
            index += 1
        response = response + '\r\n' + html_data
        return response
    
    except FileNotFoundError as e :
        html_file = open( './pageNotFound.html', encoding = 'utf-8' )
        html_data = html_file.read()
        response = request[0].split(' ')[2] + ' 404 Not Found\r\n'
        index = 0
        for header in request :
            if index != 0 and index != 1 :
                response = response + '\r\n' + header 
            index += 1
        response = response + '\r\n' + html_data
        return response
    
def HTTP_Request_POST( request ) :
    return request
    
def HTTP_Bad_Request( request ) :
    response = request[0].split(' ')[2] + ' 400 Bad Request\r\n'
    response = response + '\r\n' + 'Content-Type: text/html\r\n'
    response = response + '\r\n\r\n' + '<h1>400 Bad Request</h1>'
    return response

def HTTP_Request( request ) :
    if request[0].split(' ')[0] == 'GET' :
        return HTTP_Request_GET( request )
    elif request[0].split(' ')[0] == 'POST' :
        return HTTP_Request_POST( request )
    else :
        return HTTP_Bad_Request( request )

if __name__ == '__main__':
    # 创建socket对象
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 绑定IP和端口
    server.bind((HOST, PORT))
    server.listen(5)

    while True:
        
        client, addr = server.accept()
        http_request = client.recv(1024).decode()
        print( http_request )
        http_request = http_request.split('\r\n')
        response = HTTP_Request( http_request )
        client.send(response.encode())
        client.close()
