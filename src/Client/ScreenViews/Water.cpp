#include "Water.h"
#include "Path.h"
#include "ObjectSizes.h"

Water::Water(){}

Water::~Water(){}

void Water::show(Gtk::Layout& layout){
	size_t pos = 0;
	guint width, height;
	layout.get_size(width, height);
	
	while(pos < width){
		Gtk::Image image;
		image.set(IMAGES_PATH + "Water.png");
		this->images.push_back(std::move(image));
		layout.put(this->images.back(), pos, height - water_height);
		pos += water_length;
	}
}
