/* func_8014D820 — shared body (overlay slot 0x80128158, h_exact ce76d008). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2)
{

    extern u8 D_801202A0[];
    extern u8 D_80180EC8[];
    extern u8 D_801152A8[];
    extern s16 D_801152AC;
  /* BLOCK-SCOPE types — see the header note. `Ent` at file scope collides with
     src/shared/engine_types.h:434 and kills the TU's cc1 stage (exit 33). */
  typedef Unkstruct_800B5CB8 Ent;
  int new_var2;
  s16 new_var3;
  V4 out[3];
  V4 pos;
  Desc desc;
  Ent *ent;
  Ent *p;
  s32 dx;
  s32 dz;
  s32 ex;
  s32 ez;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 ang;
  s32 x0;
  s32 y0;
  s32 z0;
  s32 tx;
  s32 tz;
  s32 ty;
  s32 r;
  s32 t;
  s32 u;
  s32 a0v;
  t = a2[0];
  u = a1[0];
  dx = t - u;
a0v = a0;
  new_var3 = (s16) dx;
  t = a2[2];
  u = a1[2];
  dz = t - u;
  if (((s16) (dx | dz)) == 0)
  {
    goto fail;
  }
  desc.x = dx;
  desc.y = a2[1] - a1[1];
  desc.z = a2[2] - a1[2];
  ent = *((Ent **) (a0v + 0x170));
  if (ent->unk0 == 0)
  {
    goto fail;
  }
  if ((ent->unk5C & 0x1000) == 0)
  {
    goto fail;
  }
  if (ent->unk58 == 0)
  {
    goto fail;
  }
  if (func_80135A4C(ent->unk20, ent->unk58, (s32 *) a1, (s32) a2) == 0)
  {
    goto fail;
  }
  ex = ent->unk6 - (*((u16 *) (a0v + 6)));
  ez = ent->unkE - (*((u16 *) (a0v + 0xE)));
  r1 = (s16) ratan2((s16) dz, new_var3);
  r2 = (s16) ratan2((s16) ez, (s16) ex);
  r3 = (s16) func_80012A60(r1, r2);
  if (0x400 <= r3)
  {
    goto fail;
  }
  desc.f20 = 0;
  desc.f1C = 0;
  desc.f18 = 0;
  x0 = ent->unk6;
  pos.x = x0;
  y0 = ent->unkA;
  pos.y = y0;
  z0 = ent->unkE;
  tx = x0 + desc.x;
  pos.z = z0;
  tz = z0 + desc.z;
  desc.x = tx;
  desc.z = tz;
  ty = (y0 + desc.y) + 8;
  desc.y = ty;
  if (currentLocationId != 0x3008)
  {
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->unk0 == 0)
      {
        continue;
      }
      if (p->unk5C == 0)
      {
        continue;
      }
      if (p->unk58 == 0)
      {
        continue;
      }
      func_80135888(p->unk20, p->unk58, (s32) (&pos), (s32) (&desc));
    }

  }
  else
  {
    ang = ratan2(((s16) x0) - ((s16) tx), ((s16) z0) - ((s16) tz)) & 0xFFF;
    func_800139C8(ang, D_80180EC8, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_80180EC8, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_80180EC8, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->unk0 == 0)
      {
        continue;
      }
      if (p->unk5C == 0)
      {
        continue;
      }
      if (p->unk58 == 0)
      {
        continue;
      }
      if (func_8014DCE0((s32) p, (s32) (&pos), (s32) (&out[0])) != 0)
      {
        __builtin_memcpy((void *) ((s32) (&desc)), (void *) ((s32) (&pos)), 8);
      }
    }

  }
  r = func_80133784(0, &pos, (s32) (&desc));
  if ((r == 0) || ((r == 0x2000) && (((*(u16 *) D_801152A8) | ((u16) D_801152AC)) == 0)))
  {
    ent->unk6 = desc.x - desc.f18;
    ent->unkA = desc.y;
    ent->unkE = desc.z - desc.f20;
    desc.x -= pos.x;
    desc.y -= pos.y;
    desc.z -= pos.z;
    *((u16 *) (a0v + 6)) = a1[0] + desc.x;
    new_var2 = desc.y;
    new_var2 = new_var2 + 0x10;
    *((u16 *) (a0v + 0xA)) = a1[1] + new_var2;
    *((u16 *) (a0v + 0xE)) = a1[2] + desc.z;
  }
  else
  {
    *((u16 *) (a0v + 6)) = a1[0];
    *((u16 *) (a0v + 0xA)) = a1[1] + 0x10;
    *((u16 *) (a0v + 0xE)) = a1[2];
  }
  return 1;
  fail:
  *((s32 *) (a0v + 0x170)) = 0;

  return 0;
}
