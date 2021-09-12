#include "Exceptions.h"
#include <string>

namespace mtm
{
    Exception::Exception(std::string message_t) : message(message_t){}

    const char* Exception::what() const noexcept
    {
        return const_cast<char*>(message.c_str());
    }

    GameException::GameException(std::string message_t, std::string description_t)
            : Exception(description_t + message_t){}

    IllegalArgument::IllegalArgument()  : GameException("IllegalArgument") {}
    IllegalCell::IllegalCell()          : GameException("IllegalCell") {}
    CellEmpty::CellEmpty()              : GameException("CellEmpty") {}
    MoveTooFar::MoveTooFar()            : GameException("MoveTooFar") {}
    CellOccupied::CellOccupied()        : GameException("CellOccupied") {}
    OutOfAmmo::OutOfAmmo()              : GameException("OutOfAmmo") {}
    OutOfRange::OutOfRange()            : GameException("OutOfRange") {}
    IllegalTarget::IllegalTarget()      : GameException("IllegalTarget") {}

    AccessIllegalElement::AccessIllegalElement() :
                Exception("Mtm matrix error: An attempt to access an illegal element") {}

    IllegalInitialization::IllegalInitialization() :
                Exception("Mtm matrix error: Illegal initialization values") {}

    DimensionMismatch::DimensionMismatch(unsigned int matrix1_h, unsigned int matrix1_w,
                unsigned int matrix2_h, unsigned int matrix2_w, std::string description) :
                Exception(description + "(" + std::to_string(matrix1_h) + "," + std::to_string(matrix1_w)
                + ") (" + std::to_string(matrix2_h) + "," + std::to_string(matrix2_w) + ")") {}

}
