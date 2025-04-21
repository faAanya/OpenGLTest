#include "include/PLua.h"
#include "src/lua.hpp"

Lua::Lua() {
    L = luaL_newstate();
}