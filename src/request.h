/*
 * request.h
 *
 *  Created on: 14.09.2016
 *      Author: Anton Petrusevich
 *      simple test project
 *
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <map>

using namespace std;

typedef map<string, string> stringMap;

class Request {
public:
	string method;
	string url;
	string path;
	string query_string;
	string http_version;
	stringMap headers;
	stringMap body_params;
	stringMap query_params;
	enum State {
		WAIT_FOR_METHOD, WAIT_FOR_HEADERS, WAIT_FOR_BODY, COMPLETED, BROKEN
	};
	Request() :
			current_state(WAIT_FOR_METHOD) {
	}
	Request(const string &buf) :
			Request() {
		parse(buf);
	}
	State parse(const string & buf);
	static string URIunescape(const string &str);
	static string URIdecode(const string &str);
private:
	void parseMethod(size_t eolp);
	void parseHeaders(size_t eolp);
	void parseBody();
	static stringMap parseUrlEncoded(const string &encoded);
	State current_state;
	string internal_buffer;
};

#endif /* REQUEST_H_ */
