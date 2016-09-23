/*
 * response.h
 *
 *  Created on: Sep 20, 2016
 *      Author: anton
 */

#ifndef SRC_RESPONSE_H_
#define SRC_RESPONSE_H_

#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Response {

public:
	typedef vector<pair<string, string> > headersVector;
	Response() {
		code = 200;
	}
	Response(int code) :
			Response() {
		this->code = code;
	}
	virtual ~Response() {
	}
	virtual string toString();
	void addHeader(pair<string, string> &p) {
		headers.push_back(p);
	}
	void addBody(const string &body) {
		this->body += body;
	}
	void addHeader(const string &h, const string &v) {
		headers.emplace_back(h, v);
	}
private:
	int code;
	headersVector headers;
	string body;
};

#endif /* SRC_RESPONSE_H_ */
