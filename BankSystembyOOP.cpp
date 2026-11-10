
#include <iostream>
#include "clsLoginScreen.h"
#include "clsManageUsersMenue.h"
using namespace std;
int main()
{
    while (true)
    {
        clsManageUsersMenue::ShowManageUserMenue();

        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

    }
    return 0;
}


