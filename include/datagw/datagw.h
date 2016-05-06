#pragma once

#include <stdint.h>
#include <string>
#include <memory>
#include <czmq.h>

class DataGateway {
public:
	DataGateway();
	~DataGateway();

	int run(const std::string& address,const std::string& connect_string);

private:
	zsock_t* create_socket(const std::string& address);

	void handle_error(const std::shared_ptr<google::protobuf::Message>& msg);

	// process functions
private:
	int proce_get_account(const google::protobuf::Message& msg);
private:
	zsock_t*			m_sock;
};

