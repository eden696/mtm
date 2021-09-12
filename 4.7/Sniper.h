#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"
#include "Exceptions.h"
#include <cmath>
#include <memory>



/**
* ________________________________Sniper________________________________
*
* the sniper is a type of character (inherits all og the character arguments)
 * the sniper have a passive buff every 3 successful attack -> thus he have an int attack counter;
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
    class Sniper : public Character
    {
        int attack_count;

    public:
        /**
         * Sniper- given the character stats the function will insert the info into the character.
         *      @param - ♦health
         *               ♦range (of attack)
         *               ♦power
         *               ♦ammo_load
                         ♦the "Team" the character belongs to.
                         ✩ the rest of the info is the same for all the characters
                            from the same type -> wil be implemented in the cpp.
                @return - a Sniper
         */
        explicit Sniper(Team team, int health_t, int ammo_t, int range_t, int power_t);

        /**
          * Sniper - copy constructor.
          *      @param - Sniper - the Sniper we want to copy.
                 @return - a new Sniper.
          */
        Sniper(const Sniper &Sniper);

        /**
        * ~Sniper - destructor.
        */
        ~Sniper() = default;

        /**
         * clone() - implementation of the virtual function that makes a copy of the sniper.
                @return - a pointer to the new Sniper.
         */
        virtual Character *clone() const override;

        /**
        legalAttack - checks if an attack is legal.
        @param      - location - the location of the character.
                    - target - the location of the desired target.
                    - target_type - the character type of the target. (targets on the same team can npt be attacked.)
        @return     - true if the attack can be executed.
                    - throws OutOfRange if the target is out of the attack range.
                    - false if the attack can't be executed for another reason.
        */
        virtual bool legalAttack(const GridPoint location, const GridPoint target, std::shared_ptr<Character> target_char) override;

        /**
        attackCharacter - returns the power of the attack.
        @param      - start - the location of the character.
                    - end - the location of the desired target.
                    - target_team - the tame of the enemy.
        @return     -the power of the attack.
        */
        virtual int attackCharacter(GridPoint start, GridPoint end, Team target_team) override;
    };
}

#endif //SNIPER_H
