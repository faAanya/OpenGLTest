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
    lua_State *L;
    GlobalVars *global;
    ObjectManager *objectManager;

    static int lua_createFigure(lua_State *L) {

        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));


        if (lua_gettop(L) != 10) {
            return luaL_error(L, "Need 10 args: name, pos, scale, angle, type, textures");
        }


        const char *name = luaL_checkstring(L, 1);

        glm::vec3 pos = {
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3)),
                static_cast<float>(luaL_checknumber(L, 4))
        };

        glm::vec3 scale = {
                static_cast<float>(luaL_checknumber(L, 5)),
                static_cast<float>(luaL_checknumber(L, 6)),
                static_cast<float>(luaL_checknumber(L, 7))
        };


        float angle = static_cast<float>(luaL_checknumber(L, 8));
        const char *type = luaL_checkstring(L, 9);

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

    static int lua_createLight(lua_State *L) {

        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));


        if (lua_gettop(L) != 9) {
            return luaL_error(L, "Need 9 args: name, pos, scale, angle, type");
        }

        const char *name = luaL_checkstring(L, 1);

        glm::vec3 pos = {
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3)),
                static_cast<float>(luaL_checknumber(L, 4))
        };

        glm::vec3 scale = {
                static_cast<float>(luaL_checknumber(L, 5)),
                static_cast<float>(luaL_checknumber(L, 6)),
                static_cast<float>(luaL_checknumber(L, 7))
        };


        float angle = static_cast<float>(luaL_checknumber(L, 8));
        const char *type = luaL_checkstring(L, 9);

        self->objectManager->createLight(name,
                                         self->global->getCamera(),
                                         pos,
                                         scale,
                                         angle,
                                         self->global->getObjectShader(),
                                         self->global->getLightShader(),
                                         type);

        return 0;
    }

    static int lua_pickActiveObject(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 1) {
            return luaL_error(L, "Need 1 args: name");
        }

        const char *name = luaL_checkstring(L, 1);

        if (self->objectManager->selectObjectByName(name)) {
            self->objectManager->getActiveObject();
        }

        return 0;
    }

    static int lua_deleteActiveObject(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        self->objectManager->deleteObj();

        return 0;
    }

    static int lua_deleteAllObject(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        self->objectManager->deleteAllObjects();

        return 0;
    }

public:
    PLua(GlobalVars &g, ObjectManager &m) : global(&g), objectManager(&m) {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    void loadScriptFromFile(const std::string &filename) {
        if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
            std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
            return;
        }
    }
    void loadScriptFromTextBox(const std::string &text) {
        if (luaL_dostring(L, text.c_str()) != LUA_OK) {
            std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
            return;
        }
    }

    void registerFunctions() {
        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_createFigure, 1);
        lua_setglobal(L, "create_figure");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_createLight, 1);
        lua_setglobal(L, "create_light");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_pickActiveObject, 1);
        lua_setglobal(L, "pick_object");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_deleteActiveObject, 1);
        lua_setglobal(L, "delete_object");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_deleteAllObject, 1);
        lua_setglobal(L, "delete_all");
    }

    ~PLua() {
        lua_close(L);
    }
};

#endif