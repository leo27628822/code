import socket
import os
from datetime import datetime

HOST = '127.0.0.1'
PORT = 8080

UPLOAD_DIR = './uploads'

def HTTP_Request_GET(request):
    path = request[0].split(' ')[1]
    if path == '/old_page.html':
        new_location = '/index.html'
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
        response += 'Set-Cookie:' + 'username=admin' + '\r\n'
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

def parse_parts(body, boundary):
    parts = body.split(boundary)[1:-1]
    result = []
    for part in parts:
        headers_section, body = part.split(b'\r\n\r\n', 1)
        headers = parse_header(headers_section.decode())
        result.append((headers, body))
    return result

def HTTP_Request_POST(request):
    request = '\r\n'.join(request)
    headers_section, body = request.split('\r\n\r\n', 1)
    
    # Remove any extra '\r\n' between the headers and the body
    if body.startswith('\r\n'):
        body = body[2:]

    headers = parse_header(headers_section)
    
    content_type = headers.get('Content-Type', '')
    content_length = int(headers.get('Content-Length', '0'))

    response = 'HTTP/1.1 200 OK\r\n'
    response += 'Content-Type: text/html\r\n'
    response += '\r\n'

    if 'multipart/form-data' in content_type:
        
        boundary = content_type.split('boundary=')[1].encode()
        boundary = b'\r\n--' + boundary
        parts = parse_parts(body.encode(), boundary)

        for part_headers, part_body in parts:
            
            content_disposition = part_headers.get('Content-Disposition', '')
            filename = None
            for segment in content_disposition.split(';'):
                segment = segment.strip()
                if segment.startswith('filename='):
                    filename = segment.split('=')[1].strip('"')

            if filename:
                print(f"Filename: {filename}")
                print(f"Content: {part_body}")
                try:
                    
                    file_path = os.path.join(UPLOAD_DIR, filename)
                    with open(file_path, 'wb') as f:
                        f.write(part_body)

                    # return the content of success.html
                    with open('success.html', 'r') as success_file:
                        success_content = success_file.read()
                    response += success_content
                    return response.encode()

                except Exception as e:
                    print(f"An error occurred: {e}")
                    response = 'HTTP/1.1 500 Internal Server Error\r\n'
                    response += 'Content-Type: text/html\r\n'
                    response += '\r\n' + '<h1>500 Internal Server Error</h1>'
                    return response.encode()
        
        response += '<h1>200 OK</h1>'
        return response.encode()

    elif content_length > 0:
        
        # Handle other POST data here
        response += '<h1>200 OK</h1>'
        return response.encode()

    else:
        # Handle cases where there is no POST data
        response += '<h1>200 OK</h1>'
        return response.encode()

def HTTP_Request_HEAD(request):
    path = request[0].split(' ')[1]
    if path == '/':
        path = './index.html'
    else:
        path = '.' + path
    try:
        # Check if the file exists
        if os.path.isfile(path):
            # Get the size of the file
            file_size = os.path.getsize(path)
            response = request[0].split(' ')[2] + ' 200 OK\r\n'
            # Add some basic headers
            response += 'Date: {}\r\n'.format(datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT'))
            response += 'Content-Type: text/html\r\n'
            response += 'Content-Length: {}\r\n'.format(file_size)
            # Note: headers in request are not usually echoed back in the response. 
            # But I'm leaving this code in case you need it for something.
            for header in request[1:]:
                response = response + header + '\r\n'
            # Add ending characters
            response += '\r\n'
            return response
        else:
            raise FileNotFoundError
    
    except FileNotFoundError as e:
        response = request[0].split(' ')[2] + ' 404 Not Found\r\n'
        # Add some basic headers
        response += 'Date: {}\r\n'.format(datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT'))
        response += 'Content-Type: text/html\r\n'
        # Note: headers in request are not usually echoed back in the response. 
        # But I'm leaving this code in case you need it for something.
        for header in request[1:]:
            response = response + header + '\r\n'
        # Add ending characters
        response += '\r\n'
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

def HTTP_301_Redirect(request, new_location):
    response = request[0].split(' ')[2] + ' 301 Moved Permanently\r\n'
    response += 'Location: http://127.0.0.1:8080' + new_location + '\r\n'
    response += '\r\n'
    return response

def HTTP_505_Version_Not_Supported(request):
    response = 'HTTP/1.1 505 HTTP Version Not Supported\r\n'
    response += '\r\n'
    return response

def parse_header(header_section):
    headers = {}

    header_lines = header_section.split('\r\n')
    for line in header_lines:
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

def HTTP_Request(request):
    if not authenticate(request):
        response = request[0].split(' ')[2] + ' 403 Forbidden\r\n'
        response = response + '\r\n' + 'Content-Type: text/html\r\n'
        response = response + '\r\n\r\n' + '<h1>403 Forbidden</h1>'
        return response
    
    # 檢查版本號，如果版本號不是HTTP/1.1，返回HTTP_505_Version_Not_Supported響應
    http_version = request[0].split(' ')[2]
    if http_version != 'HTTP/1.1':
        return HTTP_505_Version_Not_Supported(request).encode()

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
        return HTTP_Bad_Request(request)

def receive_request(conn):
    data = conn.recv(2048)  # receive initial data
    request = data.decode()

    # extract content-length value from headers
    headers = parse_header(request.split('\r\n\r\n', 1)[0])
    content_length = int(headers.get('Content-Length', '0'))

    # receive remaining data
    while len(request.encode()) < content_length:
        data = conn.recv(1024)
        request += data.decode()

    return request

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_DIR):
        os.makedirs(UPLOAD_DIR)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server.bind((HOST, PORT))
    server.listen(5)

    while True:
        client, addr = server.accept()
        http_request = receive_request(client)
        print("TEST", http_request)
        #print("TEST", http_request)
        print( http_request )
        http_request = http_request.split('\r\n')
        response = HTTP_Request( http_request )

        if isinstance(response, bytes):
            print( response )
            client.sendall(response)
        else:
            print( response )
            client.sendall(response.encode())
        client.close()
        print()