import socket
import os

HOST = '127.0.0.1'
PORT = 8080

def HTTP_Response(request, status_code, message, data=''):
    response = request[0].split(' ')[2] + ' ' + status_code + ' ' + message + '\r\n'
    response += 'Content-Type: text/html\r\n'
    response += '\r\n\r\n' + data
    return response

def HTTP_Request_GET(request):
    path = request[0].split(' ')[1]
    if path == '/':
        path = './index.html'
    else:
        path = '.' + path
    try:
        with open(path, 'r', encoding='utf-8') as html_file:
            html_data = html_file.read()
        return HTTP_Response(request, '200', 'OK', html_data)
    except FileNotFoundError:
        with open('./pageNotFound.html', encoding='utf-8') as html_file:
            html_data = html_file.read()
        return HTTP_Response(request, '404', 'Not Found', html_data)

def HTTP_Request_POST(request):
    path = request[0].split(' ')[1]
    path = '.' + path
    try:
        with open(path, 'w', encoding='utf-8') as html_file:
            html_file.write(request[-1])
        return HTTP_Response(request, '200', 'OK', '<h1>File created successfully</h1>')
    except Exception as e:
        return HTTP_Response(request, '500', 'Internal Server Error', '<h1>500 Internal Server Error</h1>')

def HTTP_Request_HEAD(request):
    path = request[0].split(' ')[1]
    path = '.' + path
    try:
        file_size = os.path.getsize(path)
        return HTTP_Response(request, '200', 'OK', f'<h1>File size: {file_size} bytes</h1>')
    except FileNotFoundError:
        with open('./pageNotFound.html', encoding='utf-8') as html_file:
            html_data = html_file.read()
        return HTTP_Response(request, '404', 'Not Found', html_data)

def HTTP_Request_PUT(request):
    return HTTP_Request_POST(request)

def HTTP_Request_DELETE(request):
    path = request[0].split(' ')[1]
    path = '.' + path
    try:
        os.remove(path)
        return HTTP_Response(request, '200', 'OK', '<h1>File deleted successfully</h1>')
    except FileNotFoundError:
        with open('./pageNotFound.html', encoding='utf-8') as html_file:
            html_data = html_file.read()
        return HTTP_Response(request, '404', 'Not Found', html_data)

def authenticate(request):
    for header in request:
        if header.startswith('Cookie:'):
            cookie = header[8:]
            if cookie == 'username=admin':
                return True
    return False

def HTTP_Request(request):
    if not authenticate(request):
        return HTTP_Response(request, '403', 'Forbidden', '<h1>403 Forbidden</h1>')
    
    method = request[0].split(' ')[0]
    if method == 'GET':
        return HTTP_Request_GET(request)
    elif method == 'POST':
        return HTTP_Request_POST(request)
    elif method == 'HEAD':
        return HTTP_Request_HEAD(request)
    elif method == 'PUT':
        return HTTP_Request_PUT(request)
    elif method == 'DELETE':
        return HTTP_Request_DELETE(request)
    else:
        return HTTP_Response(request, '400', 'Bad Request', '<h1>400 Bad Request</h1>')

if __name__ == '__main__':
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)

    while True:
        client, addr = server.accept()
        http_request = client.recv(1024).decode()
        print(http_request)
        http_request = http_request.split('\r\n')
        response = HTTP_Request(http_request)
        client.send(response.encode())
        client.close()