#include "Character.h"

namespace mtm
{
    Character::Character(Team team_t, CharacterType type_t, units_t ammo_load_t,
                         units_t health_t, units_t ammo_t, units_t range_t,
                         units_t power_t, units_t max_move_t, units_t attack_cost_t) :
                         char_health(health_t), char_range(range_t), char_power(power_t),
                         char_max_move(max_move_t), char_ammo_load(ammo_load_t),
                         char_attack_cost(attack_cost_t), char_team(team_t),
                         char_type(type_t), char_ammo(ammo_t){}

    Character::Character(const Character& character) : char_health(character.char_health),
                        char_range(character.char_range), char_power(character.char_power),
                        char_max_move(character.char_max_move), char_ammo_load(character.char_ammo_load),
                        char_attack_cost(character.char_attack_cost), char_team(character.char_team),
                        char_type(character.char_type), char_ammo(character.char_ammo){}

     int Character::health() const
    {
        return char_health;
    }

     int Character::ammo() const
    {
        return char_ammo;
    }

    int Character::range() const
    {
        return char_range;
    }

    int Character::power() const
    {
        return char_power;
    }

    Team Character::team() const
    {
        return char_team;
    }

    CharacterType Character::type() const
    {
        return char_type;
    }

    int Character::maxMove() const
    {
        return char_max_move;
    }

    int Character::ammoLoad() const
    {
        return char_ammo_load;
    }

    int Character::attackCost() const
    {
        return char_attack_cost;
    }

    void Character::health(int n)
    {
        char_health += n;
    }

    void Character::load()
    {
        char_ammo += char_ammo_load;
    }

    bool Character::canMove(const GridPoint location, const GridPoint target)
    {
        return (GridPoint::distance(location, target) <= range());
    }

    int Character::attackCharacter(GridPoint start, GridPoint end, Team target_team)
    {
        char_ammo--;
        return (-char_power);
    }
}
