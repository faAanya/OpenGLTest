#include "include/lua-maintainer.h"
#include "src/lua.hpp"

Lua::Lua() {
    L = luaL_newstate();
}