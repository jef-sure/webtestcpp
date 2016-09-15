/*
 * server.h
 *
 *  Created on: Sep 15, 2016
 *      Author: anton
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <memory>

class Server {

public:
	typedef std::function<void(boost::shared_ptr<boost::asio::ip::tcp::socket>)> handler;
	Server(const boost::asio::ip::tcp::endpoint &endpoint);
	Server() = delete;
	Server(const Server&) = delete;
	Server(Server&) = delete;
	Server& operator =(const Server&) = delete;
	Server& operator =(Server&) = delete;
	static boost::asio::io_service & getIoService();
	static void acceptorRunner(handler);
};

#endif /* SRC_SERVER_H_ */
