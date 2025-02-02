#pragma once

#include <secp256k1-zkp/secp256k1.h>

// SEE: https://github.com/mimblewimble/rust-secp256k1-zkp/blob/304ef7264a0dd9ef4efaaa0e28480cb030c18265/src/constants.rs#L138-L188
secp256k1_pubkey GENERATOR_J_PUB = {{
		0x5f, 0x15, 0x21, 0x36, 0x93, 0x93, 0x01, 0x2a,
		0x8d, 0x8b, 0x39, 0x7e, 0x9b, 0xf4, 0x54, 0x29,
		0x2f, 0x5a, 0x1b, 0x3d, 0x38, 0x85, 0x16, 0xc2,
		0xf3, 0x03, 0xfc, 0x95, 0x67, 0xf5, 0x60, 0xb8,
		0x3a, 0xc4, 0xc5, 0xa6, 0xdc, 0xa2, 0x01, 0x59,
		0xfc, 0x56, 0xcf, 0x74, 0x9a, 0xa6, 0xa5, 0x65,
		0x31, 0x6a, 0xa5, 0x03, 0x74, 0x42, 0x3f, 0x42,
		0x53, 0x8f, 0xaa, 0x2c, 0xd3, 0x09, 0x3f, 0xa4
}};
