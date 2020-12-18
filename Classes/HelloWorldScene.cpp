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

#include "HelloWorldScene.h"
#include "PlayScreen.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Point p = Point(visibleSize.width / 2, visibleSize.height / 2);
    auto background = Sprite::create("Sky-Stars-Pattern.jpg");
    background->setPosition(p);
    this->addChild(background, -10);
    auto logo = Sprite::create("Logo.png");
    logo->setPosition(p);
    this->addChild(logo, 0);
    auto pantonio = Sprite::create("Pantonio.png");
    pantonio->setPosition(Point(visibleSize.width - 150, 90));
    this->addChild(pantonio, 0);
    int points[7][2] =
    {
        {800, 400}, {750, 300}, {850, 200}, {650, 450},
        {120, 100}, {100, 200}, {200, 50}
    };
   
    for (int i = 0; i < 7; i++) {
        auto image = Sprite::create("pp" + std::to_string(i+1) + ".png");
        image->setPosition(Point(points[i][0], points[i][1]));
        this->addChild(image);
    }

    auto scale = ScaleBy::create(3, 0.25);
    logo->runAction(scale);
    auto moveL = MoveTo::create(3, Point(150, visibleSize.height - 150));
    logo->runAction(moveL);
    auto moveUpandDown = Sequence::create(MoveBy::create(1, Point(0, 25)), MoveBy::create(1, Point(0, -25)), NULL);
    auto bounce = RepeatForever::create(moveUpandDown);
    logo->runAction(bounce);
    auto action = SkewBy::create(3, 180, 180);
    logo->runAction(action);

    auto play = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::Play, this));
    play->setFontSizeObj(150);
    play->setPosition(Point(visibleSize.width / 2, visibleSize.height / 8 * 5));
    auto exit = MenuItemFont::create("Exit", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    exit->setFontSizeObj(75);
    exit->setPosition(Point(visibleSize.width / 2, visibleSize.height / 8 * 2));
    auto info = MenuItemFont::create("?", CC_CALLBACK_1(HelloWorld::Information, this));
    info->setFontSizeObj(75);
    info->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
    auto* menu = Menu::create(play, exit, info, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void HelloWorld::Play(HelloWorld::Ref* pSender) {
    CCLOG("Play");
    auto scene = PlayScreen::createScene();
    Director::getInstance()->pushScene(scene);
}
void HelloWorld::Information(HelloWorld::Ref* pSender) {
    CCLOG("Information");
    /*
    auto scene = PlayScreen::createScene();
    //Director::getInstance() -> replaceScene(scene);
    Director::getInstance() -> replaceScene(TransitionCrossFade::create(2, scene));
    */
}