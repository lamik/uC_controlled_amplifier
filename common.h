/*
 * common.h
 *
 *  Created on: 15-08-2013
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

#endif /* COMMON_H_ */
