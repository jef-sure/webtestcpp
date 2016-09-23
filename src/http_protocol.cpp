/*
 * http_protocol.cpp
 *
 *  Created on: 20.09.2016
 *      Author: apetrusevich
 */

#include "http_protocol.h"
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <memory>
#include <string>
#include "response.h"

HttpProtocol::HttpProtocol(std::shared_ptr<boost::asio::ip::tcp::socket> socket) :
		Protocol(socket), state(WAIT_FOR_REQUEST) {
}

HttpProtocol::~HttpProtocol() {
}

void HttpProtocol::handler() {
	auto self(shared_from_this());
	if (state == WAIT_FOR_REQUEST) {
		socket->async_read_some(boost::asio::buffer(read_buffer),
				[this,self](boost::system::error_code ec, std::size_t bytes_transferred) -> void {
					if (!ec) {
						Request::State s = request.parse(std::string(read_buffer.data(), bytes_transferred));
						if(s == Request::COMPLETED) {
							onRequest();
						} else {
							handler();
						}
					}
				});
	}
}

void HttpProtocol::onRequest() {
	auto self(shared_from_this());
	Response resp(200);
	string body = "<html><head><title>test</title>"
			"</head><body><h1>Test</h1><p>This is a test!</p></body></html>";
	string cl = boost::lexical_cast<std::string>(body.size());
	resp.addHeader("Content-Length", cl);
	resp.addHeader("Content-Type", "text/html");
	resp.addBody("");
	response_buffer = resp.toString();
	async_write(*socket,
			boost::asio::buffer(response_buffer.data(), response_buffer.size()),
			[this,self](boost::system::error_code ec, std::size_t bytes_transferred) -> void {
			});
}
