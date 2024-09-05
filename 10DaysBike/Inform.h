#pragma once
#include"Vec2.h"
#include<string>
#include<memory>

static const Vec2 WINDOW_SIZE = { 640,940 };
static const std::string TITLE = "10DaysProt";

//rgbがセットになった構造体(プロト用)
struct ColorDxLib
{
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
};
