/**
 * File: color.hpp
 * Initial Author: andimoto
 */
#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"

enum class color : std::uint8_t{
	RED,
	RED1,
	ORANGE,
	ORANGE1,
	YELLOW,
	YELLOW1,
	LIGHTGREEN,
	LIGHTGREEN1,
	GREEN,
	GREEN1,
	AQUAMARINE,
	AQUAMARINE1,
	CYAN,
	CYAN1,
	AZURE,
	AZUR1,
	BLUE,
	BLUE1,
	VIOLET,
	VIOLET1,
	MAGENTA,
	MAGENTA1,
	ROSE,
	ROSE1,
	ALL_COLORS
};

enum class LED : std::uint8_t
{
	RED,
	GREEN,
	BLUE,
	ALL
};


const std::uint8_t colorValues[static_cast<std::uint8_t>(color::ALL_COLORS)][static_cast<std::uint8_t>(LED::ALL)] = {
		{255,000,000},/* Red */
		{255,100,000},/* Red1 */
		{255,150,000},/* Orange */
		{255,200,000},/* Orange1 */
		{255,255,000},/* Yellow */
		{200,255,000},/* Yellow1 */
		{150,255,000},/* Lightgreen */
		{100,255,000},/* Lightgreen1 */
		{000,255,000},/* Green */
		{000,255,100},/* Green1 */
		{000,255,150},/* Aquamarine */
		{000,255,200},/* Aquamarine1 */
		{000,255,255},/* Cyan */
		{000,200,255},/* Cyan1 */
		{000,150,255},/* Azure */
		{000,100,255},/* Azure1 */
		{000,000,255},/* Blue */
		{100,000,255},/* Blue1 */
		{150,000,255},/* Violet */
		{200,000,255},/* Violet1 */
		{255,000,255},/* Magenta */
		{255,000,200},/* Magenta1 */
		{255,000,150},/* Rose */
		{255,000,100} /* Rose1 */
};


#endif /* COLOR_H_ */
