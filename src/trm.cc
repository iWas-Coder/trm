#include <args.hh>
#include <iostream>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();
  return 0;
}
