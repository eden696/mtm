#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"
#include "Exceptions.h"
#include <memory>

/**
* ________________________________Medic________________________________
*
* the medic is a type of character (inherits all og the character arguments)
    the medic can heal characters from the same team as him.
 *
* The following functions are available:
 * public:
 *      explicit Medic(@argumnts) - constructor.
        Medic(const Sniper &Sniper) - copy constructor.
        ~Medic() - destructor.
        clone() -  makes a copy of the character.
        legalAttack - checks if an attack is legal.
        attackCharacter - returns the power of the attack.
*
*/



namespace mtm
{
    class Medic : public Character
    {
    public:
        /**
         * Medic- given the character stats the function will insert the info into the character
         *      @param - ♦health
         *               ♦ range (of attack)
         *               ♦power
         *               ♦ammo_load
                         ♦the "Team" the character belongs to.
                         ✩ the rest of the info is the same for all the characters
                            from the same type -> wil be implemented in the cpp.
                @return - a Medic.
         */
        explicit Medic(Team team, int health_t, int ammo_t, int range_t, int power_t);

        /**
        * Medic - copy constructor.
        *      @param - Medic - the Sniper we want to copy.
               @return - a new Medic.
        */
        Medic(const Medic& medic);

        /**
        * ~Medic - destructor.
        */
        ~Medic() = default;

        /**
        * clone() - implementation of the virtual function that makes a copy of the Medic.
               @return - a pointer to the new Medic.
        */
        virtual Character* clone() const override;

        /**
        legalAttack - checks if an attack is legal.
        @param      - location - the location of the character.
                    - target - the location of the desired target.
                    - target_character - a character at the target location.
        @return     - throws OutOfRange if the target is out of the attack range.
                    - false if the attack can't be executed for another reason.
                    - true otherwise.

        */
        virtual bool legalAttack(GridPoint location, GridPoint target, std::shared_ptr<Character> target_char) override;

        /**
        attack      - returns the power of the attack.
        @param      - start - the location of the character.
                    - end - the location of the desired target.
                    - target_team - the team of the target.
        @return     - the power of the attack.
        */
        virtual int attackCharacter(GridPoint start, GridPoint end, Team target_team) override;
    };
}

#endif //MEDIC_H
