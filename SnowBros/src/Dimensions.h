/*
 * Dimensions.h
 *
 *  Created on: 18 apr 2019
 *      Author: francesco
 */

#ifndef DIMENSIONS_H_
#define DIMENSIONS_H_

class Dimensions
{
public:
	float x;
	float y;
	static Dimensions createDimensions(float x, float y)
	{
		Dimensions tmp = {x, y};
		return tmp;
	}
};

#endif /* DIMENSIONS_H_ */
