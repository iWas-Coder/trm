#include <args.hh>
#include <iostream>
#include <block.hh>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  std::vector<trm::chain::TX<trm::merkle::DigestType::SHA256>> txns;
  for (const auto &i : args.getFiles()) txns.emplace_back(trm::chain::TX<trm::merkle::DigestType::SHA256> { i });
  trm::chain::Block<trm::merkle::DigestType::SHA256> block { txns };

  std::cout << std::endl;
  block.print();

  return 0;
}
