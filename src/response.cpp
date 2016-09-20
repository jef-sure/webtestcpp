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
		{ 200, "HTTP/1.0 200 OK\r\n" }, //
				{ 201, "HTTP/1.0 201 Created\r\n" }, //
				{ 202, "HTTP/1.0 202 Accepted\r\n" }, //
				{ 204, "HTTP/1.0 204 No Content\r\n" }, //
				{ 300, "HTTP/1.0 300 Multiple Choices\r\n" }, //
				{ 301, "HTTP/1.0 301 Moved Permanently\r\n" }, //
				{ 302, "HTTP/1.0 302 Moved Temporarily\r\n" }, //
				{ 304, "HTTP/1.0 304 Not Modified\r\n" }, //
				{ 400, "HTTP/1.0 400 Bad Request\r\n" }, //
				{ 401, "HTTP/1.0 401 Unauthorized\r\n" }, //
				{ 403, "HTTP/1.0 403 Forbidden\r\n" }, //
				{ 404, "HTTP/1.0 404 Not Found\r\n" }, //
				{ 500, "HTTP/1.0 500 Internal Server Error\r\n" }, //
				{ 501, "HTTP/1.0 501 Not Implemented\r\n" }, //
				{ 502, "HTTP/1.0 502 Bad Gateway\r\n" },  //
				{ 503, "HTTP/1.0 503 Service Unavailable\r\n" }, //
		};

