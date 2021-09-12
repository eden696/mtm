#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>

    /**
    * _____________________________Exception_____________________________
    *
    * the Exception struct will contain a message (a string).
     * the class inherits std::exception.
     *
    * The following functions are available:
    * protected:
             Exception - constructor.
    * public:
            what - implement an "error massage" to the message inside the Exception.
    */

namespace mtm
{
    class Exception         : public std::exception
    {
        std::string message;
    protected:
        Exception(std::string message_t);
    public:
        const char* what() const noexcept;
    };
    /*_________________________GameException____________________________*/


    class GameException     : public Exception
    {
    protected:
        GameException(std::string message_t, std::string description_t = "A game related error has occured: ");
    };

    //IllegalArgument - In cases where the user tries to execute an invalid parameter.
    struct IllegalArgument  : public GameException
    {
        IllegalArgument();
    };

    //IllegalCell - In cases where a target slot of any action is not within the scope of the game board.
    struct IllegalCell      : public GameException
    {
        IllegalCell();
    };

    //CellEmpty - In cases where an attempt is made to run an action from an empty source slot
    struct CellEmpty        : public GameException
    {
        CellEmpty();
    };

    //MoveTooFar - In cases where an attempt is made to move a figure to a slot that is out of range.
    struct MoveTooFar       : public GameException
    {
        MoveTooFar();
    };

    //CellOccupied - In cases where an attempt is made to add a character to a slot that already contains a character.
    struct CellOccupied     : public GameException
    {
        CellOccupied();
    };

    //OutOfRange - In cases where a character tries to attack a slot that is outside the range of the attacker.
    struct OutOfRange       : public GameException
    {
        OutOfRange();
    };

    //OutOfAmmo - In cases where the character does not have enough ammunition to perform an attack.
    struct OutOfAmmo        : public GameException
    {
        OutOfAmmo();
    };

    //IllegalTarget - For cases where a character is unable to attack any target slot for non-range reasons.
    struct IllegalTarget    : public GameException
    {
        IllegalTarget();
    };

    // ______________Matrix Exceptions______________________  //


    // Exception for when there was an attempt to access an illegal element
    struct AccessIllegalElement : public Exception
    {
        AccessIllegalElement();
    };

    // Exception for when there was an attempt to create dimension of non positive int/
    struct IllegalInitialization : public Exception
    {
        IllegalInitialization();
    };

    // Exception for when there was an attempt to apply function that needs to be
    // applied on matrix from the same dimension but could not.
    struct DimensionMismatch : public Exception
    {
        DimensionMismatch(unsigned int matrix1_h, unsigned int matrix1_w,
                          unsigned int matrix2_h, unsigned int matrix2_w,
                          std::string description = "Mtm matrix error: Dimension mismatch: ");
    };
}

#endif //EXCEPTION_H
