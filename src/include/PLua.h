// PLua.h
#ifndef LUA_MAINTAINER_H
#define LUA_MAINTAINER_H

#include "src/lua.hpp"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GlobalVars.h"
#include "ObjectManager.h"

class PLua {
private:
    lua_State* L;
    GlobalVars* global;
    ObjectManager* objectManager;

    static int lua_createFigure(lua_State* L) {

        PLua* self = static_cast<PLua*>(lua_touserdata(L, lua_upvalueindex(1)));


        if (lua_gettop(L) != 10) {
            return luaL_error(L, "Need 10 args: name, pos, scale, angle, type, textures");
        }


        const char* name = luaL_checkstring(L, 1);

        glm::vec3 pos = {
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3)),
                static_cast<float>(luaL_checknumber(L, 4))
        };

        glm::vec3 scale = {
                static_cast<float>(luaL_checknumber(L, 5)),
                static_cast<float>(luaL_checknumber(L, 6)),
                static_cast<float>(luaL_checknumber(L, 7)) // Ошибка! Должно быть 5,6,7?
        };


        float angle = static_cast<float>(luaL_checknumber(L, 8));
        const char* type = luaL_checkstring(L, 9);

        std::vector<std::string> textures;
        luaL_checktype(L, 10, LUA_TTABLE);
        for (int i = 1; i <= lua_rawlen(L, 10); i++) {
            lua_rawgeti(L, 10, i);
            textures.push_back(luaL_checkstring(L, -1));
            lua_pop(L, 1);
        }

        self->objectManager->createFigure(
                name,
                self->global->getCamera(),
                pos,
                scale,
                angle,
                self->global->getObjectShader(),
                type,
                textures
        );

        return 0;
    }

public:
    PLua(GlobalVars& g, ObjectManager& m) : global(&g), objectManager(&m) {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    bool loadScript(const std::string& filename) {
        if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
            std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
            return false;
        }
        return true;
    }

    void registerFunctions() {
        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_createFigure, 1);
        lua_setglobal(L, "create_figure");
    }

    ~PLua() {
        lua_close(L);
    }
};

#endif