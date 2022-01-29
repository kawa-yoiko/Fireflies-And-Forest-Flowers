#include "main.hh"
#include "utils.hh"

using button = button_group::button;

static inline bool in_button(float x, float y, const button &btn)
{
  return (x >= btn.pos.x && x < btn.pos.x + btn.size.x &&
          y >= btn.pos.y && y < btn.pos.y + btn.size.y);
}

bool button_group::pton(float x, float y)
{
  for (auto &btn : buttons) {
    if (in_button(x, y, btn)) {
      sel_button = &btn;
      cur_in = true;
      return true;
    }
  }
  sel_button = nullptr;
  return false;
}

bool button_group::ptmove(float x, float y)
{
  if (sel_button == nullptr) return false;
  cur_in = in_button(x, y, *sel_button);
  return true;
}

bool button_group::ptoff(float x, float y)
{
  if (sel_button == nullptr) return false;
  if (cur_in) sel_button->fn();
  sel_button = nullptr;
  return true;
}

void button_group::draw()
{
  for (const auto &btn : buttons) {
    tint4 tint = tint4(1, 1, 1, 1);
    if (&btn == sel_button && cur_in)
      tint = tint4(0.8, 0.8, 0.8, 1);
    painter::image(
      btn.image, btn.pos, btn.size,
      tint);
  }
}
