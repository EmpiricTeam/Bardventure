#pragma once
#ifndef FACTORYNPC_H
#define FACTORYNPC_H
#include "npc.h"
#include <memory>

class NPCFactory {
public:
    static std::unique_ptr<Npc> createNPC(const std::string& texture, NPCType type, int x, int y);
};
#endif
