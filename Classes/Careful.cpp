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
#include "Finish.h"

USING_NS_CC;

bool redWins;
int puntaje = 0;

class Graph {
public:
    int nV;
    int mat[100][100];
    std::vector<cocos2d::Point> points;
    Graph(int nV, bool complete = false) : nV(nV) {
        for (int i = 0; i < nV; i++)
            for (int j = 0; j < nV; j++)
                if (i != j) mat[i][j] = complete;
    }
    bool hasTriangle(int node, int player = 10) {
        for (int i = 0; i < nV; i++) {
            for (int j = 0; j < nV && mat[node][i] == player; j++) {
                if (mat[node][j] == player && mat[i][j] == player)
                    return true;
            }
        }
        return false;
    }
    DrawNode* draw(double x, double y) {
        int size = 200;
        double angle = 2 * M_PI / nV;
        DrawNode* graph = DrawNode::create();
        for (int i = 0; i < nV; i++) {
            auto p = Point(x + size * cos(angle * i), y + size * sin(angle * i));
            //graph -> drawDot(p, 50, Color4F::YELLOW);
            graph->drawDot(p, 10, Color4F::WHITE);
            points.push_back(p);
            
            for (int j = 0; j < points.size(); j++) {
                if (i != j) {
                    graph->drawLine(points[i], points[j], (mat[i][j] == 10 ? Color4F::RED : (mat[i][j] == -10 ? Color4F::BLUE : Color4F::WHITE)));
                }
            }
        }
        return graph;
    }
    bool connect(int a, int b, bool player = true) {
        if (abs(mat[a][b]) == 10) return false;
        mat[a][b] = mat[b][a] = (player? 10: -10);
        return true;
    }
    std::pair<int, int> play() {
        int a = rand(), x;
        for (int i = 0; i < nV; i++) 
            for (int j = 0; j < nV; j++) {
                x = (i + a) % nV;
                if (x != j && mat[x][j] == 1) {
                    connect(x, j, false);
                    return std::make_pair(x, j);
                }
            }
    }
} g(6, true);

Scene* Careful::createScene()
{
    return Careful::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Careful::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    x = visibleSize.width / 2, y = visibleSize.height / 2;

    puntaje = 0, selected = NULL;

    score = Label::createWithSystemFont("Score: 0", "Arial", 30);
    score->setPosition(Vec2(100, visibleSize.height - 50));
    for (int i = 0; i < planetas.size(); i++) {
        planetas[i]->removeFromParent();
        planetas[i] = NULL;
    }
    planetas.clear();
    planetas.resize(10);

    //auto graph = g.draw(x, y);
    //this->addChild(graph);
    node = g.draw(x, y);
    this -> addChild(node);

    for (int i = 0; i < g.points.size(); i++) {
        std::string s = "pp" + std::to_string(rand() % 7 + 1) + ".png";
        planetas[i] = Sprite::create(s);
        planetas[i]->setPosition(g.points[i]);
        this->addChild(planetas[i]);
    }

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Careful::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Careful::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Careful::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(score);
    //this->scheduleUpdate();
    return true;
}
int closeTo(cocos2d::Vec2 pos) {
    for (int i = 0; i < g.points.size(); i++)
        if (g.points[i].getDistanceSq(pos) < 500)
            return i;
    return -1;
}
bool Careful::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    int planet = closeTo(touch -> getLocation());
    if (selected) {
        auto smaller = ScaleTo::create(0.1, 1);
        selected->runAction(smaller);
        selected = NULL;
    }
    else if (planet >= 0) {
        auto bigger = ScaleTo::create(0.1, 1.5);
        planetas[planet]->runAction(bigger);
        selected = planetas[planet];
    }
    return true;
}
bool Careful::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    CCLOG("Moved\tx = %f,\ty = %f", touch->getLocation().x, touch->getLocation().y);
    return true;
}

bool Careful::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    int planet = closeTo(touch->getLocation());
    if (selected) {
        auto smaller = ScaleTo::create(0.1, 1);
        auto bigger = ScaleTo::create(0.1, 1.5);
        if (planet >= 0) {
            if (planetas[planet] != selected) {
                int pu = 0, pd = 0;
                for (int i = 0; i < planetas.size(); i++) {
                    if (selected == planetas[i]) pu = i;
                    if (planetas[planet] == planetas[i]) pd = i;
                }
                if (g.connect(pu, pd)) {
                    node->drawLine(g.points[pu], g.points[pd], (g.mat[pu][pd] == 10 ? Color4F::RED : (g.mat[pu][pd] == -10 ? Color4F::BLUE : Color4F::WHITE)));
                    if (g.hasTriangle(pu)) {
                        CCLOG("You Lost");
                        redWins = false;
                        auto scene = Finish::createScene();
                        Director::getInstance()->pushScene(scene);
                    }
                    auto machine = g.play();
                    pu = machine.first, pd = machine.second;
                    node->drawLine(g.points[pu], g.points[pd], (g.mat[pu][pd] == 10 ? Color4F::RED : (g.mat[pu][pd] == -10 ? Color4F::BLUE : Color4F::WHITE)));
                    if (g.hasTriangle(pu, -10)) {
                        CCLOG("You Won");
                        redWins = true;
                        auto scene = Finish::createScene();
                        Director::getInstance()->pushScene(scene);
                    }
                }
                score->setString("Score: " + std::to_string(++puntaje));
            }
        }
        selected->runAction(smaller);
        selected = NULL;
    }
    
    return true;
}
