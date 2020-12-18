/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Careful.h"
#include "Finish.h"
#include "PlayScreen.h"

USING_NS_CC;

extern bool redWins;
extern int puntaje;

Scene* Finish::createScene()
{
    return Finish::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Finish::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto background = Sprite::create("FinishBackground.jpeg");
    background->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);

    auto gana = Label::createWithSystemFont((redWins? "Red Wins": "Blue Wins"), "Arial", 70);
    gana->setPosition(Vec2(visibleSize.width/2 + 200, visibleSize.height - 200));
    this->addChild(gana);
    auto puntos = Label::createWithSystemFont("Puntos: " + std::to_string(puntaje), "Arial", 40);
    puntos->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height - 300));
    this->addChild(puntos);

    auto menu_item_1 = MenuItemFont::create("Play Again", CC_CALLBACK_1(Finish::Play, this));
    menu_item_1->setFontSizeObj(50);
    menu_item_1->setPosition(Point(150,100));
    auto menu_item_2 = MenuItemFont::create("Menu", CC_CALLBACK_1(Finish::Menu, this));
    menu_item_2->setFontSizeObj(50);
    menu_item_2->setPosition(Point(visibleSize.width -100, visibleSize.height - 100));

    auto* menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    return true;
}

void Finish::Play(Ref* pSender) {
    auto scene = Careful::createScene();
    //Director::getInstance() -> replaceScene(scene);
    //Director::getInstance()->replaceScene(TransitionCrossFade::create(2, scene));
    Director::getInstance()->pushScene(scene);
}

void Finish::Menu(Ref* pSender) {
    auto scene = PlayScreen::createScene();
    //Director::getInstance() -> replaceScene(scene);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2, scene));
    /*
    CCLOG("To first game.");
    //auto scene = FindaWay::createScene();
    auto scene = Careful::createScene();
    Director::getInstance()->pushScene(scene);
    */
}

