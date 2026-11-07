---
ts: 2026-11-06T16:44:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V7gUBs0JkH0TSTVzluqs
---
Without the pin, `v0` gets `$v1` (register v1) and other registers shift (a1/a0 swap). Score 37.

The pin forces `v0` to $2. In the target, v0 is used as the temp in many places. Real-C ways to get $2:
- Make the value be a call's return in $2? 
- The `v0` local is a temp used for loads and arithmetic. To get $2 naturally, maybe use the parameter differently or restructure.

Wait — in the target, `v0` is used as the temp for `lh v0,112(s0)` etc. $v0 is caller-saved and typically the first choice for short-lived temps. Why does the unpinned version give $v1 instead of $v0? Because some other pseudo takes $v0 first. The pin $2 reserves... Let me look at what else uses $v0 in the unpinned body: `a0r`? Let me see the full diff. The diff shows `a1` and `a0` swapped in one region, and `v1` replacing `v0`.

The target: `v0` = the temp, `a1` = the pointer `p` (48(a1)), `a0` = the D_8019C7CC value.

In mine (no pin): `v1` = temp, `a2` = pointer? `sh a1,48(a2)` — hmm.

So the register assignment shifted: the temp got v1, the pointer got a2/a1, etc.

Real-C moves: 
- The local `v0` is reused for several loads. Maybe rename/split so local-alloc gives it $v0.
- The parameter `s0 = (s32)arg0` copy: `s32 s0 = (s32)arg0;` — maybe `arg0` should be used directly (C0241: the parameter itself is a regalloc dial).
- The `a1 = CAST_SIGN(u32, s0, 0x20);` line — a1 is a separate local (the pointer p? no). Let me re-read the source:

```c
void func_8017F200(void *arg0) {
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern void func_8017F348(s32 a0);
    extern s16 D_8019C7D4[];
    extern u16 D_8019C7CC[];
    extern u16 D_8019C7DC[];

    s32 s0 = (s32)arg0;
    s32 a1;
    register s32 v0 __asm__("$2");
    s32 v1;
    s32 at;
    s32 a0r;
    s32 pad[4];

    a1 = CAST_SIGN(u32, s0, 0x20);

    v0 = ((Unkstruct_800B5CB8 *)s0)->unk70;
    v0 = v0 * 2;
    at = (s32)D_8019C7D4 + v0;
    v0 = *(u16 *)at;
    v1 = CAST_WIDTH(u16, a1, 0x30);
    v1 = v1 + v0;
    CAST_WIDTH(u16, a1, 0x30) = v1;
    ...
```

So `a1` is the pointer `s0+0x20` (the object), `v0` the temp, `v1` the u16 value, `at` the address, `a0r` the bound value.

Target registers: s0=$16 (s0), a1=$5 (a1), v0=$2 (v0), v1=$3 (v1), at=$1 (at), a0r=$4 (a0).

Unpinned: the allocator assigned different regs. Which one moved first? The diff shows mine's `lh v1,0(at)` vs target `lh v0,0(at)` — mine's v0 temp → v1; mine's v1 value → a0; mine's a0r → a1? Let me get the full register mapping. The diff header said "REG-caller" but the pair summary wasn't shown in tail. Let me get the first lines of dt output.

Actually, the key: the pin makes v0=$2. Without it, v0→$3 (v1). Why? Because `v1` (the other temp) took $2 first? In target, v1=$3. In mine, v0=$3 and v1=$4 (a0)? Hmm.

local-alloc allocates per basic block by qty priority (refs/live length). To make v0 get $2, we could adjust the ref counts: e.g., merge v0 and v1 into one variable? Or split.

C0505: "One value per temp: a local that dies in several places is refused by local-alloc and goes global — substitute in place, split, or declare per block". "two locals the tree pins to one register are one variable".

Let me look at the actual unpinned register assignment. Let me run dt with the pair summary (first line).
