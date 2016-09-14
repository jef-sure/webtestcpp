/*
 * request.cpp
 *
 *  Created on: 14.09.2016
 *      Author: Anton Petrusevich
 */

#include "request.h"
#include <ctype.h>
#include <map>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;
using namespace boost::algorithm;
using namespace boost;

void Request::parseMethod(size_t eolp) {
	string method_line(internal_buffer, 0, eolp);
	internal_buffer.erase(0, eolp + 2);
	auto sp = method_line.find(' ');
	if (sp == string::npos || sp == 0) {
		current_state = BROKEN;
		return;
	}
	method = string(method_line, 0, sp);
	auto su = method_line.find(' ', sp + 1);
	if (su == string::npos || su == sp + 1) {
		current_state = BROKEN;
		return;
	}
	url = string(method_line, sp + 1, su - sp - 1);
	http_version = method_line.substr(su + 1);
	replace_first(http_version, "HTTP/", "");
	auto qp = url.find('?');
	if (qp != string::npos) {
		path = URIunescape(url.substr(0, qp));
		query_string = url.substr(qp + 1);
	} else {
		path = URIunescape(url);
	}
	if (!query_string.empty())
		query_params = parseUrlEncoded(query_string);
	current_state = WAIT_FOR_HEADERS;
}

void Request::parseHeaders(size_t eolp) {
	string headers_buffer(internal_buffer, 0, eolp);
	internal_buffer.erase(0, eolp + 4);
	string key;
	size_t lb = 0;
	auto sp = headers_buffer.find("\r\n");
	if (sp == string::npos)
		sp = headers_buffer.size();
	while (sp != lb) {
		string hline;
		if (isspace(headers_buffer[lb])) {
			if (key.empty()) {
				current_state = BROKEN;
				return;
			}
			while (lb < sp && isspace(headers_buffer[lb]))
				++lb;
			if (lb != sp)
				headers[key].append(string(headers_buffer, lb, sp - lb));
		} else {
			while (lb < sp && isspace(headers_buffer[lb]))
				++lb;
			if (lb != sp) {
				string hline(headers_buffer, lb, sp - lb);
				auto cs = hline.find(':');
				if (cs == string::npos) {
					current_state = BROKEN;
					return;
				}
				key = string(hline, 0, cs);
				++cs;
				while (cs < hline.size() && isspace(hline[cs]))
					++cs;
				headers[key] = hline.substr(cs);
			}
		}
		if (sp == headers_buffer.size())
			break;
		lb = sp + 2;
		sp = headers_buffer.find("\r\n", lb);
		if (sp == string::npos)
			sp = headers_buffer.size();
	}
	current_state = WAIT_FOR_BODY;
}

static uint8_t hex2val(char c) {
	c &= ~32;
	if (c < 32)
		return c - 16;
	return c - 55;
}

static char hex2char(char h1, char h0) {
	return (hex2val(h1) << 4) | hex2val(h0);
}

static bool is_hex(char c) {
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')
			|| (c >= 'a' && c <= 'f');
}

static size_t find_escaped(const string &str, size_t spos) {
	while (spos + 3 <= str.size()) {
		auto prc = str.find('%', spos);
		if (prc == string::npos || prc + 3 >= str.size())
			return string::npos;
		if (is_hex(str[prc + 1]) && is_hex(str[prc + 2]))
			return prc;
		spos = prc + 1;
	}
	return string::npos;
}

string Request::URIunescape(const string &str) {
	string ret;
	size_t cp = 0;
	while (cp < str.size()) {
		auto ep = find_escaped(str, cp);
		if (ep == string::npos) {
			ret.append(str.substr(cp));
			break;
		}
		ret.append(str.substr(cp, ep - cp));
		ret += hex2char(str[ep + 1], str[ep + 2]);
		cp = ep + 3;
	}
	return ret;
}

string Request::URIdecode(const string &str) {
	string ret(str);
	for (char &c : ret) {
		if (c == '+')
			c = ' ';
	};
	return URIunescape(ret);
}

stringMap Request::parseUrlEncoded(const string &encoded) {
	stringMap ret;
	vector<string> params_vec;
	split(params_vec, encoded, is_any_of("&;"), token_compress_on);
	for (auto i : params_vec) {
		string param;
		string value;
		auto se = i.find('=');
		if (se == string::npos) {
			param = i;
			value = "1";
		} else {
			param = i.substr(0, se);
			value = i.substr(se + 1);
		}
		ret[URIdecode(param)] = URIdecode(value);
	}
	return ret;
}

void Request::parseBody() {
	auto cli = headers.find("Content-Length");
	auto cti = headers.find("Content-Type");
	if (cli == headers.end()) {
		current_state = COMPLETED;
		return;
	}
	long l = strtol(cli->second.c_str(), NULL, 10);
	if (l < 0 || cti == headers.end()
			|| cti->second != "application/x-www-form-urlencoded") {
		current_state = BROKEN;
		return;
	}
	if (l == 0) {
		current_state = COMPLETED;
		return;
	}
	if (internal_buffer.size() < (size_t) l)
		return;
	body_params = parseUrlEncoded(internal_buffer);
	internal_buffer.clear();
	current_state = COMPLETED;
}

Request::State Request::parse(const string &buffer) {
	internal_buffer.append(buffer);
	if (current_state == WAIT_FOR_METHOD) {
		size_t eolp = internal_buffer.find("\r\n");
		if (eolp != string::npos) {
			parseMethod(eolp);
		}
	}
	if (current_state == WAIT_FOR_HEADERS) {
		size_t eolp = internal_buffer.find("\r\n\r\n");
		if (eolp != string::npos) {
			parseHeaders(eolp);
		}
	}

	if (current_state == WAIT_FOR_BODY) {
		parseBody();
	}
	return current_state;
}

