#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

class BloomFilter {
private:
  size_t m_numBits{};
  size_t m_numHashs{};
  std::vector<uint8_t> m_bits{};

  static size_t calc_num_bits(size_t capacity, double false_pos_rate) {
    double ln2{ std::log(2.0) };
    return static_cast<size_t>(
      std::ceil(-(static_cast<double>(capacity) * std::log(false_pos_rate)) / (ln2 * ln2))
    );
  }

  static size_t calc_m_hashs(size_t num_bits, size_t capacity) {
    return static_cast<size_t>(
      std::round((static_cast<double>(num_bits) / static_cast<double>(capacity)) * std::log(2.0))
    );
  }

  size_t get_pos(const std::string_view item, size_t hash_idx) const {
    std::hash<std::string_view> strHash{};
    size_t hash1{ strHash(item) };
    size_t hash2{ strHash(std::string(item) + std::to_string(hash_idx)) };

    return (hash1 + hash_idx * hash2) % m_numBits;
  }

public:
  BloomFilter(size_t capacity, double false_pos_rate) {
    m_numBits = calc_num_bits(capacity, false_pos_rate);
    m_numHashs =  calc_m_hashs(m_numBits, capacity);
    m_bits.assign(m_numBits, 0);
  }

  void add(const std::string_view item) {
    for (size_t i{0}; i < m_numHashs; ++i)
      m_bits[get_pos(item, i)] = 1;
  }

  bool contain(const std::string_view item) const {
    for (size_t i{0}; i < m_numHashs; ++i)
      if (m_bits[get_pos(item, i)] == 0)
        return false;
      
    return true;
  }

  void clear() {
    m_bits.assign(m_numBits, 0);
  }

  size_t bit_count() const { return m_numBits; }
  size_t hash_count() const { return m_numHashs; }
};
