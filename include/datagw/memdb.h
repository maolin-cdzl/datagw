#pragma once

#include <string>


class MemoryDB {
public:
	MemoryDB();
	~MemoryDB();

	int init(const std::string& connect_string);
};

