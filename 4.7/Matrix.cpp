#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include <memory>
#include "Matrix.h"

namespace mtm
{
    Matrix::Matrix(const Dimensions dims, std::shared_ptr<Character> value)
    {
        if(dims.getCol()<0 || dims.getRow()<0){ //Sends error if the initialization values are illegal.
            IllegalInitialization error;
            throw error;
        }

        matHeight = dims.getRow();
        matWidth = dims.getCol();
        matSize = matHeight * matWidth;

        matrix = new std::shared_ptr<Character>[matSize];

        for (unsigned int i = 0; i < matSize; i++) {
            matrix[i] = value;
        }
    }


    Matrix::Matrix(const Matrix& old_matrix) :
            matrix(new std::shared_ptr<Character>[old_matrix.matSize]), matHeight(old_matrix.matHeight),
            matWidth(old_matrix.matWidth), matSize(old_matrix.matSize)
    {
        for (unsigned int i = 0; i < old_matrix.matSize; i++) {
            matrix[i] = old_matrix.matrix[i];
        }
    }

    Matrix::~Matrix()
    {
        delete[] matrix;
    }

    Matrix& Matrix::operator=(const Matrix x)
    {
        if (this == &x) {
            return *this;
        }
        delete[] matrix;
        matSize = x.matSize;
        matHeight = x.matHeight;
        matWidth = x.matWidth;
        matrix = new std::shared_ptr<Character>[matSize];

        for (unsigned int i = 0; i < x.matSize; i++) {
            matrix[i] = x.matrix[i];
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream &os, Matrix &matrix)
    {
        return printMatrix(os, matrix.begin(), matrix.end(), matrix.matWidth);
    }

    const std::shared_ptr<Character>& Matrix::operator()(const unsigned int x, const unsigned int y) const
    {
        if ((x < 0) || (y < 0) || (x >= (*this).matHeight) || (y >= (*this).matWidth)) {
            AccessIllegalElement error;
            throw error;
        }
        return (*this).matrix[x * (*this).matWidth + y];
    }

    std::shared_ptr<Character>& Matrix::operator()(const unsigned int x, const unsigned int y)
    {
        if ((x < 0) || (y < 0) || (x >= (*this).matHeight) || (y >= (*this).matWidth)) {
            AccessIllegalElement error;
            throw error;
        }
        return (*this).matrix[x * (*this).matWidth + y];
    }

    //Iterator's methods
    Matrix::iterator::iterator(Matrix *a_matrix, unsigned int an_index)
    {
        index = an_index;
        matrix = a_matrix;
    }

    std::shared_ptr<Character>& Matrix::iterator::operator*()
    {
        if ((index < 0) || (index >= ((this->matrix)->matSize))){
            throw AccessIllegalElement();
        }
        return (*matrix).matrix[index];
    }

    typename Matrix::iterator& Matrix::iterator::operator++()
    {
        ++index;
        return *this;
    }

    typename Matrix::iterator Matrix::iterator::operator++(int)
    {
        iterator result = *this;
        ++*this;
        return result;
    }

    bool Matrix::iterator::operator==(const iterator &it) const
    {
        return index == it.index;
    }

    bool Matrix::iterator::operator!=(const iterator &it) const
    {
        return !(*this == it);
    }

    typename Matrix::iterator Matrix::begin()
    {
        return iterator(this, 0);
    }

    typename Matrix::iterator Matrix::end()
    {
        return iterator(this, matSize);
    }
}
