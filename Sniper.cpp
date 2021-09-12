#include "Sniper.h"

#define MAX_MOVE 4
#define AMMO_LOAD 2
#define ATTACK_COST 1
#define CRITICAL_HIT_MULTIPLIER 2

#define ATTACK_DISTANCE_MULTIPLIER 0.5
#define ADD_TO_ROUND_UP 0.5



namespace mtm
{
    Sniper::Sniper(Team team, int health_t, int ammo_t, int range_t, int power_t) :
                    Character(team, SNIPER, AMMO_LOAD, health_t, ammo_t, range_t,
                    power_t, MAX_MOVE, ATTACK_COST), attack_count(1){}


    Sniper::Sniper(const Sniper& sniper) : Sniper(sniper.team(), sniper.health(),
                    sniper.ammo(), sniper.range(), sniper.power()){}

    Character* Sniper::clone() const
    {
        return new Sniper(*this);
    }

    bool Sniper::legalAttack(const GridPoint location, const GridPoint target, std::shared_ptr<Character> target_char)
    {
        if(target_char==nullptr){
            CellEmpty e;
            throw e;
        }

        if(target_char->team() == team()){
            IllegalTarget e;
            throw e;
        }

        int distance = GridPoint::distance(location, target);
        if(distance > range() || distance < ceil((range()*ATTACK_DISTANCE_MULTIPLIER)+ADD_TO_ROUND_UP)){
            OutOfRange error;
            throw error;
        }
        return true;
    }

    int Sniper::attackCharacter(GridPoint start, GridPoint end, Team target_team)
    {
        if(attack_count%3 != 0){
            attack_count++;
            char_ammo -= ATTACK_COST;
            return (-power());
        }
        attack_count++;
        char_ammo -= ATTACK_COST;
        return (-CRITICAL_HIT_MULTIPLIER*power());
    }
}
