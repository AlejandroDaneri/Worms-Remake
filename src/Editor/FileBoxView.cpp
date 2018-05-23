
#include "FileBoxView.h"

FileBoxView::FileBoxView(BaseObjectType *cobject,
                         const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Grid(cobject),
          m_builder(builder) {
    m_builder->get_widget("btn_save", save);
    m_builder->get_widget("btn_load", load);
}

void FileBoxView::linkControler(std::shared_ptr<FileBoxController> controller) {
    this->file_box_controller = std::move(controller);
    save->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onSaveClicked));

    save->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onLoadClicked));
}