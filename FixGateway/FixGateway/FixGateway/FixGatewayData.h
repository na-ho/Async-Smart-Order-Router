#pragma once

#include "UserManager.h"
#include "MsgBus.h"

namespace FixGateway
{
    class FixGatewayData
    {
    public:
        UserManager* getUserMgr() {
            return _userMgr;
        }

        static FixGatewayData* instance()
        {
            if (!s_instance)
                s_instance = new FixGatewayData;
            return s_instance;
        }

    private:
        FixGatewayData();
        ~FixGatewayData();

        void init();

    private:
        static FixGatewayData* s_instance;

        UserManager* _userMgr;
        MsgBus* _msgBus;
    };
}