#ifndef SMZ3T_ITEMBOX_H
#define SMZ3T_ITEMBOX_H

#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

#include <string>
#include <vector>

class ItemArea : public Gtk::DrawingArea {
 public:
  ItemArea();
  ItemArea(std::vector<std::string> images, unsigned int range_start = 0,
           unsigned int range_end = 0, unsigned int range_step = 0);
  virtual ~ItemArea();
  void draw_next_state();
  void draw_init_state();
  void draw_prev_state();

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  std::vector<Glib::RefPtr<Gdk::Pixbuf>> m_images;
  unsigned int m_range_start;
  unsigned int m_range_end;
  unsigned int m_range_step;
  unsigned int m_state;
  unsigned int m_max_state;
};

class ItemBox : public Gtk::EventBox {
 public:
  ItemBox();
  ItemBox(std::vector<std::string> images, unsigned int range_start = 0,
          unsigned int range_end = 0, unsigned int range_step = 0);
  virtual ~ItemBox();

 protected:
  virtual bool on_button_release(GdkEventButton* event);
  ItemArea m_item;
};

#endif  // SMZ3T_ITEMBOX_H
