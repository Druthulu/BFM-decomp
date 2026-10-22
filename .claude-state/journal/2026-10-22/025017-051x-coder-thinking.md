---
ts: 2026-10-22T08:50:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RiHKOOtCynIyEDWx4dA3
---
C0409 is about a different thing (reload-remat constant) but confirms: "Reload then ... REMATERIALIZES ... picking the register by `reload1.c order_regs_for_reload` preference rather than local-alloc's ascending scan."

So the reload's reg choice is `reload1.c order_regs_for_reload`. Let me recall GCC 2.7's reload1.c:

```c
/* Return the number of the first register in the class that is not ... */
static int
order_regs_for_reload (r, j)
{
  int i;
  int result = -1;
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      int r = regclass->regs[i];
      ...
    }
}
```

Hmm, actually in GCC 2.7's reload1.c there IS a function `order_regs_for_reload`:

```c
/* Return the reg to use for a reload... */
static int
order_regs_for_reload (r, j)
{
  int i;
  int result = -1;
  int nr = 0;
  enum reg_class class = (enum reg_class) reload_inp[j].in_reg->reg_class;

  /* Avoid clobbering the register in the insn... */
  ...
  /* First, find the register which is preferred. */
  ...
}
```
I recall it sorts the class's registers by "how many times they're used in the function" (i.e., prefer the least used) — `reg_use_count`? Hmm. Actually! I remember: GCC's reload1.c has:

```c
/* Return the number of times the register is used... */
static int
reg_use_count (r) { ... }
```
Hmm, there might be a preference for the register that is used LEAST in the function, to minimize the number of times the value must be preserved.

In our function: a0 is used as a call arg (twice) and v1 is used for the const and the switch value (more times?). Hmm, if reload prefers the LEAST-used reg, and a0 is used less than v1, that would explain a0!

Interesting. So to shift the reload to v1, I'd need v1 to be used less than a0 in the function. Currently v1 is used by: the const 0x9000 (twice: li + slt), the slt result (twice), the switch value (lhu). a0 is used by: the call arg copies (twice), the ptr load, the q load (in the target: v1).

Hmm, but the *count* is per hard reg in the function. Hmm, this is at the reload stage, before allocation, so the counts are of hard regs in the RTL at that point.

Hmm! This is a promising lever: reduce the number of uses of v1 in the function, or increase the uses of a0.

How to reduce v1's uses? The const 0x9000 (li v1,0x9000; slt v1,v1,v0) is in v1 in the TARGET, so I can't change that... but wait: those uses are what they are.

Hmm, but if the reload prefers the least-used reg and a0 is used less... but in the target a0 is used MORE (the call args) hmm.

Let me check GCC 2.7's reload1.c order_regs_for_reload:

```c
/* Return the number of the first register in the class that is not
   occupied ... */
static int
order_regs_for_reload (r, j)
{
  int i;
  int result = -1;
  ...
  /* We prefer a register that is not used in the insn... */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      ...
    }
}
```

I really don't remember. Let me find the actual gcc 2.7.2 source. Maybe I can download it? No network probably. Hmm.

Wait — maybe the project has a copy of gcc source in docs or research. Let me grep the repo for "order_regs_for_reload".
