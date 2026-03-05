//
// Created by oto_9 on 06.03.2026.
//

#pragma once

class GameObject {
public:
    virtual void init() {};
    virtual void onDraw() {};
    virtual void destroy() {};
};