#include "main.hh"
using namespace rl;

#include <map>

typedef unsigned long hash_t;

static Font font;

struct tex_record {
  Texture2D tex;
  int width, height;
};
static std::map<hash_t, tex_record> textures;

static inline hash_t hash(const char *s)
{
  hash_t r = 0;
  for (; *s != '\0'; s++) r = r * 997 + *s;
  return r;
}

static inline void load_tex(const char *name, const char *path)
{
  hash_t h = hash(name);
  if (textures.count(h) > 0) {
    puts("Collision!");
    return;
  }
  Image img = LoadImage(path);
  textures[h] = (tex_record){
    .tex = LoadTextureFromImage(img),
    .width = img.width,
    .height = img.height,
  };
  UnloadImage(img);
}

static inline tex_record tex(const char *name)
{
  auto p = textures.find(hash(name));
  if (p == textures.end()) {
    puts("Unknown texture");
    return (tex_record){};
  }
  return p->second;
}

void painter::init()
{
  font = LoadFont("res/Imprima.ttf");
  load_tex("bellflower_ord", "res/bellflower_ord.png");
  load_tex("board_bg", "res/board_bg.png");
}

static inline unsigned char to_u8(float x) { return (unsigned char)(255.0f * x); }

void painter::text(
  const char *s, int size,
  vec2 pos, vec2 anchor, float alpha)
{
  Vector2 dims = MeasureTextEx(font, s, size, 0);
  DrawTextEx(
    font, s,
    (Vector2){pos.x - dims.x * anchor.x, pos.y - dims.y * anchor.y},
    size, 0,
    (Color){255, 255, 255, to_u8(alpha)}
  );
}

void painter::image(
  const char *name,
  vec2 pos, vec2 dims,
  tint4 tint)
{
  auto rec = tex(name);
  image(name, pos, dims,
    vec2(0, 0), vec2(rec.width, rec.height),
    vec2(0, 0), 0,
    tint);
}

void painter::image(
  const char *name,
  vec2 pos, vec2 dims,
  vec2 src_pos, vec2 src_dims,
  vec2 anchor, float rot,
  tint4 tint)
{
  auto rec = tex(name);
  DrawTexturePro(rec.tex,
    (Rectangle){src_pos.x, src_pos.y, src_dims.x, src_dims.y},
    (Rectangle){pos.x, pos.y, dims.x, dims.y},
    (Vector2){anchor.x, anchor.y},
    rot / M_PI * 180,
    (Color){
      to_u8(tint.r), to_u8(tint.g),
      to_u8(tint.b), to_u8(tint.a)
    }
  );
}