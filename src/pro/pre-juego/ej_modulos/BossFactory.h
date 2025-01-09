#pragma once
#ifndef FACTORYBOSS_H
#define FACTORYBOSS_H

#include <memory>
#include "Boss.h"

class BossFactory {
public:
    static std::unique_ptr<Boss> createBoss(const std::string& texture, BossType type);
};
#endif