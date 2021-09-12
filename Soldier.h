#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"
#include "Exceptions.h"

/**
* ________________________________Soldier________________________________
*
* the Soldier is a type of character (inherits all og the character arguments)
* the Soldier have a passive buff all enemy targets that are in a distance of a third
 * of the Soldier range suffers from collateral damage
*
* The following functions are available:
 * public:
 *      explicit Sniper(@argumnts) - constructor.
        Sniper(const Sniper &Sniper) - copy constructor.
        ~Sniper() - destructor.
        clone() -  makes a copy of the character.
        legalAttack - checks if an attack is legal.
        attack - returns the power of the attack.
        attackCharacter - returns the power of the attack.
*
*/


namespace mtm
{
    class Soldier : public Character
    {
    public:

        /**
         * Soldier- given the character stats the function will insert the info into the character.
         *      @param - ♦health
         *               ♦ range (of attack)
         *               ♦power
         *               ♦ammo_load
                         ♦the "Team" the character belongs to.
                         ✩ the rest of the info is the same for all the characters
                            from the same type -> wil be implemented in the cpp.
                @return - a Soldier
         */
        explicit Soldier(Team team, int health_t, int ammo_t, int range_t, int power_t);

        /**
        * Soldier - copy constructor.
        *      @param - soldier - the soldier we want to copy.
               @return - a new Soldier.
        */
        Soldier(const Soldier& soldier);

        /**
        * ~Soldier - destructor.
        */
        ~Soldier() = default;

        /**
         * clone() - implementation of the virtual function that makes a copy of the Soldier.
                @return - a pointer to the new Soldier.
         */
        virtual Character* clone() const override;

        /**
        * removeOneAmmo -  subtract 1 ammo unit.
        */
        virtual void removeOneAmmo() override;

        /**
        legalAttack - checks if an attack is legal.
        @param      - location - the location of the character.
                    - target - the location of the desired target.
        @return     -true if the attack can be executed, false otherwise.
        */
        virtual bool legalAttack(const GridPoint location, const GridPoint target, std::shared_ptr<Character> target_char) override;

        /**
        adjacentDamage - returns the power of the attack to adjacent cells.
        @param      - distance - the distance between the original attack and a cell around it.
        @return     - the power of the attack to adjacent cells.
         */
        virtual int adjacentDamage(int distance) override;
    };
}

#endif //SOLDIER_H
