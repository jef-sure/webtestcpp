/*
 * http_protocol.cpp
 *
 *  Created on: 20.09.2016
 *      Author: apetrusevich
 */

#include "http_protocol.h"
#include <boost/asio/buffer.hpp>
#include <memory>
#include <string>

HttpProtocol::HttpProtocol(std::shared_ptr<boost::asio::ip::tcp::socket> socket) :
		Protocol(socket), state(WAIT_FOR_REQUEST) {
}

HttpProtocol::~HttpProtocol() {
}

void HttpProtocol::handler() {
	auto self(shared_from_this());
	if (state == WAIT_FOR_REQUEST) {
		std::array<char, 4096> buffer;
		socket->async_read_some(boost::asio::buffer(buffer),
				[this](boost::system::error_code ec, std::size_t bytes_transferred) {
					if (!ec) {
						Request::State s = request.parse(std::string(buffer.data(), bytes_transferred));
						if(s == Request::COMPLETED) {
							onRequest();
						} else {
							handler();
						}
					}
				});
	}
}
