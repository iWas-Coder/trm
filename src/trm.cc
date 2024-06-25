#include <args.hh>
#include <iostream>
#include <merkle_tree.hh>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  auto hash1 { trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute("Hello, World!") };
  auto hash2 { trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute("Welcome to San Andreas...") };
  auto hash3 { trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute("This is C++ and its cool :D") };
  auto hash4 { trm::merkle::Hash<trm::merkle::DigestType::SHA256>::compute("Leaks are scheiße") };
  trm::merkle::Tree<trm::merkle::DigestType::SHA256> tree;
  tree.insert(hash1);
  tree.insert(hash2);
  tree.insert(hash3);
  tree.insert(hash4);

  std::cout << "Merkle root: " << tree.root() << std::endl;

  return 0;
}
