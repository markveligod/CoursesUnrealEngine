// ShootTheMap


#include "STMGameInstance.h"

FName USTMGameInstance::GetStartUpLevelName() const
{
    return (this->StartUpLevelName);
}

FName USTMGameInstance::GetMenuLevelName() const
{
    return (this->MenuLevelName);
}
