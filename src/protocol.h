/*
 * connection.h
 *
 *  Created on: 15.09.2016
 *      Author: apetrusevich
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

#include <memory>
#include <boost/asio.hpp>

class Protocol: protected  std::enable_shared_from_this<Protocol> {
protected:
	std::shared_ptr<boost::asio::ip::tcp::socket> socket;
public:
	Protocol(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
	std::shared_ptr<Protocol> getShared() {
		return shared_from_this();
	}
	virtual ~Protocol() {};
protected:
	virtual void handler() = 0;
};

#endif /* SRC_PROTOCOL_H_ */
