#define BOOST_ALL_DYN_LINK

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include "token/Tokenizer.h"
#include "parse/Parser.h"
#include "tree/Node.h"

namespace po = boost::program_options;

po::variables_map options(int argc, char **argv) {
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "print this message")
    ("verbose,v", "enable verbose mode")
    ("input-file", po::value<std::vector<std::string>>(), "input file");

  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  po::notify(vm);

  if(vm.count("help")) {
    std::cout << desc << std::endl;
    exit(EXIT_SUCCESS);
  }

  if(!vm.count("input-file")) {
    std::cout << desc << std::endl;
    exit(EXIT_SUCCESS);
  }

  if(vm.count("verbose")) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
  } else {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::fatal);
  }

  return vm;
}

int main(int argc, char **argv) {
  po::variables_map vm = options(argc, argv);

  std::vector<std::string> inputs = vm["input-file"].as<std::vector<std::string>>();
  for(std::string file : inputs) {
    std::fstream fs(file, std::fstream::in);

    if(!fs) {
      BOOST_LOG_TRIVIAL(fatal) << "Unable to open file";
      return EXIT_FAILURE;
    }

    Tokenizer tokenizer;
    Parser parser(fs, tokenizer);

    Node *root = parser.parse();

    if(vm.count("verbose")) {
      root->printTree();
    }

    std::cout << root->emitTree() << std::endl;

    fs.close();
  }

  return EXIT_SUCCESS;
}

