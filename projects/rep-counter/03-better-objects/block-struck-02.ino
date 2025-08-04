struct Block {
  //
  // All this is mostly the same as the Button object I had
  int w, h;
  int x1, y1, x2, y2;
  int tw, th;
  int tx, ty;
  int color, font;
  const GFXfont* gfx;
  BB_SPI_LCD sprite;

  Block(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
    //
    // These are two sentinal values I'm initializing here 
    //  just to keep my attribute list clean looking
    font = 0;
    tw = -1;
    sprite.createVirtual(w, h);
    sprite.fillScreen(color);
  }
  //
  // I made special setter methods for the font/typeface so
  //  I could change them mid-program if I wanted to at some 
  //  point in the future
  void setFont(int _font) {
    font = _font;
  }

  void setFont(const GFXfont* _gfx) {
    gfx = _gfx;
    font = -1;
  }

  void text(char *text, int _textColor) {
    //
    // this is the only major new addition to my text methods
    if (tw > -1) {
      sprite.fillRect(tx, ty, tw, th, color);
    }

    if (font > -1) {
      sprite.setFont(font);
    } else {
      sprite.setFreeFont(gfx);
    }

    int16_t _x1, _y1;
    uint16_t _tw, _th;
    sprite.getTextBounds(text, 0, 0, &_x1, &_y1, &_tw, &_th);

    int x = (w / 2) - (_tw / 2);
    int y = (_y1 == 0) ? (h / 2) - (_th / 2) : (h / 2) + (_th / 2);

    tw = _tw;
    th = _th;
    tx = x;
    ty = (_y1 == 0) ? y : (y - th);

    sprite.setTextColor(_textColor, color);
    sprite.setCursor(x, y);
    sprite.println(text);
  }

  void text(char *text, int val, int _textColor) {

    if (tw > -1) {
      sprite.fillRect(tx, ty, tw, th, color);
    }

    if (font > -1) {
      sprite.setFont(font);
    } else {
      sprite.setFreeFont(gfx);
    }

    std::string valString = std::to_string(val);
    std::string textString(text);
    textString.pop_back();
    textString.pop_back();

    std::string wholeString = textString + valString;

    int16_t _x1, _y1;
    uint16_t _tw, _th;
    sprite.getTextBounds(wholeString.c_str(), 0, 0, &_x1, &_y1, &_tw, &_th);

    int x = (w / 2) - (_tw / 2);
    int y = (_y1 == 0) ? (h / 2) - (_th / 2) : (h / 2) + (_th / 2);

    tw = _tw;
    th = _th;
    tx = x;
    ty = (_y1 == 0) ? y : (y - th);

    sprite.setTextColor(_textColor, color);
    sprite.setCursor(x, y);
    sprite.printf(text, val);
  }
  //
  // I like the functionality this gives me and I'll probably 
  //  do some other drawing functions down the line
  void textOutline(int pad, int xOff, int yOff, int rad, int color) {
    int bw = tw + (pad * 2);
    int bh = th + (pad * 2);
    int bx = tx - pad + xOff;
    int by = ty - pad + yOff;
    sprite.drawRoundRect(bx, by, bw, bh, rad, color);
  }

  void draw(int x, int y, BB_SPI_LCD *_dest) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    _dest->drawSprite(x1, y1, &sprite);
  }

  bool click(TOUCHINFO *ti) {
    return (ti->x[0] >= x1 && ti->x[0] <= x2) && (ti->y[0] >= y1 && ti->y[0] <= y2);
  }
};