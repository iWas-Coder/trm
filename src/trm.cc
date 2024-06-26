#include <args.hh>
#include <iostream>
#include <merkle_tree.hh>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  trm::merkle::Tree<trm::merkle::DigestType::SHA256> tree;

  for (const auto &i : { "Hello", "World", "This is", "C++" }) {
    tree.insert(trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute(i));
  }

  std::cout << "Merkle root: " << tree.root() << std::endl;

  return 0;
}
