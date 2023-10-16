#include <SDL2/SDL.h>

#define SCREENWIDTH  640
#define SCREENHEIGHT 480

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef size_t   usize;
typedef ssize_t  isize;

typedef struct v2_s  { f32 x, y; } v2;
typedef struct v2i_s { i32 x, y; } v2i;

void drawpixel(u32 *pixels, v2i p, u32 color);
void drawline(u32 *pixels, v2i p0, v2i p1, u32 color);

