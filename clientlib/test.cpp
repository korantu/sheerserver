#include <sheer_cloud.h>

int main() {
  SheerCloud * cloud = GetSheerCloud();
  cloud->Authorize("a", "b");
}
