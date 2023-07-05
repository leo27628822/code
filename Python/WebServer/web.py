import socket
import os

HOST = '127.0.0.1'
PORT = 8080

def HTTP_Request_GET(request):
    path = request[0].split(' ')[1]
    if path == '/old_page.html':
        new_location = '/new_page.html'
        return HTTP_301_Redirect(request, new_location)

    if path == '/':
        path = './index.html'
    else:
        path = '.' + path
    try:
        # if the file is a binary file, open with 'rb'
        with open(path, 'rb') as file:
            data = file.read()

        response = request[0].split(' ')[2] + ' 200 OK\r\n'
        response += 'Content-Type: application/octet-stream\r\n'
        response += 'Content-Disposition: attachment; filename="{}"\r\n'.format(path.split('/')[-1])
        response += 'Content-Length: {}\r\n'.format(len(data))
        response += '\r\n'
        return response.encode() + data

    except FileNotFoundError as e:
        html_file = open( './pageNotFound.html', encoding = 'utf-8' )
        html_data = html_file.read()
        response = request[0].split(' ')[2] + ' 404 Not Found\r\n'
        index = 0
        for header in request :
            if index != 0 and index != 1 :
                response = response + '\r\n' + header 
            index += 1
        response = response + '\r\n' + html_data
        return response.encode()
    
def HTTP_Request_POST(request):
    path = request[0].split(' ')[1]
    if path == '/':
        response = request[0].split(' ')[2] + ' 400 Bad Request\r\n'
        response = response + '\r\n' + 'Content-Type: text/html\r\n'
        response = response + '\r\n\r\n' + '<h1>400 Bad Request</h1>'
        return response

    # Assume the file name is in the request URI
    filename = path.strip('/')
    # Assume the file data is in the last line of the request
    file_data = request[-1]  
    try:
        with open(filename, 'w', encoding='utf-8') as f:
            f.write(file_data)
    except Exception as e:
        response = request[0].split(' ')[2] + ' 500 Internal Server Error\r\n'
        response = response + '\r\n' + 'Content-Type: text/html\r\n'
        response = response + '\r\n\r\n' + '<h1>500 Internal Server Error</h1>'
        return response

    response = request[0].split(' ')[2] + ' 200 OK\r\n'
    response = response + '\r\n' + 'Content-Type: text/html\r\n'
    response = response + '\r\n\r\n' + '<h1>200 OK</h1>'
    return response

def HTTP_Request_HEAD(request):
    path = request[0].split(' ')[1]
    if path == '/':
        path = './index.html'
    else:
        path = '.' + path
    try:
        html_file = open(path, 'r', encoding='utf-8')
        html_file.close()
        response = request[0].split(' ')[2] + ' 200 OK\r\n'
        index = 0
        for header in request:
            if index != 0 and index != 1:
                response = response + '\r\n' + header 
            index += 1
        return response
    
    except FileNotFoundError as e:
        response = request[0].split(' ')[2] + ' 404 Not Found\r\n'
        index = 0
        for header in request:
            if index != 0 and index != 1:
                response = response + '\r\n' + header 
            index += 1
        return response
    
def HTTP_Request_PUT(request):
    path = request[0].split(' ')[1]
    if path == '/':
        response = request[0].split(' ')[2] + ' 400 Bad Request\r\n'
        response += '\r\n' + 'Content-Type: text/html\r\n'
        response += '\r\n\r\n' + '<h1>Cannot PUT to /</h1>'
        return response
    else:
        path = '.' + path
        data = request[-1]  # 假設數據在請求的最後一行
        with open(path, 'w', encoding='utf-8') as file:
            file.write(data)
        response = request[0].split(' ')[2] + ' 200 OK\r\n'
        response += '\r\n' + 'Content-Type: text/html\r\n'
        response += '\r\n\r\n' + '<h1>PUT data received</h1>'
        return response

def HTTP_Request_DELETE(request):
    path = request[0].split(' ')[1]
    if path == '/':
        response = request[0].split(' ')[2] + ' 400 Bad Request\r\n'
        response += '\r\n' + 'Content-Type: text/html\r\n'
        response += '\r\n\r\n' + '<h1>Cannot DELETE /</h1>'
        return response
    else:
        path = '.' + path
        if os.path.exists(path):
            os.remove(path)
            response = request[0].split(' ')[2] + ' 200 OK\r\n'
            response += '\r\n' + 'Content-Type: text/html\r\n'
            response += '\r\n\r\n' + '<h1>Resource deleted</h1>'
            return response
        else:
            response = request[0].split(' ')[2] + ' 404 Not Found\r\n'
            response += '\r\n' + 'Content-Type: text/html\r\n'
            response += '\r\n\r\n' + '<h1>Resource not found</h1>'
            return response

def HTTP_Bad_Request( request ) :
    response = request[0].split(' ')[2] + ' 400 Bad Request\r\n'
    response = response + '\r\n' + 'Content-Type: text/html\r\n'
    response = response + '\r\n\r\n' + '<h1>400 Bad Request</h1>'
    return response

def create_http_response(header, file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            data = file.read()

        response = header + '\r\n'
        response += 'Content-Length: ' + str(len(data)) + '\r\n'
        response += 'Content-Type: text/html; charset=utf-8' + '\r\n'
        response += '\r\n' + data

        return response

    except FileNotFoundError:
        return header + ' 404 Not Found\r\n\r\nFile Not Found'

def HTTP_301_Redirect(request, new_location):
    response = request[0].split(' ')[2] + ' 301 Moved Permanently\r\n'
    response += 'Location: http://127.0.0.1:8080' + new_location + '\r\n'
    response += '\r\n'
    return response

def HTTP_505_Version_Not_Supported(request):
    response = 'HTTP/1.1 505 HTTP Version Not Supported\r\n'
    response += '\r\n'
    return response

def parse_header(request):
    headers = {}

    request_lines = request.split('\r\n')
    for line in request_lines[1:]:  # skip the request line
        if ':' in line:  # header lines
            name, value = line.split(':', 1)
            headers[name.strip()] = value.strip()

    return headers

def authenticate(request):
    for header in request:
        if header.startswith('Cookie: '):
            cookie = header[8:]
            if cookie == 'username=admin':
                return True
    return False

def HTTP_Request( request ) :
    if not authenticate(request):
        response = request[0].split(' ')[2] + ' 403 Forbidden\r\n'
        response = response + '\r\n' + 'Content-Type: text/html\r\n'
        response = response + '\r\n\r\n' + '<h1>403 Forbidden</h1>'
        return response
    
    # 检查版本号，如果版本号不是HTTP/1.1，返回HTTP_505_Version_Not_Supported响应
    http_version = request[0].split(' ')[2]
    if http_version != 'HTTP/1.1':
        return HTTP_505_Version_Not_Supported(request)
    
    headers = parse_header('\r\n'.join(request))
    print(headers)  # 打印头部信息，实际使用时可能不需要这一行

    if request[0].split(' ')[0] == 'GET':
        return HTTP_Request_GET(request)
    elif request[0].split(' ')[0] == 'POST':
        return HTTP_Request_POST(request)
    elif request[0].split(' ')[0] == 'HEAD':
        return HTTP_Request_HEAD(request)
    elif request[0].split(' ')[0] == 'PUT':
        return HTTP_Request_PUT(request)
    elif request[0].split(' ')[0] == 'DELETE':
        return HTTP_Request_DELETE(request)
    else:
        return HTTP_Bad_Request(request)

if __name__ == '__main__':
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server.bind((HOST, PORT))
    server.listen(5)

    while True:
        client, addr = server.accept()
        http_request = client.recv(1024).decode()
        print( http_request )
        http_request = http_request.split('\r\n')
        response = HTTP_Request( http_request )
        if isinstance(response, bytes):
            client.send(response)
        else:
            client.send(response.encode())
        client.close()