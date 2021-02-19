#pragma once

#include "User.h"

namespace FixGateway
{
    class UserFactory
    {
    public:
        static void warmUp() {
            if (!s_instance)
                s_instance = new UserFactory;
        }

        static UserFactory* instance()
        {
            return s_instance;
        }

        User* newUser();

    private:

        static class UserFactory* s_instance;
    };
}