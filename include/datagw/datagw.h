#pragma once

#include <stdint.h>
#include <string>
#include <czmq.h>

class DataGateway {
public:
	DataGateway();
	~DataGateway();

	int run(const std::string& address,const std::string& connect_string);

private:
	std::string		m_address;
	std::string		m_connect_string;
};

