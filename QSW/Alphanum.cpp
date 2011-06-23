/**
 * \file alphanum.cpp
 * \brief Description
 */



#include "Alphanum.h"

/*!
 *    \fn    compare - сравнивает две строки.
 *    \param    l - строка слева.
 *    \param    r - строка справа.
 *
 *    \return 
 *        l<r - отрицательное значение;
 *        l>r - положительное значение;
 *        l=r - нуль.
 */
int compare(QString l, QString r)
{
    enum Mode{STRING, NUMBER} mode = STRING;
    int size;
    if (l.size() < r.size())
        size = l.size();
    else
        size = r.size();

    int i = 0;
    
    // бежим по обоим строчкам в право до позиции "size-1"
    while(i < size){
        if (mode == STRING){
            QChar lchar, rchar;
            bool ldigit, rdigit;
            while(i < size){
                lchar = l.at(i);
                rchar = r.at(i);
                ldigit = lchar.isDigit();
                rdigit = rchar.isDigit();
                // Если оба символа являются числами, то переходим в режим чисел
                if (ldigit && rdigit){
                    mode = NUMBER;
                    break;
                }
                if (ldigit) return -1;
                if (rdigit) return +1;
                // Оба символа - буквы
                if (lchar < rchar) return -1;
                if (lchar > rchar) return +1;
                // Оба символа равны друг другу
                i++;
            }
        }else{//mode == NUMBER
            unsigned long long lnum = 0, rnum = 0;
            int li = i, ri = i; // локальные индексы
            int ld = 0, rd = 0; // цифры
            
            // собираем левое число
            while(li < l.size()){
                ld = l.at(li).digitValue();
                if (ld < 0 ) break;
                lnum = lnum*10 + ld;
                li++;
            }
            
            // собираем правое число
            while(ri < r.size()){
                rd = r.at(ri).digitValue();
                if (rd < 0 ) break;
                rnum = rnum*10 + rd;
                ri++;
            }
            
            long long delta = lnum - rnum;
            if (delta) return delta;
            
            // числа одинаковы
            mode = STRING;
            if (li <= ri)
                i=li;
            else
                i=ri;
        }
    }
    // Сюда попадём если обе строки до позиции "size-1" одинаковы
    if (i < r.size()) return -1;
    if (i < l.size()) return +1;
    
    // Обе сроки полностью одинаковы
    return 0;    
}