















void func_80039DEC(a0, a1, a2)
void *a0;
s16 a1;
s16 a2;
{
register u8 *pc __asm__("$2");
register u8 bc __asm__("$3");
register u8 *pd __asm__("$3");
register u8 bd __asm__("$2");
  s32 tmp;
register u8 kind __asm__("$4");
  u8 cnt;
  if (a2 == 0x1E)
  {
    goto L_1E;
  }
  if (a2 < 0x1F)
  {
    if (a2 == 0x14)
    {
      goto L_14;
    }
  }
  else
    if (a2 == 0x28)
  {
    goto L_28;
  }
  goto L_default;
  L_14:
  pc = ((u8 *) a0) + (a1 * 26);

  bc = pc[0x21];
  kind = 0x18;
  goto L_merge;
  L_1E:
  if ((*((u8 *) (((u8 *) a0) + 0x1F6))) == 0)
  {
    *((u8 *) (((u8 *) a0) + 0x1F9)) = 1;
    return;
  }

  cnt = *((u8 *) (((u8 *) a0) + 0x1F5));
  if (((u8) cnt) != 0x7F)
  {
    *((u8 *) (((u8 *) a0) + 0x1F5)) = cnt + 0xFF;
    if (((u8) cnt) == 0)
    {
      return;
    }
  }
 do { ; *((s32 *) a0) = *((s32 *) (((u8 *) a0) + 0xC)); *((u8 *) (((u8 *) a0) + 0x1F7)) = 0xB0; *((u8 *) (((u8 *) a0) + 0x1F7)) = a1 | (*((u8 *) (((u8 *) a0) + 0x1F7))); return; L_28: pc = ((u8 *) a0) + (a1 * 26); bc = pc[0x21]; kind = 0x1A; L_merge: pc[0x1F] = (tmp = a2); pc[0x22] = kind; } while (0);
  pc[0x21] = bc | 3;
  return;
  L_default:
  pd = ((u8 *) a0) + (a1 * 26);

  bd = pd[0x21];
  pd[0x1F] = tmp;
  pd[0x21] = bd | 1;
}