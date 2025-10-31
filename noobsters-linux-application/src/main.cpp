#include <gtk/gtk.h>

#include "../include/core/linux_application.h"

int main(int argc, char **argv) {
  noobsters::linux_platform::application app(argc, argv);
  return app.run();
}
