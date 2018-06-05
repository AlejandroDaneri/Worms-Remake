#ifndef WORMS_WALKINGANIMATION_H
#define WORMS_WALKINGANIMATION_H

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <queue>

class WalkingAnimation {
	private:
		std::queue<Glib::RefPtr<Gdk::Pixbuf>> walk_queue;
		Glib::RefPtr<Gdk::Pixbuf> walk_image;
		char dir;

	public:
		WalkingAnimation();
		~WalkingAnimation();
		WalkingAnimation(WalkingAnimation&& other);

		void setMovementImage(Gtk::Image& image, char new_dir);
		void setStaticImage(Gtk::Image& image);

		char getDir() const;
};


#endif //WORMS_WALKINGANIMATION_H
