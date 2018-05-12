#include "myarea.h"
#include <cairomm/context.h>

MyArea::MyArea() {}

MyArea::~MyArea() {}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(1.0);

  // draw red lines out from the center of the window
  cr->set_source_rgb(0.8, 0.0, 0.0);
  cr->move_to(xc, yc);
  cr->rel_line_to(100, 0);
  cr->move_to(xc, yc);
  cr->rel_line_to(100, 100);
  cr->rel_line_to(200, 10); // Dibuja desde donde quedo 
  /*cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);*/
  cr->stroke();
  //sleep(2);
  //cr->rel_line_to(100, 100);
  //cr->stroke();
  cr->restore();

  return true;
}
