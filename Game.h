#ifndef GAME_H
#define GAME_H

#include "Matrix.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include <memory>


/**
* _____________________________Game_____________________________
*
* the game struct will contain the following arguments:
        ✴board height, board width .
        ✴Matrix* board - matrix of pointers to characters.
        ✴int num_of_team1_players, num_of_team2_players - will keep a record of the number of players in each team.
*
* The following functions are available:

 * privet:
        getBoardHeight - tells us the height of the matrix.
        getBoardWidth - tells us the width of the matrix.
        inBounds - check if the points given are in the borders of the matrix.
        checkIllegalCoordinates - check if the point given is in the borders of the matrix.
        doCollateralDamage - implementing the damage to the area around the target - not all characters are able to.
 * public:
 *      Game(int height, int width) - game constructor.
        Game(const Game& other)- game copy constructor.
        ~Game() - game destructor.
        Game& operator=(const Game& other) -  implementation of operator= (between two game struct).
        addCharacter - adds a character in the board.
        makeCharacter- given starting stats of a character this function create a smart pointer to a character.
        move - move a character across the board.
        attack - implement damage the the enemy character/s.
        reload - add ammo to a character.
        friend std::ostream& operator<<(std::ostream &os, Game& game) - implementation of the printing function.
        isOver - tells us if there's a winner and if so who won.
*
*/


namespace mtm
{    /**
       printGameBoard  - prints the game board(matrix<char>).

       @params     - os - Output stream objects.
                   - begin - pointer to the beginning of the matrix.
                   - end - pointer to the end (+1) of the matrix.
                   - width - the width of the matrix.
       @return     - a board with the existing character in top of the board
                        ✶ capital letters symbols CPP team whereas lower case symbols PYTHON team✶
                        ♦n,N - symbols sniper
                        ♦s,S - symbols solider
                        ♦m,M - symbols medic
       */
    std::ostream& printGameBoard(std::ostream& os, const char* begin, const char* end, unsigned int width);

    class Game
    {
        int board_height, board_width;
        Matrix* board ;//A matrix of pointers to characters..
        int num_of_team1_players, num_of_team2_players; //will keep a record of the number of players in each team.

        //Extra methods.
        /**
       getBoardHeight  - tells us the height of the matrix of this game.
       @return     - int - the height of the matrix.
       */
        int getBoardHeight() const;

        /**
      getBoardWidth  - tells us the width of the matrix of this game.
      @return     - int - the width of the matrix.
      */
        int getBoardWidth() const;

        /**
       inBounds  - prints the game board(matrix<char>).

       @params     - point1 - coordinate on the board.
                   - point2 - coordinate on the board.
       @return     - true - if both points are in the matrix
                   - false - if any of the points is outside of the Limits of the board
       */
        bool inBounds(const GridPoint& point1, const GridPoint& point2);
        /**
       checkIllegalCoordinates  - prints the game board(matrix<char>).

       @params     - coordinates - coordinate on the board.
       @return     - true - if the coordinate is in the matrix.
                   - false - if the Coordinate  is outside of the Limits of the board.
       */
        bool checkIllegalCoordinates(const GridPoint& coordinates);

        /**
      doCollateralDamage  -helper function to implement damage to enemy characters around the target.

      @params     - location - the coordinate of the attacker.
                  - target- the coordinate of the attacked character.

      */

        void doCollateralDamage (const GridPoint& location, const GridPoint& target);
    public:

        /**
        Game - the game constructor
        @params     - height - the height og the board that we want.
                  - width - the width og the board that we want.
        @return     - a Game type file with its arguments.
        */
        Game(int height, int width);

        /**
        Game - a copy constructor
        @params     - other - the Game we want to copy
        @return     - a new Game type file with its arguments and the current sate in "other" game.
        */
        Game(const Game& other);

        /**
        ~Game - destructor
        */
        ~Game();

        /**
        operator= -  implementation of operator= (between two game struct).
        @params     - other - the Game we want to insert into "this" game.
        @return     - a refrence to Game.
        */
        Game& operator=(const Game& other);

        /**
        addCharacter -  adds a character in the board.
        @params      -  coordinates - the coordinates that the character will appear on.
                        character - a smart_ ptr of the character.

        */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /**
        makeCharacter - given starting stats of a character this function create a smart pointer to a character.
        @params     ♦type - the charcter type {sniper,solider,medic}
                    ♦team - the team that the character belongs to {cpp,PYTHON}
                    ♦health - the character health stat.
                    ♦ammo - the character ammo stat.
                    ♦range - the character ammo stat.
                    ♦power - the character ammo stat.
        @return     - a smart pointer to a character.
        */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
                                                        units_t ammo, units_t range, units_t power);

        /**
        move -  if possible this function moves a character across the board.
        @params   ♦src_coordinates - the original location
                  ♦dst_coordinates - the location we want to get to.
        */
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

        /**
        attack - implement damage the the enemy character/s.
        @params   ♦src_coordinates - the location of the character that will preform the attack.
                  ♦dst_coordinates - the location the coordinates that will be attacked.
        */
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

        /**
        reload - add ammo to a character.
        @params   ♦coordinates - the location of the character that will reload its ammo.
        */
        void reload(const GridPoint& coordinates);

        /**
        operator<< - a function that will creat a matrix of char according to the current
                    board with that matrix if will preform the print. .
        @params   ♦os - Output stream objects.
                  ♦game - the game that contains the board we want to print.
        */
        friend std::ostream& operator<<(std::ostream &os, Game& game);

        /**
        isOver - tells us if there's a winner and if so who won.
        @params     ♦ winningTeam - a pointer to the winning team if there is one.
        @return     - false - if there currently no winner.
                    - true - if there's a winner.
                    ✹ the winning team will be inserted into the pointer..
        */
        bool isOver(Team* winningTeam=NULL) const;
    };
    std::ostream& operator<<(std::ostream &os, Game& game);
}

#endif //GAME_H
