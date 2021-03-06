#include "Matrix.h"

double determ(QVector<QVector<int>> Arr, int size);

Matrix::Matrix()
{
    m_name = "default";
    m_height = m_width = 3;
    for(int i = 0; i < 3; i++)
    {
        QVector <int> temp;
        for(int j = 0; j < 3; j++)
        {
            temp.push_back(0);
        }
        m_Matrix.push_back(temp);
    }
}
Matrix::Matrix(int height, int width, QString name)
{
    m_name = name;
    m_height = height;
    m_width = width;
    for(int i = 0; i < height; i++)
    {
        QVector <int> temp;
        for(int j = 0; j < width; j++)
        {
            temp.push_back(0);
        }
        m_Matrix.push_back(temp);
    }
}
Matrix::Matrix(QVector<QVector<int>> QVec_matrix, QString name)
{
    m_name = name;
    m_height = QVec_matrix.size();
    m_width = QVec_matrix[0].size();
    m_Matrix = QVec_matrix;
}
Matrix::~Matrix()
{

}

QString Matrix::getName()
{
    return m_name;
}
void Matrix::setName(QString name)
{
    m_name = name;
}
QVector<QVector<int>> Matrix::getVecMatrix()
{
    return  m_Matrix;
}
void Matrix::setVecMatrix(QVector<QVector<int>> QVecMatr)
{
    m_Matrix = QVecMatr;
}
int Matrix::getHeight()
{
    return m_height;
}
int Matrix::getWidth()
{
    return m_width;
}

double Matrix::determinant()
{
    double result = determ(m_Matrix,m_height);
    return result;
}

void Matrix::transpose()
{
    QVector<QVector<int>> tempM;
    for(int i = 0; i < m_width; i++){
        QVector<int> tempV;
        for(int j = 0; j < m_height; j++){
            tempV.push_back(m_Matrix[j][i]);
        }
        tempM.push_back(tempV);
    }
    m_Matrix = tempM;
    std::swap(m_width, m_height);
}

Matrix & Matrix::operator = (const Matrix second_Matrix)
{
    m_name = second_Matrix.m_name;
    m_height = second_Matrix.m_height;
    m_width = second_Matrix.m_width;
    m_Matrix = second_Matrix.m_Matrix;
    return *this;
}

Matrix &Matrix::operator +(int value)
{
    for(int i = 0; i < m_Matrix.size(); i++)
    {
        for(int j = 0; j < m_Matrix[i].size(); j++)
        {
            m_Matrix[i][j]+=value;
        }
    }
    return *this;
}
Matrix &Matrix::operator -(int value)
{
    for(int i = 0; i < m_Matrix.size(); i++)
    {
        for(int j = 0; j < m_Matrix[i].size(); j++)
        {
            m_Matrix[i][j]-=value;
        }
    }
    return *this;
}
Matrix &Matrix::operator *(int value)
{
    for(int i = 0; i < m_Matrix.size(); i++)
    {
        for(int j = 0; j < m_Matrix[i].size(); j++)
        {
            m_Matrix[i][j]*=value;
        }
    }
    return *this;
}

Matrix &Matrix::operator ^(int value)
{
    if(m_height == m_width)
    {
        Matrix clone(m_Matrix,m_name);
        for(int i = 0; i < value - 1; i++){
            this->operator*(clone);
        }
    }
    return *this;
}

Matrix &Matrix::operator +(Matrix second_Matrix)
{
    if(m_width == second_Matrix.m_width && m_height == second_Matrix.m_height)
    {
        for(int i = 0; i < m_height; i++)
        {
            for(int j = 0; j < m_width; j++)
            {
                m_Matrix[i][j] += second_Matrix.m_Matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix &Matrix::operator -(Matrix second_Matrix)
{
    if(m_width == second_Matrix.m_width && m_height == second_Matrix.m_height)
    {
        for(int i = 0; i < m_height; i++)
        {
            for(int j = 0; j < m_width; j++)
            {
                m_Matrix[i][j] -= second_Matrix.m_Matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix &Matrix::operator *(Matrix second_Matrix)
{
    QVector<QVector<int>> temp_m;
    if(m_width == second_Matrix.m_height)
    {
        for(int i = 0; i < m_height; i++)
        {
            QVector<int> temp_vec;
            for(int j = 0; j < second_Matrix.m_width; j++)
            {
                int a = 0;
                for (int k = 0; k < m_width; k++)
                {
                    a += m_Matrix[i][k] * second_Matrix.m_Matrix[k][j];
                }
                temp_vec.push_back(a);
            }
            temp_m.push_back(temp_vec);
        }
        m_Matrix = temp_m;
        m_height = m_Matrix.size();
        m_width = m_Matrix[0].size();
    }
    return *this;
}

bool Matrix::operator ==(const Matrix second_Matrix)
{
     if(m_name == second_Matrix.m_name &&
        m_height == second_Matrix.m_height &&
        m_width == second_Matrix.m_width &&
        m_Matrix == second_Matrix.m_Matrix)
        return true;
     else
         return false;
}

bool Matrix::operator !=(const Matrix second_Matrix)
{
    if(m_name == second_Matrix.m_name &&
       m_height == second_Matrix.m_height &&
       m_width == second_Matrix.m_width &&
       m_Matrix == second_Matrix.m_Matrix)
       return false;
    else
        return true;
}

QVector<int> &Matrix::operator [](int index)
{
    return m_Matrix[index];
}

double determ(QVector<QVector<int>> Arr, int size)
{
        int i,j;
        double det=0;
        if(size==1)
        {
                det=Arr[0][0];
        }
        else if(size==2)
        {
                det=Arr[0][0]*Arr[1][1]-Arr[0][1]*Arr[1][0];
        }
        else
        {
                QVector<QVector<int>>matr(size-1);
                for(i=0;i<size;++i)
                {
                        for(j=0;j<size-1;++j)
                        {
                                if(j<i)
                                        matr[j]=Arr[j];
                                else
                                        matr[j]=Arr[j+1];
                        }
                        det+=pow((double)-1, (i+j))*determ(matr, size-1)*Arr[i][size-1];
                }
        }
        return det;
}

