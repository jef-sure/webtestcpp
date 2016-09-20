/*
 * connection.cpp
 *
 *  Created on: 15.09.2016
 *      Author: apetrusevich
 */

#include "protocol.h"

Protocol::Protocol(std::shared_ptr<boost::asio::ip::tcp::socket> _socket) :
		socket(_socket) {
	handler();
}
