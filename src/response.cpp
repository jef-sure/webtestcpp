/*
 * response.cpp
 *
 *  Created on: Sep 20, 2016
 *      Author: anton
 */

#include "response.h"
#include <map>

struct std_response {
	string status;
	string body;
};

map<int, std_response> stdResponseMap = { //
		{ 200, { "HTTP/1.0 200 OK\r\n", "" } }, //
				{ 201, { "HTTP/1.0 201 Created\r\n", "<html>"
						"<head><title>Created</title></head>"
						"<body><h1>201 Created</h1></body>"
						"</html>" } }, //
				{ 202, { "HTTP/1.0 202 Accepted\r\n", "<html>"
						"<head><title>Accepted</title></head>"
						"<body><h1>202 Accepted</h1></body>"
						"</html>" } }, //
				{ 204, { "HTTP/1.0 204 No Content\r\n", "<html>"
						"<head><title>No Content</title></head>"
						"<body><h1>204 Content</h1></body>"
						"</html>" } }, //
				{ 300, { "HTTP/1.0 300 Multiple Choices\r\n", "<html>"
						"<head><title>Multiple Choices</title></head>"
						"<body><h1>300 Multiple Choices</h1></body>"
						"</html>" } }, //
				{ 301, { "HTTP/1.0 301 Moved Permanently\r\n", "<html>"
						"<head><title>Moved Permanently</title></head>"
						"<body><h1>301 Moved Permanently</h1></body>"
						"</html>" } }, //
				{ 302, { "HTTP/1.0 302 Moved Temporarily\r\n", "<html>"
						"<head><title>Moved Temporarily</title></head>"
						"<body><h1>302 Moved Temporarily</h1></body>"
						"</html>" } }, //
				{ 304, { "HTTP/1.0 304 Not Modified\r\n", "<html>"
						"<head><title>Not Modified</title></head>"
						"<body><h1>304 Not Modified</h1></body>"
						"</html>" } }, //
				{ 400, { "HTTP/1.0 400 Bad Request\r\n", "<html>"
						"<head><title>Bad Request</title></head>"
						"<body><h1>400 Bad Request</h1></body>"
						"</html>" } }, //
				{ 401, { "HTTP/1.0 401 Unauthorized\r\n", "<html>"
						"<head><title>Unauthorized</title></head>"
						"<body><h1>401 Unauthorized</h1></body>"
						"</html>" } }, //
				{ 403, { "HTTP/1.0 403 Forbidden\r\n", "<html>"
						"<head><title>Forbidden</title></head>"
						"<body><h1>403 Forbidden</h1></body>"
						"</html>" } }, //
				{ 404, { "HTTP/1.0 404 Not Found\r\n", "<html>"
						"<head><title>Not Found</title></head>"
						"<body><h1>404 Not Found</h1></body>"
						"</html>" } }, //
				{ 500, { "HTTP/1.0 500 Internal Server Error\r\n", "<html>"
						"<head><title>Internal Server Error</title></head>"
						"<body><h1>500 Internal Server Error</h1></body>"
						"</html>" } }, //
				{ 501, { "HTTP/1.0 501 Not Implemented\r\n", "<html>"
						"<head><title>Not Implemented</title></head>"
						"<body><h1>501 Not Implemented</h1></body>"
						"</html>" } }, //
				{ 502, { "HTTP/1.0 502 Bad Gateway\r\n", "<html>"
						"<head><title>Bad Gateway</title></head>"
						"<body><h1>502 Bad Gateway</h1></body>"
						"</html>" } },  //
				{ 503, { "HTTP/1.0 503 Service Unavailable\r\n", "<html>"
						"<head><title>Service Unavailable</title></head>"
						"<body><h1>503 Service Unavailable</h1></body>"
						"</html>" } }, //
		};

