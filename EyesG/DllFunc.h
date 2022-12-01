#pragma once

#define _IN
#define _OUT
#define _IN_OUT

typedef void (WINAPI* FNsetColorInversion)();
typedef void (WINAPI* FNsetColorGray)();
typedef void (WINAPI* FNsetColorNormal)();

extern FNsetColorInversion setColorInversion;
extern FNsetColorGray setColorGray;
extern FNsetColorNormal setColorNormal;



