#include "Player.h"

std::string Player::GetWeapon()
{
    return _weapon;
}

std::string Player::GetArmor()
{
    return _armor;
}

std::string Player::GetAccessory()
{
    return _accessory;
}

void Player::SetWeapon(std::string weapon)
{
    _weapon = weapon;
}

void Player::SetArmor(std::string armor)
{
    _armor = armor;
}

void Player::SetAccessory(std::string accessory)
{
    _accessory = accessory;
}

