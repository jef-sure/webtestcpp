//============================================================================
// Name        : tb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "request.h"

void dump_map(const stringMap & map) {
	for (auto it = map.begin(); it != map.end(); it++) {
		cout << it->first << ": " << it->second << endl;
	}
}

void test_buffer(const string &buffer) {
	Request req;
	req.parse(buffer);
	cout << "method: " << req.method << ", path: " << req.path
			<< ", http version: " << req.http_version << endl;
	cout << "headers: " << endl;
	dump_map(req.headers);
	cout << "query: " << endl;
	dump_map(req.query_params);
	cout << "body: " << endl;
	dump_map(req.body_params);
}

int main() {
	test_buffer(
			"GET /recv.php?u=20bb9c026e&l=http%3A%2F%2Fredis.io%2Ftopics%2Fdata-types-intro%23strings&r=http%3A%2F%2Fredis.io%2F&w=1600&h=900&a=Mozilla%2F5.0%20(Windows%20NT%206.1%3B%20WOW64%3B%20rv%3A48.0)%20Gecko%2F20100101%20Firefox%2F48.0&c=y&hl=2&nv=0&rv=1 HTTP/1.1\r\n"
					"Host: demo.lloogg.com\r\n"
					"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0\r\n"
					"Accept: */*\r\n"
					"Accept-Language: de,en-US;q=0.7,en;q=0.3\r\n"
					"Accept-Encoding: gzip, deflate\r\n"
					"Referer: http://redis.io/topics/data-types-intro\r\n"
					"Connection: keep-alive\r\n\r\n");
	test_buffer(
			"POST /pass.php HTTP/1.1\r\n"
					"Host: 127.0.0.1\r\n"
					"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:18.0) Gecko/20100101 Firefox/18.0\r\n"
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
					"Accept-Language: en-US,en;q=0.5\r\n"
					"Accept-Encoding: gzip, deflate\r\n"
					"DNT: 1\r\n"
					"Referer: http://127.0.0.1/pass.php\r\n"
					"Cookie: passx=87e8af376bc9d9bfec2c7c0193e6af70; PHPSESSID=l9hk7mfh0ppqecg8gialak6gt5\r\n"
					"Connection: keep-alive\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n"
					"Content-Length: 29\r\n\r\n"
					"username=zurfyx&pass=password");
	return 0;
}
