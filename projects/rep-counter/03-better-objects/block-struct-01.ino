struct Block {
  int w, h;
  int x1, y1, x2, y2;
  int tw, th;
  int tx, ty;
  int color;
  int font = 0;
  const GFXfont* gfx;
  BB_SPI_LCD sprite;

  Block(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
    sprite.createVirtual(w, h);
    sprite.fillScreen(color);
  }

  void setFont(int _font) {
    font = _font;
  }

  void setFont(const GFXfont* _gfx) {
    gfx = _gfx;
    font = -1;
  }

  void text(char *text, int _textColor) {

    if (font > -1) {
      sprite.setFont(font);
    } else {
      sprite.setFreeFont(gfx);
    }

    int16_t _x1, _y1;
    uint16_t _tw, _th;
    sprite.getTextBounds(text, 0, 0, &_x1, &_y1, &_tw, &_th);

    int x = (sprite.width() / 2) - (_tw / 2);
    int y = (_y1 == 0) ? (sprite.height() / 2) - (_th / 2) : (sprite.height() / 2) + (_th / 2);

    tw = _tw;
    th = _th;
    tx = x;
    ty = y;

    sprite.setTextColor(_textColor, color);
    sprite.setCursor(x, y);
    sprite.println(text);
  }

  void draw(int x, int y, BB_SPI_LCD *dest) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    dest->drawSprite(x1, y1, &sprite);
  }
};