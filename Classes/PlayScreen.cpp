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
#include "Careful.h"

USING_NS_CC;

Scene* PlayScreen::createScene()
{
    return PlayScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("Saturn.jpeg");
    background->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);

    auto menu_item_1 = MenuItemFont::create("Go Back", CC_CALLBACK_1(PlayScreen::GoBack, this));
    menu_item_1->setFontSizeObj(50);
    menu_item_1->setPosition(Point(150, visibleSize.height-100));
    auto menu_item_2 = MenuItemFont::create("Play", CC_CALLBACK_1(PlayScreen::Play, this));
    menu_item_2->setFontSizeObj(50);
    menu_item_2->setPosition(Point(visibleSize.width -100, 100));

    auto* menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    return true;
}

void PlayScreen::GoBack(Ref* pSender) {
    //Director::getInstance() -> popScene();
    auto scene = HelloWorld::createScene();
    //Director::getInstance() -> replaceScene(scene);
    Director::getInstance()->replaceScene(TransitionFlipAngular::create(2, scene));
}

void PlayScreen::Play(Ref* pSender) {

    CCLOG("To first game.");
    //auto scene = FindaWay::createScene();
    auto scene = Careful::createScene();
    Director::getInstance()->pushScene(scene);
}

