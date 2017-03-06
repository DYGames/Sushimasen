#pragma once

#define D_DESIGN_WIDTH 720
#define D_DESIGN_HEIGHT 1280

#define D_WINDOWS_SHOW 0.75

#define D_GAME_NAME "Sushi Masen"

#define GAME_FONT "status/font.ttf"

#define HALL true
#define KITCHEN false

#define N_ITEM 6
#define N_MATERIAL 22

#define FONT_SIZE_NUM 35
#define FONT_SIZE_INFO 20

#define N_BUYITEM 22

#define MOVEBTAG 88

#define CANTTOUCH !Popup::getInstance()->getPopupOpen() && !Inventory::getInstance()->getisInvOn() && !StaffMng::getInstance()->getIsStaffMenuOn() && !Store::getInstance()->getStoreOpen() && !Option::getInstance()->getOptionOpen() && !Recipe::getInstance()->isRecipeOn()

#define MOVESCENE(t, p) Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);\
					 Director::getInstance()->replaceScene(TransitionFade::create((t), (p)));

#define GUESTLIMIT 25

#define TYPEGUEST 6

#define N_HALL 8
#define N_WAIT 3

#define COOKSUSHIXLIMIT 1775
#define POPUPXLIMIT 1835
#define INVENTORYMATERIALXLIMIT 1800
#define STOREMATXLIMIT 1900
#define STOREITEMXLIMIT 50

#define B_LEFT			100
#define B_RIGHT			101
#define M_LEFT			102
#define M_RIGHT			103
#define M_UNDER			104
#define OBSTACLE        105
#define MISSILE			106
#define HITPOINT		107
#define BARRIER			108
#define BOOM			109
#define ITEM			110
#define BARRIERITEM		111
#define TIMER			112
#define LIFE			113
#define DIE				114

#define EXPITEM 100

enum
{
	SPRING = 1,
	SUMMER,
	FALL,
	WINTER,
};

enum
{
	MINIGAME = 0,
	STORE,
	RECIPE,
	INVENTORY,
	OPTION,
	STAFF,
	EXIT,
};

enum
{
	ZBACKGROUND = 0,
	ZMAT,
	ZGUEST,
	ZMENU,
	ZOPENMENU,
	ZMOVEBUT,
	ZINVENTORY,
	ZPOPUPSCROLL,
	ZPOPUP,
};

enum G_Z_ORDER
{
	BACKGROUND,
	OBJ,
	HIT,
	UNIT,
	INTER,
};

enum Direction
{
	RIGHT_UP,
	RIGHT_DOWN,
	LEFT_UP,
	LEFT_DOWN,
};

enum box
{
	one,
	two,
	three,
};
enum question
{
	Answer1,
	Answer2,
	Answer3,
	incorrect4,
	incorrect5,
	incorrect6,
	incorrect7,
	incorrect8,
	incorrect9,
	incorrect10,
	incorrect11,
	incorrect12,
	incorrect13,
	incorrect14,
	incorrect15,
};