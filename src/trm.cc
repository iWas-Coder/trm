#include <args.hh>
#include <iostream>
#include <merkle_tree.hh>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  auto hash { trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute("Hello, World!") };
  trm::merkle::Tree<trm::merkle::DigestType::SHA256> tree;
  tree.insert(hash);

  std::cout << "Merkle root: " << tree.root() << std::endl;

  return 0;
}
