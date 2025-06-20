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


        if (lua_gettop(L) != 12) {
            return luaL_error(L, "Need 12 args: name, pos, scale, angle, type, textures");
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


        vec3 angle = {
                static_cast<float>(luaL_checknumber(L, 8)),
                static_cast<float>(luaL_checknumber(L, 9)),
                static_cast<float>(luaL_checknumber(L, 10))
        };
        string type = luaL_checkstring(L, 11);

        std::vector<std::string> textures;
        luaL_checktype(L, 12, LUA_TTABLE);
        for (int i = 1; i <= lua_rawlen(L, 12); i++) {
            lua_rawgeti(L, 12, i);
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
        if (self->objectManager->selectObjectByName(name)) {
            self->objectManager->getActiveObject();
        }
        return 0;
    }

    static int lua_createLight(lua_State *L) {

        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));


        if (lua_gettop(L) != 11) {
            return luaL_error(L, "Need 11 args: name, pos, scale, angle, type");
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


        vec3 angle = {
                static_cast<float>(luaL_checknumber(L, 8)),
                static_cast<float>(luaL_checknumber(L, 9)),
                static_cast<float>(luaL_checknumber(L, 10))
        };
        string type = luaL_checkstring(L, 11);

        self->objectManager->createLight(name,
                                         self->global->getCamera(),
                                         pos,
                                         scale,
                                         angle,
                                         self->global->getObjectShader(),
                                         self->global->getLightShader(),
                                         type);
        if (self->objectManager->selectObjectByName(name)) {
            self->objectManager->getActiveObject();
        }
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

    static int lua_moveTo(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 pos = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->moveTo(pos);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);

            glm::vec3 pos = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->moveTo(pos);
            return 0;
        }
        return 0;
    }

    static int lua_moveOn(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 pos = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->moveOn(pos);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);

            glm::vec3 pos = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->moveOn(pos);
            return 0;
        }
        return 0;
    }

    static int lua_scaleTo(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 scale = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->scaleTo(scale);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);

            glm::vec3 scale = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->scaleTo(scale);
            return 0;
        }
        return 0;
    }

    static int lua_scaleOn(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 scale = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->scaleOn(scale);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);

            glm::vec3 scale = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->scaleOn(scale);
            return 0;
        }
        return 0;
    }

    static int lua_rotateTo(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 angle = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->rotateTo(angle);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);
            glm::vec3 angle = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->rotateTo(angle);
            return 0;
        }
        return 0;
    }

    static int lua_rotateOn(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 angle = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->rotateOn(angle);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);
            glm::vec3 angle = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->rotateOn(angle);
            return 0;
        }
        return 0;
    }

    static int lua_changeColorBG(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {
            glm::vec3 color = {
                    static_cast<float>(luaL_checknumber(L, 1)),
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3))
            };

            self->objectManager->changeBgColor(color);
        }
        return 0;
    }

    static int lua_changeColor(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) == 3) {

            if (self->objectManager->getActiveObject()) {
                glm::vec3 color = {
                        static_cast<float>(luaL_checknumber(L, 1)),
                        static_cast<float>(luaL_checknumber(L, 2)),
                        static_cast<float>(luaL_checknumber(L, 3))
                };

                self->objectManager->changeColor(color);
                return 0;
            }
            return luaL_error(L, "Need 1 args: name");
        }
        if (lua_gettop(L) == 4) {
            const char *name = luaL_checkstring(L, 1);

            glm::vec3 color = {
                    static_cast<float>(luaL_checknumber(L, 2)),
                    static_cast<float>(luaL_checknumber(L, 3)),
                    static_cast<float>(luaL_checknumber(L, 4))
            };

            self->objectManager->selectObjectByName(name);
            self->objectManager->changeColor(color);
            return 0;
        }
        return 0;
    }

    static int lua_setDirection(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 3) {
            return luaL_error(L, "Need 3 args: x,y,z");
        }
        glm::vec3 dir = {
                static_cast<float>(luaL_checknumber(L, 1)),
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3))
        };
        self->objectManager->setDirection(dir);

        return 0;
    }

    static int lua_setAmbient(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 3) {
            return luaL_error(L, "Need 3 args: x,y,z");
        }
        glm::vec3 ambient = {
                static_cast<float>(luaL_checknumber(L, 1)),
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3))
        };
        self->objectManager->setLightAmbient(ambient);

        return 0;
    }

    static int lua_setDiffuse(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 3) {
            return luaL_error(L, "Need 3 args: x,y,z");
        }
        glm::vec3 diffuse = {
                static_cast<float>(luaL_checknumber(L, 1)),
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3))
        };
        self->objectManager->setLightDiffuse(diffuse);

        return 0;
    }

    static int lua_setSpecular(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 3) {
            return luaL_error(L, "Need 3 args: x,y,z");
        }
        glm::vec3 specular = {
                static_cast<float>(luaL_checknumber(L, 1)),
                static_cast<float>(luaL_checknumber(L, 2)),
                static_cast<float>(luaL_checknumber(L, 3))
        };
        self->objectManager->setLightSpecular(specular);

        return 0;
    }

    static int lua_setSpotLightRadius(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 1) {
            return luaL_error(L, "Need 1 args: radius");
        }
        float cut = static_cast<float>(luaL_checknumber(L, 1));
        self->objectManager->setSpotLightCutOff(cut);
        return 0;
    }

    static int lua_setSpotLightOuterRadius(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));
        if (lua_gettop(L) != 1) {
            return luaL_error(L, "Need 1 args: radius");
        }
        float cut = static_cast<float>(luaL_checknumber(L, 1));
        self->objectManager->setSpotLightOuterCutOff(cut);
        return 0;
    }

    static int lua_addTexture(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) != 3) {
            return luaL_error(L, "Need 3 args: objectName, texturePath, textureType");
        }

        const char *objectName = luaL_checkstring(L, 1);
        const char *texturePath = luaL_checkstring(L, 2);
        const char *textureType = luaL_checkstring(L, 3);

        self->objectManager->addTextureToObject(objectName, texturePath, textureType);
        return 0;
    }

    static int lua_removeAllTextures(lua_State *L) {
        PLua *self = static_cast<PLua *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (lua_gettop(L) != 1) {
            return luaL_error(L, "Need 1 arg: objectName");
        }

        const char *objectName = luaL_checkstring(L, 1);

        bool success = self->objectManager->removeAllTexturesFromObject(objectName);
        lua_pushboolean(L, success);
        return 1;
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
        lua_setglobal(L, "figure");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_createLight, 1);
        lua_setglobal(L, "light");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_pickActiveObject, 1);
        lua_setglobal(L, "pick");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_moveTo, 1);
        lua_setglobal(L, "move");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_scaleTo, 1);
        lua_setglobal(L, "scale");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_rotateTo, 1);
        lua_setglobal(L, "rotate");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_moveOn, 1);
        lua_setglobal(L, "moveOn");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_scaleOn, 1);
        lua_setglobal(L, "scaleOn");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_rotateOn, 1);
        lua_setglobal(L, "rotateOn");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_changeColor, 1);
        lua_setglobal(L, "color");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_changeColorBG, 1);
        lua_setglobal(L, "color_bg");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setDirection, 1);
        lua_setglobal(L, "direction");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setAmbient, 1);
        lua_setglobal(L, "ambient");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setDiffuse, 1);
        lua_setglobal(L, "diffuse");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setSpecular, 1);
        lua_setglobal(L, "specular");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setSpotLightRadius, 1);
        lua_setglobal(L, "radius");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_setSpotLightOuterRadius, 1);
        lua_setglobal(L, "radius_outer");

        lua_pushlightuserdata(L, this);
        lua_pushcclosure(L, &PLua::lua_addTexture, 1);
        lua_setglobal(L, "add_texture");

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