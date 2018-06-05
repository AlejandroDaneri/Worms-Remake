#ifndef WORMS_WALKINGANIMATION_H
#define WORMS_WALKINGANIMATION_H

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <queue>

class WalkingAnimation {
	private:
		std::queue<Glib::RefPtr<Gdk::Pixbuf>> walk_queue;
		Glib::RefPtr<Gdk::Pixbuf> walk_image;
		Gtk::Image* worm_image;
		char dir;

	public:
		WalkingAnimation(Gtk::Image* worm_image);
		~WalkingAnimation();
		WalkingAnimation(WalkingAnimation&& other);

		void setMovementImage(char new_dir);
		void setStaticImage();

		void updateWormImage(Gtk::Image* worm_image);
};


#endif //WORMS_WALKINGANIMATION_H
