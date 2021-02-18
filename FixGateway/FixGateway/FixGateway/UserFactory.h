#pragma once

#include "User.h"

namespace FixGateway
{
    class UserFactory
    {
    public:

        static UserFactory* instance()
        {
            if (!s_instance)
                s_instance = new class UserFactory;
            return s_instance;
        }

        User* newUser();

    private:

        static class UserFactory* s_instance;
    };
}