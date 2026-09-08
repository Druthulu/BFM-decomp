/* src/shared/engine_prelude.h — Phase 35: what every overlay/module TU needs from the shared tree BEFORE its first shared
 * body: the shared engine types and the ENGINE_SHB barrier. It replaces the engine_core.h include (the bodies now live as
 * per-function headers under src/shared/<space>/, included at each member's site — sotn's shape). */
#ifndef SHARED_ENGINE_PRELUDE_H
#define SHARED_ENGINE_PRELUDE_H
#include "common.h"
#include "engine_types.h"
#ifndef ENGINE_SHB
#define ENGINE_SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#endif
#endif
