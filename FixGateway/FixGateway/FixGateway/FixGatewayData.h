#pragma

#include "UserManager.h"

class FixGatewayData
{
    UserManager *_userMgr;
    static FixGatewayData* s_instance;
    FixGatewayData(){
        init();
    }

    ~FixGatewayData() {
        delete _userMgr;
    }

    void init() {
        _userMgr = new UserManager();
    }
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
};