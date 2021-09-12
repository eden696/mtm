#include "Medic.h"

#define MAX_MOVE 5
#define AMMO_LOAD 5
#define ATTACK_COST 1

namespace mtm
{

    Medic::Medic(Team team, int health_t, int ammo_t, int range_t, int power_t) :
                Character(team, MEDIC, AMMO_LOAD, health_t, ammo_t, range_t,
                power_t, MAX_MOVE, ATTACK_COST){}

    Medic::Medic(const Medic& medic) : Character(medic.team(), MEDIC, AMMO_LOAD,
                        medic.health(), medic.ammo(), medic.range(), medic.power(),
                        MAX_MOVE, ATTACK_COST){}

    Character* Medic::clone() const
    {
        return new Medic(*this);
    }

    bool Medic::legalAttack(GridPoint location, GridPoint target, std::shared_ptr<Character> target_char)
    {
        if(target_char == nullptr){
            CellEmpty e;
            throw e;
        }

        if(location == target){
            IllegalTarget e;
            throw e;
        }

        if(GridPoint::distance(location, target) > range()){
            OutOfRange error;
            throw error;
        }
        return true;
    }

    int Medic::attackCharacter(GridPoint start, GridPoint end, Team target_team)
    {
        if(target_team == team()){
            return power();
        }
        char_ammo -= ATTACK_COST;
        return (-power());
    }
}
