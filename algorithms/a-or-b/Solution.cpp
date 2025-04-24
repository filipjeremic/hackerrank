#include <cctype>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

[[nodiscard]]
static std::vector<bool>
hexStringToBitVector(const std::string_view hexString) noexcept {
  std::vector<bool> bitVector;
  bitVector.reserve(hexString.size() * 4);

  for (const char c : hexString) {
    const int hexValue = c - (std::isdigit(c) ? '0' : 'A' - 10);
    for (int i = 3; i >= 0; i--) {
      bitVector.push_back(((hexValue >> i) & 1) != 0);
    }
  }

  return bitVector;
}

[[nodiscard]]
static std::string
bitVectorToHexString(const std::vector<bool> &bitVector) noexcept {
  std::stringstream ss;
  bool skipZero = true;
  for (std::size_t i = 0; i < bitVector.size(); i += 4) {
    int hexValue = 0;
    for (std::size_t j = 0; j < 4; j++) {
      hexValue = (hexValue << 1) | bitVector[i + j];
    }
    if (!skipZero || hexValue != 0) {
      skipZero = false;
      constexpr std::string_view hexDigits = "0123456789ABCDEF";
      ss << hexDigits[hexValue];
    }
  }

  std::string hexString = ss.str();
  return hexString.empty() ? "0" : hexString;
}

[[nodiscard]]
static bool getInitialResult(int &k, std::vector<bool> &aBitVector,
                             std::vector<bool> &bBitVector,
                             const std::vector<bool> &cBitVector) noexcept {
  for (std::size_t i = 0; i < aBitVector.size(); i++) {
    const bool a = aBitVector[i];
    const bool b = bBitVector[i];
    const bool c = cBitVector[i];

    aBitVector[i] = a && c;
    bBitVector[i] = c && (!a || (a && b));

    const int da = a == aBitVector[i] ? 0 : 1;
    const int db = b == bBitVector[i] ? 0 : 1;
    k -= da + db;

    if (k < 0) {
      return false;
    }
  }

  return true;
}

static void minimizeA(int &k, std::vector<bool> &aBitVector,
                      std::vector<bool> &bBitVector) noexcept {
  for (std::size_t i = 0; i < aBitVector.size(); i++) {
    if (k == 0) {
      return;
    }

    if (!aBitVector[i]) {
      continue;
    }

    if (bBitVector[i]) {
      k--;
    } else if (k >= 2) {
      k -= 2;
    } else {
      continue;
    }

    aBitVector[i] = false;
    bBitVector[i] = true;
  }
}

[[nodiscard]]
static std::optional<std::pair<std::string, std::string>>
a_or_b(int k, const std::string_view aHexString,
       const std::string_view bHexString,
       const std::string_view cHexString) noexcept {

  std::vector<bool> aBitVector = hexStringToBitVector(aHexString);
  std::vector<bool> bBitVector = hexStringToBitVector(bHexString);
  const std::vector<bool> cBitVector = hexStringToBitVector(cHexString);

  if (!getInitialResult(k, aBitVector, bBitVector, cBitVector)) {
    return std::nullopt;
  }

  minimizeA(k, aBitVector, bBitVector);

  return std::make_pair(bitVectorToHexString(aBitVector),
                        bitVectorToHexString(bBitVector));
}

int main() {
  int q = 0;
  std::cin >> q;

  for (int i = 0; i < q; i++) {
    int k = 0;
    std::string a, b, c;

    std::cin >> k >> a >> b >> c;

    if (const auto result = a_or_b(k, a, b, c)) {
      std::cout << result.value().first << '\n'
                << result.value().second << std::endl;
    } else {
      std::cout << -1 << std::endl;
    }
  }

  return 0;
}
