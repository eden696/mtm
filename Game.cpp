#include "Game.h"
#define RANGE_DIVIDER 3
#define ATTACK_DIVIDER 3


namespace mtm
{
    std::ostream& printGameBoard(std::ostream& os, const char* begin,
                                 const char* end, unsigned int width) {
        std::string delimiter = std::string(2 * width + 1, '*');
        const char* temp = begin;
        os << delimiter << std::endl;
        while(temp != end) {
            os << "|" << (*temp);
            ++temp;
            if ((temp - begin) % width == 0)
                os << "|" << std::endl;
        }
        os << delimiter;
        delete[] begin;
        return os;
    }

    int Game::getBoardHeight() const
    {
        return board_height;
    }
    int Game::getBoardWidth() const
    {
        return board_width;
    }

    // returns true if the coordinates are illegal
    bool Game::checkIllegalCoordinates(const GridPoint& coordinates)
    {
        return (coordinates.row >= board_height ||
                coordinates.col >= board_width ||
                coordinates.row < 0 || coordinates.col < 0);
    }

    Game::Game(int height, int width)
    {
        if(height<=0 || width<=0){
            throw IllegalArgument() ;
        }
        num_of_team1_players = num_of_team2_players = 0;
        Dimensions dims(height, width);
        board = new Matrix(dims);
        board_height = height;
        board_width = width;
    }

    Game::~Game()
    {
        delete[] board;
    }

    Game::Game(const Game& other)
    {
        Dimensions dims(other.board_height, other.board_width);
        board = new Matrix(dims);
        board_height = other.board_height;
        board_width = other.board_width;
        for(int i=0; i<other.board_height; i++){
            for(int j=0; j<other.board_width; j++){
                if((*other.board)(i,j)!=nullptr){
                    (*board)(i,j) = std::shared_ptr<Character>((*other.board)(i,j)->clone());
                }
            }
        }
        num_of_team2_players = other.num_of_team2_players;
        num_of_team1_players = other.num_of_team1_players;
    }

    Game& Game::operator=(const Game& other)
    {
        if (this == &other){
            return *this;
        }
        delete board;
        board = other.board;
        num_of_team2_players = other.num_of_team2_players;
        num_of_team1_players = other.num_of_team1_players;
        board_height = other.getBoardHeight();
        board_width = other.getBoardWidth();
        return (*this);
    }

    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {

        if(checkIllegalCoordinates(coordinates)){
            IllegalCell error;
            throw error;
        }
        if ((*board)(coordinates.row ,coordinates.col) != nullptr){
            CellOccupied error;
            throw error;
        }
        ((*board)(coordinates.row ,coordinates.col)) = (character);
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health,
                                                   units_t ammo, units_t range, units_t power)
    {
        if(health<=0 || power<0 || ammo<0 || range<0){
            IllegalArgument error;
            throw error;
        }
        switch (type) {
            case SOLDIER: {
                std::shared_ptr<Character> character(new Soldier(team, health, ammo, range, power));
                return character;
            }
            case SNIPER: {
                std::shared_ptr<Character> character(new Sniper(team, health, ammo, range, power));
                return character;
            }
            case MEDIC: {
                std::shared_ptr<Character> character(new Medic(team, health, ammo, range, power));
                return character;
            }
            default: {
                std::shared_ptr<Character> character = nullptr;
                return character;
            }
        }
    }

    void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {

        if(checkIllegalCoordinates(src_coordinates) || checkIllegalCoordinates(dst_coordinates)) {
            IllegalCell error;
            throw error;
        }
        if ((*board)(src_coordinates.row ,src_coordinates.col) == nullptr) {
            CellEmpty error;
            throw error;
        }
        if (!(*board)(src_coordinates.row ,src_coordinates.col)->canMove(src_coordinates, dst_coordinates)) {
            MoveTooFar error;
            throw error;
        }
        if ((*board)(dst_coordinates.row ,dst_coordinates.col) != nullptr) {
            CellOccupied error;
            throw error;
        }

        (*board)(dst_coordinates.row ,dst_coordinates.col) = (*board)(src_coordinates.row ,src_coordinates.col);
        (*board)(src_coordinates.row ,src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        std::shared_ptr<Character> attacker((*board)(src_coordinates.row, src_coordinates.col));
        std::shared_ptr<Character> target((*board)(dst_coordinates.row, dst_coordinates.col));

        if(!inBounds(src_coordinates, dst_coordinates)){
            IllegalCell error;
            throw error;
        }

        if(attacker==nullptr){
            CellEmpty error;
            throw error;
        }
        bool legal = false;

        try {
            legal = attacker->legalAttack(src_coordinates, dst_coordinates, target);
        }
        catch (OutOfRange& e){
            throw e;
        }
        catch (IllegalTarget& e){
            throw e;
        }
        if (attacker->ammo() <= 0 ){
            OutOfAmmo error;
            throw error;
        }
        if(legal){
            if(target != nullptr){
                target->health(attacker->attackCharacter(src_coordinates, dst_coordinates, target->team()));
            }
            if(target == nullptr && attacker->type() == SOLDIER){
                attacker->removeOneAmmo();
            }
            doCollateralDamage(src_coordinates, dst_coordinates);
        }
        for(int i=0; i<board_height; i++) {
            for (int j = 0; j < board_width; j++) {
                if((*board)(i,j)!=nullptr){
                    if((*board)(i,j)->health() <= 0){
                        (*board)(i,j) = nullptr;
                    }
                }
            }
        }
    }

    void Game::doCollateralDamage (const GridPoint& location, const GridPoint& target)
    {

        for(int i=0; i<board_height; i++) {
            for (int j = 0; j < board_width; j++) {
                GridPoint cell = GridPoint(i, j);
                if((*board)(i,j)!=nullptr && (*board)(i,j)->team()!=(*board)(location.row, location.col)->team()){
                    int damage = (*board)(location.row, location.col)->adjacentDamage(GridPoint::distance(cell, target));
                    (*board)(i,j)->health(damage);
                }
            }
        }
    }

    bool Game::inBounds(const GridPoint& point1, const GridPoint& point2)
    {
        if(point1.row<0 || point1.col<0 || point2.row<0 || point2.col<0){
            return false;
        }
        if(point1.row>=board_height||point1.col>=board_width){
            return false;
        }
        return !(point2.row >= board_height || point2.col >= board_width);
    }

    void Game::reload(const GridPoint& coordinates)
    {
        if(checkIllegalCoordinates(coordinates)) {
            IllegalCell error;
            throw error;
        }
        if ((*board)(coordinates.row, coordinates.col) == nullptr) {
            CellEmpty error;
            throw error;
        }
        (*board)(coordinates.row, coordinates.col)->load();
    }

    std::ostream& operator<<(std::ostream &os, Game& game)
    {
        Team current_team;
        CharacterType current_character_type;
        char* ptr_matrix = new char[game.getBoardWidth() * game.getBoardHeight()];
        for(int i=0; i<game.getBoardHeight(); i++){
            for(int j=0; j<game.getBoardWidth(); j++){
                if ((*game.board)(i,j) != nullptr){
                    current_team = (*game.board)(i,j)->team();
                    current_character_type = (*game.board)(i,j)->type();
                    switch (current_character_type){
                        case SOLDIER: {
                            ptr_matrix[(i*game.getBoardWidth()) +j] = (current_team == CPP)? 'S' : 's';
                            break;
                        }
                        case SNIPER: {
                            ptr_matrix[(i*game.getBoardWidth()) +j] = (current_team == CPP)? 'N' : 'n';
                            break;
                        }
                        case MEDIC: {
                            ptr_matrix[(i*game.getBoardWidth()) +j] = (current_team == CPP)? 'M' : 'm';
                            break;
                        }
                    }
                }
                else{
                    ptr_matrix[(i*game.getBoardWidth()) +j] = ' ';
                }
            }
        }
        return printGameBoard(os, ptr_matrix, ptr_matrix + game.getBoardWidth()* game.getBoardHeight(), game.getBoardWidth());
    }

    bool Game::isOver(Team* winningTeam) const
    {
        int cpp_counter = 0, python_counter = 0;
        for(int i=0; i<board_height; i++)
        {
            for(int j=0; j<board_width; j++) {
                if ((*board)(i, j) != nullptr) {
                    ((*board)(i, j)->team() == CPP) ? cpp_counter++ : python_counter++;
                }
            }
        }

        if (cpp_counter == 0 && python_counter != 0){
            *winningTeam = PYTHON;
            return true;
        }

        if (cpp_counter != 0 && python_counter == 0){
            *winningTeam = CPP;
            return true;
        }
        return false;
    }
}
