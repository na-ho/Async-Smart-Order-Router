#pragma once

#include "UserManager.h"
#include "MsgBus.h"

namespace FixGateway
{
    class FixGatewayData
    {
    public:
        static void warmUp() {
            if (!s_instance)
                s_instance = new FixGatewayData;
        }

        static FixGatewayData* instance()
        {
            return s_instance;
        }

        void init();

        UserManager* getUserMgr() {
            return _userMgr;
        }

        MsgBus* getMsgBus() {
            return _msgBus;
        }

        void setServer_id(const std::string &server_id) {
            _server_id = server_id;
        }

        std::string getServer_id() {
            return _server_id;
        }

    private:
        FixGatewayData();
        ~FixGatewayData();


    private:
        static FixGatewayData* s_instance;

        UserManager* _userMgr;
        MsgBus* _msgBus;
        std::string _server_id;
    };
}