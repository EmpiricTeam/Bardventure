#include "BossFactory.h"

std::unique_ptr<Boss> BossFactory::createBoss(const std::string& texture, BossType type) {
    return std::make_unique<Boss>(texture, type);
}