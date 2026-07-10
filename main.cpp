#include <iostream>
#include <string>
#include <vector>

#include "bloom_filter.hpp"

int main() {
  // basic usage of bloom filter by simulating
  // database insertion
  std::vector<std::string> registered_users = {
      "sunbro92",       "ashen_one",        "praise_the_sun", "bonfire_keeper",
      "estus_enjoyer",  "moonlight_blade",  "darkwraith77",   "silver_knight",
      "black_knight13", "firelink_dweller", "hollowed_hero",  "chosen_one95",
      "abysswalker",    "souls_collector",  "embered",        "cinder_lord",
      "phantom_blue",   "red_invader",      "giantdad420",    "chaos_pyro"};

  // false positive chance of 1%
  BloomFilter taken_usernames(10000, 0.01);

  for (const auto &username : registered_users) {
    taken_usernames.add(username);
  }

  std::vector<std::string> signup_attempts = {
      "sunbro92",       // taken
      "moonlit_knight", // free
      "giantdad420",    // taken
      "dragon_slayer",  // free
      "ashen_one",      // taken
      "ringed_city",    // free
      "chaos_pyro",     // taken
      "fire_fades"      // free
  };

  std::cout << "Checking username availability:\n\n";

  for (const auto &username : signup_attempts) {
    if (taken_usernames.contain(username)) {
      // might be a false positive.
      // a real application would now verify with the database.
      std::cout << username << " -> probably taken, checking database...\n";
    } else {
      // available guaranteed
      std::cout << username << " -> definitely free, skipping database\n";
    }
  }

  return 0;
}
