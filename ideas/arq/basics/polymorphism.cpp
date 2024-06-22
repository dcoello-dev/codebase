// sandbox_idea: arq/basics
// sandbox_name: polymorphism
// sandbox_description: simple polymorphism example
// sandbox_env: cpp

#include <array>
#include <iostream>

/// sandbox_link_start: STATIC_DESIGN
/// sandbox_link_start: TYPE
// animal types
enum class Type { MAMMAL, FISH };
/// sandbox_link_end: TYPE

/// sandbox_link_start: IANIMAL
// define contract animal with is something that talks and eats
// I stands for Interface
class IAnimal {
public:
  virtual Type type() noexcept = 0;
  virtual void talk() noexcept = 0;
  virtual void eat() noexcept = 0;
};
/// sandbox_link_end: IANIMAL

/// sandbox_link_start: MAMMAL
/// sandbox_link_start: AMAMMAL
// all mammals does same sound eating
// A stands for Abstract
class AMammal : public IAnimal {
public:
  Type type() noexcept override { return Type::MAMMAL; }
  virtual void eat() noexcept override {
    std::cout << "crunch crunch" << std::endl;
  }
};
/// sandbox_link_end: AMAMMAL

/// sandbox_link_start: MAMMAL_IMPL
class Cat : public AMammal {
public:
  void talk() noexcept override { std::cout << "meow meow" << std::endl; }
};

class Dog : public AMammal {
public:
  void talk() noexcept override { std::cout << "wof wof" << std::endl; }
};
/// sandbox_link_end: MAMMAL_IMPL
/// sandbox_link_end: MAMMAL

/// sandbox_link_start: FISH
/// sandbox_link_start: AFISH
// abstract class for fishes
class AFish : public IAnimal {
public:
  Type type() noexcept override { return Type::FISH; }
  virtual void talk() noexcept override {
    std::cout << "glup glup" << std::endl;
  }
  virtual void eat() noexcept override {
    std::cout << "slurp slurp" << std::endl;
  }
};
/// sandbox_link_end: AFISH

/// sandbox_link_start: FISH_IMPL
class OrangeFish : public AFish {
public:
  void talk() noexcept override { std::cout << "..." << std::endl; }
};

class PurpleFish : public AFish {
public:
};
/// sandbox_link_end: FISH_IMPL
/// sandbox_link_end: FISH
/// sandbox_link_end: STATIC_DESIGN

/// sandbox_link_start: DYNAMIC_DESIGN
/// sandbox_link_start: FEED
// feed any type of animals
void feed_animal(IAnimal &animal) {
  animal.talk();
  animal.eat();
}
/// sandbox_link_end: FEED

/// sandbox_link_start: TALK
// talk only with fishes
void talk_with_fishes(AFish &fish) { fish.talk(); }
/// sandbox_link_end: TALK

/// sandbox_link_start: MAIN
int main(void) {
  /// sandbox_link_start: INSTANTIATION
  Cat c{};
  Dog d{};
  OrangeFish of{};
  PurpleFish pf{};

  std::array<IAnimal *, 4> zoo{&c, &d, &of, &pf};
  /// sandbox_link_end: INSTANTIATION

  /// sandbox_link_start: LOOP
  for (auto animal : zoo) {
    feed_animal(*animal);
    if (animal->type() == Type::FISH) {
      // try to avoid this type of casts
      talk_with_fishes(*static_cast<AFish *>(animal));
    }
    std::cout << std::endl;
  }
  /// sandbox_link_end: LOOP

  return 0;
}
/// sandbox_link_end: MAIN
/// sandbox_link_end: DYNAMIC_DESIGN
