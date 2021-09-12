#ifndef CHARACTER_H
#define CHARACTER_H

#include "Auxiliaries.h"
#include <memory>
#include <cmath>

/**
* _____________________________GridPoint_____________________________
*
* Implements a duo of 2 integers.
* this struct will help us orientate inside of the board in the game.
*
* The following functions functions are available:
        GridPoint(int row, int col)  - constructor.
		GridPoint(const GridPoint& other) - copy constructor.
		~GridPoint() - destructor.
		GridPoint& operator=(const GridPoint& other) - implementation of operator=.
		bool operator==(const GridPoint& other) - implementation of operator==.
		static int distance(const GridPoint& point1, const GridPoint& point2) - helper
		        function that will tell us how many steps there are between 2 GridPoint
*/

namespace mtm
{
    enum Team { CPP, PYTHON };
	enum CharacterType { SOLDIER, MEDIC, SNIPER };
	typedef int units_t;



    struct GridPoint {
		int row, col;
    /**
     *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    *	GridPoint(int row, int col): crates a gridpoint.constructor.
    * @param row
    * @param col
    * @return
    *  a gridpoint
    */

		GridPoint(int row, int col) : row(row), col(col) {}

    /**
    *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
   *	GridPoint(const GridPoint& other): given a gridpoint it creates a copy of that gridpoint.
                    copy constructor.
   * @param const GridPoint& other - the gridpoint we want to copy
   * @return
   *  a gridpoint
   */

		GridPoint(const GridPoint& other)=default;

    /**
    *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    *~GridPoint(): destructor
    */
		~GridPoint()=default;

    /**
    *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
     *	GridPoint& operator=(const GridPoint& other): implementation of operator=.
     * @param const GridPoint& other - the gridpoint we want to copy and later insert to "this".
     * @return
     *  a reference to gridpoint.
     */
		GridPoint& operator=(const GridPoint& other)=default;

    /**
    *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
     *	GridPoint& operator==(const GridPoint& other): implementation of operator==.
     * @param const GridPoint& other - the gridpoint we want to comper to.
     * @return
     *  true - if both gridpoints are the same
     *  false- ig the gridpoints are not the same
     */
		bool operator==(const GridPoint& other) const {
			return this->row == other.row && this->col == other.col;
		}

    /**
    *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    *	distance: helper function that will tell us how many steps there are between 2 GridPoint.
    * @param point1, point2 - the coordinates we want to travel between.
    * @return
    *  int - the number of steps requierd to travel between the points.
    */
		static int distance(const GridPoint& point1, const GridPoint& point2) {
			return 	std::abs(point1.row - point2.row)
					+ std::abs(point1.col - point2.col);
		}
	};

    /**
* _____________________________Character_____________________________
*
* a struct that contain information about tha character in the game:
   the character stats:
     ♦health
     ♦range (of attack)
     ♦power
     ♦max_move
     ♦ammo_load
     ♦attack_cost
     ♦the "Team" the character belongs to.
     ♦CharacterType (from the verity given to us : solider/medic/sniper)
*
* The following functions are available:

     * protected:
       Character(-the info for the stats-(described above)) - constructor.
       Character(const Character& character) - copy constructor.

     * public:
        virtual Character* clone() - pure virtual function that makes a copy of the character.
        virtual ~Character() -  destructor.
        virtual void removeOneAmmo() - subtract 1 ammo unit
        health() - returns the character's health.
        ammo() - returns the ammount of ammo that the character has.
        range() - returns the character's range.
        power() - returns the character's power value.
        team() - returns what team the character is on.
        type() - returns the character's type. (for now - soldier / medic / sniper).
        maxMove() - returns the maximum amount of cells that a character can move in one turn.
        ammoLoad() - loads the character's ammo according to the ammo_load parameter of the character.
        attackCost() - returns how much ammo does an attack cost.
        health(-int-) - gets a value to add to the characters health (can be negative).
        load() - loads the characters ammo. (according to it's ammo_load parameter).
        canMove -   checks if the character can move from it's location to the target cell.
                    Assuming that the target cell is in the bounds of the game board.
        virtual legalAttack - checks if the targeted cell can be attacked from the location cell by the character.
        attackCharacter - returns the power of the attack.
        virtual adjacentDamage - virtual function - implemented if the sub class can damage near the target gridpoint
*
*/

    class Character
    {
        int char_health, char_range, char_power, char_max_move, char_ammo_load, char_attack_cost;
        Team char_team;
        CharacterType char_type;
    protected:
        int char_ammo;

        /**
         * Character- given the character stats the function will insert the info of the character
         *      @param - ♦health
         *               ♦ range (of attack)
         *               ♦powe
         *               ♦max_move
         *               ♦ammo_load
         *               ♦attack_cost
                         ♦the "Team" the character belongs to.
                         ♦CharacterType (from the verity given to us : solider/medic/sniper)
                @return - a character
         */
        Character();
        explicit Character(Team team_t, CharacterType type_t, units_t ammo_load_t = 0,
                           units_t health_t = 0, units_t ammo_t = 0, units_t range_t = 0,
                           units_t power_t = 0, units_t max_move_t =0, units_t attack_cost = 0);

        /**
         * Character - copy constructor.
         *      @param - character - the character we want to copy.
                @return - a new character.
         */
        Character(const Character& character);

    public:

        /**
         * clone() - pure virtual function that makes a copy of the character according to
         *          its type without slicing the its info.
                @return - a pointer to the new character.
         */
        virtual Character* clone() const = 0;

        /**
         * ~Character -  destructor.
         */
        virtual ~Character() = default;

        /**
         * removeOneAmmo -  subtract 1 ammo unit.
         */
        virtual void removeOneAmmo(){return;}

        //health - returns the character's health.
        int health() const;
        //ammo - returns the amount of ammo that the character has.
        int ammo() const;
        //range - returns the character's range.
        int range() const;
        //power - returns the character's power value.
        int power() const;
        //team - returns what team the character is on.
        Team team() const;
        //type - returns the character's type. (for now - soldier / medic / sniper).
        CharacterType type() const;
        //maxMove - returns the maximum amount of cells that a character can move in one turn.
        int maxMove() const;
        //ammoLoad - loads the character's ammo according to the ammo_load parameter of the character.
        int ammoLoad() const;
        //attackCost - returns how much ammo does an attack cost.
        int attackCost() const;

        //health() - gets a value to add to the characters health (can be negative).
        void health(int n);
        //load - loads the characters ammo. (according to it's ammo_load parameter).
        void load();

        /**
        canMove -   checks if the character can move from it's location to the target cell.
                    Assuming that the target cell is in the bounds of the game board.
        */
        bool canMove(const GridPoint location, const GridPoint target);

        /**
         * legalAttack - checks if the targeted cell can be attacked from the location cell by the character.
         *           @param -   location - the location of the character.
         *                      target - the location of the target.
         *           @return   - true - if the attack is legal.
         *                     - false - otherwise.
        */
        virtual bool legalAttack(const GridPoint location, const GridPoint target, std::shared_ptr<Character> target_char){return false;}

        /**
        attackCharacter - returns the power of the attack.
        @param      - start - the location of the character.
                    - end - the location of the desired target.
        */
        virtual int attackCharacter(GridPoint start, GridPoint end, Team target_team);

        /**
       attack      - calculate the power of the attack that should be implemented on the
                    enemy character given the distance between the target and the attacker.
       @param      - distance - the distance between the target and the attacker.

       @return     - an integer that holds the num of health that should be deducted from the enemy.
       */
        virtual int adjacentDamage(int distance){return 0;}

        friend class Exception;
    };
}

#endif //CHARACTER_H
