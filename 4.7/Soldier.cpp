#include "Soldier.h"
#include <memory>
#include <cmath>

#define MAX_MOVE 3
#define AMMO_LOAD 3
#define ATTACK_COST 1

#define ADJACENT_ATTACK_PENALTY_RANGE 3
#define ADJACENT_ATTACK_PENALTY_POWER 2
#define ADD_TO_ROUND_UP 0.5

namespace mtm
{
    Soldier::Soldier(Team team, int health_t, int ammo_t, int range_t, int power_t) :
                    Character(team, SOLDIER, AMMO_LOAD, health_t, ammo_t, range_t,
                    power_t, MAX_MOVE, ATTACK_COST){}

    Soldier::Soldier(const Soldier& soldier) : Character(soldier.team(), SOLDIER, AMMO_LOAD,
                    soldier.health(), soldier.ammo(), soldier.range(), soldier.power(),
                    MAX_MOVE, ATTACK_COST){}

    Character* Soldier::clone() const
    {
        return new Soldier(*this);
    }

    bool Soldier::legalAttack(GridPoint start, GridPoint end, std::shared_ptr<Character> target_char)
    {
        if((start.row!=end.row) && (start.col!=end.col)){
            OutOfRange e;
            throw e;
        }
        if(GridPoint::distance(start,end) > range()){
            OutOfRange e;
            throw e;
        }
        return true;
    }

    int Soldier::adjacentDamage(int distance)
    {
        if(distance==0){
            return 0;
        }
        if(distance<=(int)(ceil((double)range()/ADJACENT_ATTACK_PENALTY_RANGE) + ADD_TO_ROUND_UP)){
            return -(int)(ceil((double)power()/ADJACENT_ATTACK_PENALTY_POWER) + ADD_TO_ROUND_UP);
        }
        return 0;
    }

    void Soldier::removeOneAmmo()
    {
        char_ammo--;
    }
}
