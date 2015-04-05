#include "ScriptHandlerInternal.h"

lua_State* ScriptHandlerInternal::ls;
std::string ScriptHandlerInternal::scriptPath;

AssetHandler* ScriptHandlerInternal::assetHandler;
EntityHandler* ScriptHandlerInternal::entityHandler;