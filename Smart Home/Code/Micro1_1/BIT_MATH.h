/****************************************************************/
/*************     	Author : Adel Khaled     ********************/
/*************		Date   : 13-7-2022		 ********************/
/*************		Version: V.01            ********************/
/****************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(reg,n)       (reg |= (1<<n))
#define CLR_BIT(reg,n)       (reg &= ~(1<<n))
#define TOG_BIT(reg,n)       (reg ^= (1<<n))
#define GET_BIT(reg,n)       ((reg>>n) & 1)


#endif
