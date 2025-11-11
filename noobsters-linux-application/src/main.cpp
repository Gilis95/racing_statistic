#include <gtk/gtk.h>

#include "../include/core/linux_application.h"
#include "core/noobsters_logger.h"

int main(int argc, char **argv) {
  noobsters::log::init();
  noobsters::linux_platform::application app(argc, argv);
  return app.run();
}
