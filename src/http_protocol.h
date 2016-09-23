/*
 * http_protocol.h
 *
 *  Created on: 20.09.2016
 *      Author: apetrusevich
 */

#ifndef SRC_HTTP_PROTOCOL_H_
#define SRC_HTTP_PROTOCOL_H_

#include "request.h"
#include "protocol.h"

class HttpProtocol: public Protocol {
	Request request;
	enum State {
		WAIT_FOR_REQUEST, HAVE_RESPONSE, EXPIRED
	} state;
public:
	HttpProtocol(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
	virtual ~HttpProtocol();
protected:
	void handler() override;
	virtual void onRequest();
	array<char, 4096> read_buffer;
	string response_buffer;
};

#endif /* SRC_HTTP_PROTOCOL_H_ */
