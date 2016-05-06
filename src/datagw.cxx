#include "datagw/datagw.h"
#include "datagw/memdb.h"
#include "zprotobuf/zprotobuf++.h"

static void DataGatewayActorRun(zsock_t* pipe,void* args);

DataGateway::DataGateway()
{
}


DataGateway::~DataGateway() {
}

zsock_t* DataGateway::create_socket(const std::string& address) {
	zsock_t* sock = zsock_new(ZMQ_REP);
	if( -1 == zsock_bind(sock,"%s",address.c_str()) ) {
		zsock_destroy(&sock);
		return nullptr;
	} else {
		return sock;
	}
}

void DataGateway::handle_error(const std::shared_ptr<google::protobuf::Message>& msg) {
	zstr_send(m_sock,"#err");
}

int DataGateway::run(const std::string& address,const std::string& connect_string) {
	int result;
	MemoryDB db;

	result = db.init(connect_string);
	assert( result != -1 );

	m_sock = create_socket(address);
	assert( m_sock != nullptr );
	
	while( 1 ) {
		std::shared_ptr<google::protobuf::Message> msg = zpb_recv(m_sock,true);
		if( msg == nullptr ) {
			if( zsys_interrupted ) {
				break;
			}
			handle_error(nullptr);
			continue;
		}
		m_deliver->deliver(msg);
	}

	return 0;
}

