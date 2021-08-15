#pragma once

#include <cstdint>
#include <vector>

namespace ledger::utils {

    int bytes_to_int(const std::vector<uint8_t>& bytes);

    std::vector<uint8_t> int_to_bytes(uint32_t n, uint32_t length);

} // namespace ledger::utils
