#pragma once
#include"Vec2.h"
#include<string>
#include<memory>

static const Vec2 UI_SIZE = { 420,940 };
static const Vec2 WINDOW_SIZE = { 640 + UI_SIZE.x,940 };
static const Vec2 GAME_WINDOW_SIZE = { WINDOW_SIZE.x - UI_SIZE.x,WINDOW_SIZE.y };
static const std::string TITLE = "10DaysProt";

static const std::string RESOUCE_PATH = "Resources/";

//rgb���Z�b�g�ɂȂ����\����(�v���g�p)
struct ColorDxLib
{
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
};
