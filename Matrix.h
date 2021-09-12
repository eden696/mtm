
#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H

#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include <memory>


/**
* _____________________________Matrix - shared_ptr<Character> _____________________________
*
* a struct that will contain information about the character in the game in a form of shared_ptr :
will contain a :
        ♦matrix
        ♦matHeight
        ♦matWidth
        ♦matSize

* The following functions are available:
 * public:
     Matrix(@arg) - constructor
    Matrix(const Matrix&) - copy constructor.
    ~Matrix() -  destructor.
    height() - get the height of the matrix.
    width() - get the height of the matrix.
    size() - get the num of the arg in the matrix.
    operator=
    operator(i,j) - accessing a cube inside of the matrix.
    operator<< - helper to print the matrix.
*
*/

namespace mtm
{
    class Matrix
    {
    private:
        std::shared_ptr<Character> *matrix;
        unsigned int matHeight, matWidth, matSize;
    public:
        /**
       * Character- given the arg well create a matrix of shared_ptr<Character>, as defult
         * the matrix will be 1X1 and th shared_ptr<Character> will be null ptr.
       *      @param - ♦ dims - the dim of the matrix
         *             ♦ value - a value that will be implemented to all the cubes in the matrix.
              @return - a Matrix.
       */
        explicit Matrix(const Dimensions dims = {1,1}, std::shared_ptr<Character> value = nullptr);

        /**
         * Matrix - copy constructor.
         *      @param - Matrix - the Matrix we want to copy.
                @return - a new Matrix.
         */
        Matrix(const Matrix&);

        /**
        * ~Matrix -  destructor.
        */
        ~Matrix();

        /**height - returns the matrix height*/
        const unsigned int& height() const;

        /**height - returns the matrix width*/
        const unsigned int& width() const;

        /**height - returns the matrix size*/
        const unsigned int& size() const;

        /**
        *operator= implementation of operator=.
        * @param matrix - the matrix we want to copy and later insert to "this".
        * @return
        *  a reference to Matrix.
        */
        Matrix& operator=(const Matrix matrix);


        /**
        * operator() - accessing a cube inside of the matrix.
        * @param x - the row.
                 y - the col.
        * @return
        *  a reference to the cube.
        */
        const std::shared_ptr<Character>& operator()(const unsigned int x, const unsigned int y) const;
        std::shared_ptr<Character>& operator()(const unsigned int x, const unsigned int y);

        /**
        * operator<< - access to output stream objects.
        * @param os - output stream objects.
                 x - the ,matrix.
        * @return
        *  output stream objects.
        */
        friend std::ostream &operator<<(std::ostream &os, Matrix &x);


        //the same as matrix.h from partB
        class iterator;
        iterator begin();
        iterator end();

        friend class Exception;
    };

    std::ostream &operator<<(std::ostream &os, const Matrix &x);




/**
* _____________________________Iterator - Matrix_____________________________
*
* a struct that will implement an iterator to go over the matrix cubes :
will contain a :
        ♦matrix
        ♦int

* The following functions are available:
 * public:
        iterator(@arg)- constructor.
        iterator - copy constructor.
        operator* - allows us to access the matrix where the iterator points to.
        operator++ - allows us to move the iterator to the next cube.
        operator== - allows us to know if the iterators between the '==' are equal.
        operator!= - allows us to know if the iterators between the '==' are not equal.
        operator= - implement the appointment of the copy constructor.
*
*/
    class Matrix::iterator
    {
    private:
        Matrix *matrix;
        unsigned int index;
        /**
         * iterator- given the iterator info the function will fill the info of the character
         *      @param - ♦a_matrix - a pointer to matrix
         *               ♦an_index - the index
                @return - an iterator
         */
        iterator(Matrix *a_matrix, unsigned int an_index);
        friend class Matrix;

    public:
        /**
         * operator* - returns the value from the matrix where the iterator is
         * */
        std::shared_ptr<Character>& operator*();

        /**
         * operator++ - advance the iterator to the next cube.
         * */
        iterator& operator++();
        iterator operator++(int);

        /**
         * operator== - returns true if the an_index is the same between the iterators around '=='
         * */
        bool operator==(const iterator &it) const;

        /**
         * operator!= - returns true if the an_index is not the same between the iterators around '!='
         * */
        bool operator!=(const iterator &it) const;

        /**
         * copy constructor - returns a copy to the iterator
         * */
        iterator(const iterator &) = default;

        /**
         * ocoperator= - implement the appointment of the copy constructor.
         * */
        iterator &operator=(const iterator &) = default;
    };
}

#endif //HW3_MATRIX_H
