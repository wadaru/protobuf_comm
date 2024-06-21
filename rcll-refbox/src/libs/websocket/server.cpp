/***************************************************************************
 *  server.cpp - class to provide server functionality to handle incoming connections
 *
 *  Created: Mon Mar 30 22:59:00 2020
 *  Copyright  2020       Daniel Swoboda  [swoboda@kbsg.rwth-aachen.de]
 ****************************************************************************/

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  Read the full text in the LICENSE.GPL file in the doc directory.
 */

#include "server.h"

#include "client.h"
#include "data.h"

#include <sys/socket.h>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

namespace llsfrb::websocket {

/**
 * @brief Construct a new Server::Server object
 * 
 *  Constructs a new Server object and assigns the used backend data pointer.
 * 
 * @param data_ptr pointer to Data object that is used for this session
 * @param logger_ logger used by the backend
 */
Server::Server(std::shared_ptr<Data> data, std::shared_ptr<Logger> logger)
: data_(data), logger_(logger)
{
}

Server::Server()
{
}

/**
 * @brief Runs the Socket/Websocket Server
 *  This operator runs the socket or websocket server (currently based on WS_MODE predef).
 *  It launches an endless accepting loop, that accepts new connections and creates the 
 *  necessary objects required by the backend to work with them. 
 * 
 */
void
Server::operator()()
{
	// listen for new connection
	boost::asio::io_service io_service;
	tcp::acceptor           acceptor_(io_service, tcp::endpoint(tcp::v4(), port_));

	// acceptor loop
	while (true) {
		std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_service);
		acceptor_.accept(*socket);

		//client can send control command if allow_control_all_ is set or it is the localhost
		bool client_can_send =
		  (allow_control_all_ || (*socket).remote_endpoint().address().to_string() == "127.0.0.1");

		if (ws_mode_) {
			// websocket approach
			std::shared_ptr<boost::beast::websocket::stream<tcp::socket>> web_socket =
			  std::make_shared<boost::beast::websocket::stream<tcp::socket>>(std::move(*socket));
			std::shared_ptr<Client> client =
			  std::make_shared<ClientWS>(web_socket, logger_, data_, client_can_send);
			data_->clients_add(client);
		} else {
			// socket approach
			std::shared_ptr<Client> client =
			  std::make_shared<ClientS>(socket, logger_, data_, client_can_send);
			data_->clients_add(client);
		}

		logger_->log_info("Websocket", "new client connected");
	}
}

/**
 * @brief Configure the servers port and mode prior to start. 
 * 
 * @param port port on which the server runs on
 * @param ws_mode true if websocket only mode
 * @param allow_control_all if true, devices with not local host ip addresses can send control commands
 */
void
Server::configure(uint port, bool ws_mode = true, bool allow_control_all = false)
{
	port_              = port;
	ws_mode_           = ws_mode;
	allow_control_all_ = allow_control_all;
}

} // namespace llsfrb::websocket
