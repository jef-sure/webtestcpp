/*
 * server.cpp
 *
 *  Created on: Sep 15, 2016
 *      Author: anton
 */

#include "server.h"

using namespace boost::asio;
using namespace std::placeholders;

static io_service io_service;
static ip::tcp::acceptor acceptor { io_service };

boost::asio::io_service & getIoService() {
	return io_service;
}

Server::Server(const ip::tcp::endpoint &endpoint) {
	acceptor.open(endpoint.protocol());
	acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen(socket_base::max_connections);
}

static void acceptor_handler(const boost::system::error_code & ec,
		Server::handler handler,
		std::shared_ptr<ip::tcp::socket> accepted_socket) {
	if (!ec) {
		auto new_socket = std::make_shared<ip::tcp::socket>(&io_service);
		acceptor.async_accept(*new_socket,
				std::bind(acceptor_handler, _1, handler, new_socket));
		try {
			handler(accepted_socket);
		} catch (...) {

		}
	}
}

void Server::acceptorStart(Server::handler handler) {
	auto socket = boost::make_shared<boost::asio::ip::tcp::socket>(
			boost::ref(io_service));
	acceptor.async_accept(*socket,
			std::bind(acceptor_handler, _1, handler, socket));

}

