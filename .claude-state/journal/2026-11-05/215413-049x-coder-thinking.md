---
ts: 2026-11-06T04:54:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1ORZeBJk2vNzB0p3pf00
---
Target tail:
```
224c lui v1, D_80127524
2250 lw v1,0(v1)      ; reload *p for the store target (D_80127524)
2254 li v0,1
2258 sh v0,26(v1)     ; *(s16*)(D_80127524+0x1A) = 1
225c lw a0,0(a0)      ; reload *p for call arg
2260 jal func_80138C30
2264 nop
```
Mine:
```
224c lui v1, D_80127524
2250 lw v1,0(v1)
2254 li v0,1
2258 jal func_80138C30     ; call BEFORE the store!
225c sh v0,26(v1)          ; store in delay slot
```
So mine puts the call before the store and the store in the delay slot; target does the store, then reloads *p into a0, then calls. Also mine doesn't reload *p for the arg? It seems mine's call arg is... at 2258 jal; the arg a0 was set earlier? In mine, a0 = D_80127528 value at 2238, and `sw a0,0(v1)` stores it. Then `lw v1,0(D_80127524)` reload, li v0,1, jal. But a0 still holds the old value (D_80127528 value) — that's wrong! Wait, the call is `func_80138C30(*p)` where *p = D_80127524 value which was set to v0 = D_80127528 value (stored). So a0 = that value; the call arg a0 = value. It's the same value, so gcc reused a0. Target instead reloads from memory (lw a0,0(a0)).

So the barrier forces the reload: without it, cse knows *p == v0 and reuses v0/a0 for the call arg. That's the classic cse-copy-merge / cse equivalence: `*p = v0` then `*p` loaded for the call — cse replaces the load with v0 (register). The barrier (memory clobber) prevents cse from forwarding the stored value into the load.

So we need a real-C construct that makes cse not forward the store into the reload. Moves list: "cse-store-forward — cse1 forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it (W06)". And "launder | func_8018C2D8 | MATCH — reuse m for next ptr ... reassignment kills the cse sym class". Also "cse-copy-merge".

How to prevent cse forwarding? Classic: make the stored value's register die / reassign the variable. In the source, the pattern is:
```
v0 = D_80127528;
D_80127528 = 0;
*p = v0;
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    <barrier>
    func_80138C30(*p);
}
```
The value v0 is stored to *p and then *p is reloaded for the call. cse replaces the reload with v0. Target reloads from memory.

Real-C moves to break cse: reassign v0 after the store? That changes semantics? v0 is used in the `if (v0 != 0)` — the test happens before. After the store, v0 is not used except for the call arg via *p. If we reassign v0 to something, cse would... but that emits an insn unless dead. E.g., `v0 = v0;`? dead. 

The moves list: "launder | func_8018C2D8 | MATCH — reuse m for next ptr (m = s1+0xD0; dv = m) and m1 for col: reassignment kills the cse sym class".

Here the store `*p = v0` — cse records that the memory location *p holds the value in v0 (a "store forward"). Then the load `*p` is replaced by v0. To break it, we can write the store value through a *different expression* whose register isn't reused, e.g., store `D_80127528` value directly: `*p = D_80127528;`? But D_80127528 was already set to 0. Source: `v0 = D_80127528; D_80127528 = 0; *p = v0;` — could write `*p = v0` where v0 is a temp; cse records the store value pseudo v0. If instead we store a *different pseudo* holding the same value, cse's record is that pseudo. Then the reload *p would be replaced by that pseudo, still a register.

Alternatively, make the load of *p not recognized as the same memory location: e.g., access via a different pointer type or pointer variable. cse uses the memory rtx; if we load `*(s32 *)p` vs stored via `*p` — same. If we use a different pointer variable q = p, the address is the same after cse's address canonicalization? Probably cse canonicalizes.

Moves: "launder | func_80131CF4 ... plain while..." not relevant.

Look at W06 cse-store-forward wall and G18x. The wall tag says "only a barrier/volatile stops it". But other moves cracked similar barriers. Let's think of the cse source: cse.c in gcc 2.7.2, `cse_insn` handles stores: it invalidates memory equivalences, and for a store it records `(mem ...)` -> value in the table (store forwarding). Later a load of the same mem gets the value. To prevent, we can make the store and the load use addresses that cse can't prove equal. For instance, store via `*(s32 *)(D_80127524)` and load via a local pointer p where p was loaded from D_80127524? Actually the code:

```
p = &D_80127524;
if (*p == s0) {
    v0 = D_80127528;
    D_80127528 = 0;
    *p = v0;
    if (v0 != 0) {
        *(s16 *)(D_80127524 + 0x1A) = 1;
        func_80138C30(*p);
    }
}
```

The call arg is `*p` where p = &D_80127524. The store `*p = v0` writes D_80127524. Target's call arg is a reload of D_80127524 (lw a0,0(a0) where a0=&D_80127524 — note target keeps a0 = &D_80127524 through the block). So target: a0 holds &D_80127524, `lw a0,0(a0)`.

In target, the store `*p = v0` uses a0 as base and the reload uses a0 too. In mine, v1 holds &D_80127524 and the store `sw a0,0(v1)`, and the reload got cse'd away (a0 = value).

Idea: write the call arg as `D_80127524` directly (not via p): `func_80138C30(D_80127524);` — that's a different expression than `*p`, but same memory location; cse would still forward (it tracks mem by address). Actually cse's store-forwarding: when it sees a store to (mem X), it puts (mem X) -> value in the hash table, but it only does this if... let me check cse.c. In 2.7.2, cse_insn for a store: "if (dest is a MEM) ... invalidate memory" and then "record the store as setting the memory to the source"? Let me grep.

Actually the mechanism could be different: the reload `*p` might not be forwarded by cse but by *combine* or by the "store motion"? The wall tag cse-store-forward says cse1 forwards. Let me read cse.c around stores.
