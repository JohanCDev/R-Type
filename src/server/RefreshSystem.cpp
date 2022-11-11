
#include "../ECS/World.hpp"
#include "server.hpp"

int refresh_system(World &world, NetworkServer &server)
{
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &ids = world.getRegistry().get_components<EntityIDComponent>();
    Message<GameMessage> msg;

    std::size_t index = 0;
    for (auto& pos : positions) {
        if (pos && pos.has_value()) {
            auto &id = ids[index];
            if (!(id && id.has_value()))
                continue;
            msg << pos;
            msg << id;
            server.SendToAll(msg);
        }
    }
    return 0;
}
