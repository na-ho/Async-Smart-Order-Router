#include "FixGatewayData.h"

using namespace FixGateway;

FixGatewayData* FixGatewayData::s_instance = 0;

FixGatewayData::FixGatewayData() 
:_userMgr(NULL)
, _msgBus(NULL)
{
}

FixGatewayData::~FixGatewayData() {
	if (_msgBus != NULL) {
		delete _userMgr;
	}
	
	if (_msgBus != NULL) {
		delete _msgBus;
	}
}

void FixGatewayData::init() {
	_userMgr = new UserManager();
	_msgBus = new MsgBus();
	_msgBus->init(_server_id);
}
