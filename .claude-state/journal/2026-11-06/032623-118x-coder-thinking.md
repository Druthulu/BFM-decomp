---
ts: 2026-11-06T10:26:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oeq8SNNoapSkQcX0a2Xq
---
Target item 4:
```
dd6c: move a0,v0       # fcopy = flags (flags=v0, fcopy=a0)
dd70: andi v0,a0,0x4000
dd74: beqz v0,...
dd78: move v1,a0        # delay slot: v1 = a0 (fcopy copy for the later &0x8000?)
dd7c: j ...
dd80: li v0,2
dd84: andi v0,a0,0x2000
dd88: beqz v0,...
dd8c: andi v1,v1,0x8000   # delay slot
dd90: j ...
dd94: li v0,1
dd98: bnez v1,...
dd9c: li v0,4
dda0: move v0,s1
```

So fcopy is in a0, flags in v0. And there's a `move v1,a0` (v1 = fcopy) then `andi v1,v1,0x8000`.

Hmm, the target has fcopy in a0 AND a copy in v1. So the pin $3 (v1) is NOT what the target uses for fcopy!

Wait, the pin is `register u32 fcopy __asm__("$3")`. With the pin, fcopy is v1. But the target has fcopy in a0. So how does the pin make it match?

Hmm, maybe with the pin, the code is different: `fcopy = flags` becomes `move v1,v0`? But the target has `move a0,v0`. 

Wait, maybe the target's `move a0,v0` is `fcopy = flags` where fcopy is a0... but the pin says $3.

Hold on. Let me reconsider: maybe the target's `move a0,v0` is NOT fcopy=flags. Let me re-read the source:
```
flags = func_8014FA04(arg0);
fcopy = flags;
if (flags & 0x4000) ...
```
The call returns in v0. `flags = call` → flags=v0. `fcopy = flags` → copy v0 to fcopy. If fcopy is pinned to $3 (v1), the copy would be `move v1,v0`. But the target has `move a0,v0`.

So the target's fcopy is a0, and the pin to v1 is WRONG? But the pin is "NEEDED" per the explain...

Hmm, wait. Maybe I misidentified. Let me reconsider: with the pin (fcopy=v1), the code might be:
```
move v1,v0        # fcopy = flags
andi v0,v1,0x4000 # flags & 0x4000 (flags still v0)
...
```
That's MINE (lever-free? no, mine in explain is lever-free).

Hmm, the explain's "mine" is the lever-free body. Lever-free, fcopy is a pseudo. It got v1 (mine). The target has a0. So the lever-free gives v1, target a0. The pin forces v1 too. So the pin wouldn't fix it...

Unless the explain's "mine" is the LEVER-FREE body but with some other difference. Wait, let me re-read: "site pin $3 line 10 NEEDED" — the pin is needed. So with the pin, score 0. Let me verify by scoring the orig (with pin): score 0 (it's the tree's body). Yes, the orig scores 0.

So with the pin, fcopy=v1 and the code matches the target. But the target asm shows `move a0,v0` and `andi v0,a0,0x4000`. That's fcopy in a0!

Contradiction. Unless... the target's `move a0,v0` is something else and `andi v0,a0,0x4000` uses a0 for a different reason.

OH WAIT. Maybe in the target, `fcopy` is in a0 because the pin `$3` applies to a DIFFERENT variable in the original, or the original source had `fcopy` used differently. Hmm.

Let me look at the explain diff again:
```
replace mine[22:24] target[22:24]
      22  move	v1,v0                         | move	a0,v0
      23  andi	v0,v1,0x4000                  | andi	v0,a0,0x4000
```
So mine (lever-free) has `move v1,v0` (fcopy=v1), target has `move a0,v0` (fcopy=a0).

And the pin is $3 (v1). So the pin forces fcopy=v1, which is what MINE (lever-free) already has! So why is the pin NEEDED?

Hmm, that doesn't make sense. Unless the lever-free body differs elsewhere (the extra `move v0,v1`).

Let me look at the full residual: mine 43 ins vs target 42. The extra instruction is `move v0,v1` at mine[36]. So lever-free has an extra move.

Maybe the pin's effect is on the RETURN value, not fcopy's own register. Let me think: the function returns `ret`. `ret` is in v0 (return reg). The pin on fcopy=v1 might affect how `ret` is computed.

Hmm. Let me look at the target's end:
```
dd98: bnez v1,...
dd9c: li v0,4
dda0: move v0,s1
```
`ret` is in v0. `v1` holds the &0x8000 result.

Lever-free mine:
```
move v1,v0      # fcopy=v1
andi v0,v1,0x4000
...
move a0,v1      # ???
li v1,2
andi v0,v1,0x2000
...
andi v0,a0,0x8000
li v1,1
bnez v0,...
li v1,4
move v1,s1
move v0,v1
```
So mine has ret in v1 and then `move v0,v1` to return. Target has ret directly in v0 (li v0,2 etc.).

So the pin forces fcopy=v1, which frees... hmm, actually the pin forces fcopy into v1, which changes the allocation of `ret`? With the pin, `ret` would be in v0 directly (no move). Lever-free, `ret` is in v1 and copied to v0.

So the pin's role: by pinning fcopy to v1, it frees v0 for `ret`. Lever-free, fcopy takes v1 anyway (mine), but `ret` still ends up in v1 and gets copied to v0. Hmm, why?

Wait, maybe the pin changes the RTL: `fcopy` as a hard reg means `fcopy = flags` is a hard-reg set, and the later `fcopy & 0x8000` uses v1. Without the pin, fcopy is a pseudo that gets v1 in local-alloc, but the *qty ordering* differs, so `ret` gets v1 and is copied to v0.

So the pin's effect is subtle: it makes fcopy a hard reg so it doesn't compete with ret in local-alloc.

Hmm. So lever-free, fcopy and ret compete; ret wins v1 (or fcopy?), and ret ends in v1 with a copy to v0.

Let me check: mine[30] `andi v0,a0,0x8000` — hmm, a0? Where did a0 come from? mine[25] `move a0,v1` — so there's a copy of fcopy to a0. So mine has fcopy in v1, a copy to a0, and ret in v1.

This is messy. Let me just try lever-free variants and see.

First, let me create the nopin body and score it.

Item 4 nopin:
```
s32 func_801535F4(void *arg0) {
    s32 var_s1;
    u32 flags;
    u32 fcopy;
    s32 ret;
    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    return ret;
}
```

Let me write and score it.

Note: the extern declarations are outside the def. The body span starts at `s32 func_801535F4(void *arg0) {`.

Let me write it.
