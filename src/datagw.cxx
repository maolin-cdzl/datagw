#include <memory>
#include "datagw/datagw.h"
#include "datagw/memdb.h"
#include "zprotobuf/zprotobuf++.h"

static void DataGatewayActorRun(zsock_t* pipe,void* args);

DataGateway::DataGateway()
{
}


DataGateway::~DataGateway() {
}

int DataGateway::run(const std::string& address,const std::string& connect_string) {
	int result;
	MemoryDB db;

	result = db.init(connect_string);
	assert( result != -1 );

	zsock_t* sock = zsock_new(ZMQ_REP);
	result = zsock_bind(sock,"%s",address.c_str());
	assert( result != -1 );
	
	while( 1 ) {
		std::shared_ptr<google::protobuf::Message> msg = zpb_recv(sock,true);
		if( msg == nullptr ) {
			if( zsys_interrupted ) {
				break;
			}
			zstr_send(sock,"");
			continue;
		}
		m_deliver->deliver(msg);
	}

	return 0;
}

