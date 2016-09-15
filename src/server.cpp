/*
 * server.cpp
 *
 *  Created on: Sep 15, 2016
 *      Author: anton
 */

#include "server.h"
#include <boost/bind.hpp>

static boost::asio::io_service io_service;
static boost::asio::ip::tcp::acceptor acceptor { io_service };

boost::asio::io_service & getIoService() {
	return io_service;
}

Server::Server(const boost::asio::ip::tcp::endpoint &endpoint) {
	acceptor.open(endpoint.protocol());
	acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen(boost::asio::socket_base::max_connections);
}

static void acceptor_handler(const boost::system::error_code & ec,
		Server::handler handler,
		std::shared_ptr<boost::asio::ip::tcp::socket> accepted_socket) {
	if (!ec) {
		auto new_socket = std::shared_ptr::make_shared<boost::asio::ip::tcp::socket>();
		acceptor.async_accept(*new_socket,
				boost::bind(acceptor_handler, _1, handler, new_socket));
		try {
			handler(accepted_socket);
		} catch (...) {

		}
	}
}

void Server::acceptorRunner(Server::handler handler) {
	auto socket = std::shared_ptr::make_shared<boost::asio::ip::tcp::socket>();
	acceptor.async_accept(*socket,
			boost::bind(acceptor_handler, _1, handler, socket));

}

