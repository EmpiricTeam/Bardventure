#include "factoryNpc.h"

std::unique_ptr<Npc> NPCFactory::createNPC(const std::string& texture, NPCType type, int x, int y) {
    return std::make_unique<Npc>(texture, type,x,y);
}
