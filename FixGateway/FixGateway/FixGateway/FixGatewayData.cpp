#include "FixGatewayData.h"

using namespace FixGateway;

FixGatewayData* FixGatewayData::s_instance = 0;

FixGatewayData::FixGatewayData() {
	init();
}

FixGatewayData::~FixGatewayData() {
	delete _userMgr;
}

void FixGatewayData::init() {
	_userMgr = new UserManager();
	_msgBus = new MsgBus();
	_msgBus->init();
}
