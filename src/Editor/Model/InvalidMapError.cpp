
#include <gtkmm/enums.h>
#include <gtkmm/messagedialog.h>
#include "InvalidMapError.h"

InvalidMapError::InvalidMapError(const char *message) noexcept : message(message){
}

const char *InvalidMapError::what() const noexcept{
    Gtk::Window dialog_window;
    Gtk::MessageDialog dialog("Error al guardar archivo", false,Gtk::MESSAGE_WARNING);
    dialog.set_transient_for(dialog_window);
    dialog.set_secondary_text(message);
    dialog.run();
    return message;
}

InvalidMapError::~InvalidMapError() {
}
