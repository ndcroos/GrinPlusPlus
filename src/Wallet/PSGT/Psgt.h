#ifndef _PSGT_H
#define _PSGT_H

// Magic bytes
static constexpr uint8_t PSBT_MAGIC_BYTES[5] = {'p', 's', 'g', 't', 0xff};

// Global key types
static constexpr uint8_t PSGT_FEE = b'\x01';
static constexpr uint8_t PSGT_HEIGHT = 0x;
static constexpr uint8_t PSGT_TRANSACTION_EXCESS = 0x;
static constexpr uint8_t PSGT_KERNEL_SIG = 0x;
static constexpr uint8_t PSGT_KERNEL_OFFSET = 0x; // Transaction kernel offset
static constexpr uint8_t PSGT_VERSION = 0x;

// Per-input key types
static constexpr uint8_t PSGT_OUTPUT_FEATURES = ;

// Per-output key types
static constexpr uint8_t PSGT_OUTPUT_FEATURES = 0x;
static constexpr uint8_t PSGT_OUT_RANGEPROOF = 0x;

// Payment proof key types
static constexpr uint8_t PSGT_RECEIVER_SIG = 0x0;

static constexpr uint8_t PSFT_SEPARATOR = 0x00;

// Takes a stream and multiple arguments and serializes them as if first serialized into a vector and then into the stream
// The resulting output into the stream has the total serialized length of all of the objects followed by all objects concatenated with each other.
template<typename Stream, typename... X>
void SerializeToVector(Stream& s, const X&... args)
{


}

// Takes a stream and multiple arguments and unserializes them first as a vector then each object individually in the order provided in the arguments
template<typename Stream, typename... X>
void UnserializeFromVector(Stream& s, X&... args)
{
    size_t expected_size = ReadCompactSize(s);
    size_t remaining_before = s.size();
    UnserializeMany(s, args...);
    size_t remaining_after = s.size();
    if (remaining_after + expected_size != remaining_before) {
        throw std::ios_base::failure("Size of value was not the stated size");
    }
}


class Psgt
{
public:
	Psgt();
	~Psgt();

	void Serialize();
	void SerializeMap();
	void Parse();

private:

}

/** A structure for PSGTs which contain per-input information */
struct PSGTInput
{
    PSGTInput() {}
    bool IsNull() const;

    template <typename Stream>
    inline void Serialize(Stream& s) const {

        // Write unknown things
        for (auto& entry : unknown) {
            s << entry.first;
            s << entry.second;
        }

        s << PSBT_SEPARATOR;
    }

    template <typename Stream>
    inline void Unserialize(Stream& s) {

        // Used for duplicate key detection
        std::set<std::vector<unsigned char>> key_lookup;

        // Read loop
        bool found_sep = false;

        while(!s.empty()) {
            // Read
            std::vector<unsigned char> key;
            s >> key;

            // the key is empty if that was actually a separator byte
            // This is a special case for key lengths 0 as those are not allowed (except for separator)
            if (key.empty()) {
                found_sep = true;
                break;
            }

            // Type is compact size uint at beginning of key
            VectorReader skey(s.GetType(), s.GetVersion(), key, 0);
            uint64_t type = ReadCompactSize(skey);

            // Do stuff based on type
            switch(type) {

                // Unknown stuff
                default:
                    if (unknown.count(key) > 0) {
                        throw std::ios_base::failure("Duplicate Key, key for unknown value already provided");
                    }
                    // Read in the value
                    std::vector<unsigned char> val_bytes;
                    s >> val_bytes;
                    unknown.emplace(std::move(key), std::move(val_bytes));
                    break;
            }

        }
        if (!found_sep) {
            throw std::ios_base::failure("Separator is missing at the end of an input map");
        }
    }

};

/** A structure for PSGTs which contain per-output information */
struct PSGTOutput
{
    PSGTOutput() {}
    bool IsNull() const;

    template <typename Stream>
    inline void Serialize(Stream& s) const {

        // Write unknown things
        for (auto& entry : unknown) {
            s << entry.first;
            s << entry.second;
        }

        s << PSBT_SEPARATOR;
    }

    template <typename Stream>
    inline void Unserialize(Stream& s) {
        // Used for duplicate key detection
        std::set<std::vector<unsigned char>> key_lookup;

        // Read loop
        bool found_sep = false;
        while(!s.empty()) {
            // Read
            std::vector<unsigned char> key;
            s >> key;

            // the key is empty if that was actually a separator byte
            // This is a special case for key lengths 0 as those are not allowed (except for separator)
            if (key.empty()) {
                found_sep = true;
                break;
            }

            // Type is compact size uint at beginning of key
            VectorReader skey(s.GetType(), s.GetVersion(), key, 0);
            uint64_t type = ReadCompactSize(skey);

            // Do stuff based on type
            switch(type) {
                // Unknown stuff
                default: {
                    if (unknown.count(key) > 0) {
                        throw std::ios_base::failure("Duplicate Key, key for unknown value already provided");
                    }
                    // Read in the value
                    std::vector<unsigned char> val_bytes;
                    s >> val_bytes;
                    unknown.emplace(std::move(key), std::move(val_bytes));
                    break;
                }
            }
        }
        if (!found_sep) {
            throw std::ios_base::failure("Separator is missing at the end of an output map");
        }
    }

};

/** A structure for PSGTs which contain payment proof information */
struct PSGTPaymentProof
{
    PSGTPaymentProof() {}
    bool IsNull() const;

    template <typename Stream>
    inline void Serialize(Stream& s) const {

    }

    template <typename Stream>
    inline void Unserialize(Stream& s) {

    }

};


struct PartiallySignedTransaction
{
    std::vector<PSGTInput> inputs;
    std::vector<PSGTOutput> outputs;
    PSGTPaymentProof paymentproof;
    std::map<std::vector<unsigned char>, std::vector<unsigned char>> unknown;

    bool IsNull() const;

    bool AddInput(PSGTInput& psgtin);
    bool AddOutput(const PSGTOutput& psgtout);
    bool AddPaymentProof(PSGTPaymentProof paymentProof);
    PartiallySignedTransaction() {}

    inline void Serialize(Stream& s) const {

        // magic bytes
        s << PSGT_MAGIC_BYTES;

        // Write the unknown things
        for (auto& entry : unknown) {
            s << entry.first;
            s << entry.second;
        }

        // Separator
        s << PSGT_SEPARATOR;

        // Write inputs
        for (const PSGTInput& input : inputs) {
            s << input;
        }
        // Write outputs
        for (const PSGTOutput& output : outputs) {
            s << output;
        }
    }

    template <typename Stream>
    inline void Unserialize(Stream& s) 
        // Read the magic bytes
        uint8_t magic[5];
        s >> magic;
        if (!std::equal(magic, magic + 5, PSGT_MAGIC_BYTES)) {
            throw std::ios_base::failure("Invalid PSGT magic bytes");
        }

        // Used for duplicate key detection
        std::set<std::vector<unsigned char>> key_lookup;

        // Read global data
        bool found_sep = false;
        while(!s.empty()) {
            // Read
            std::vector<unsigned char> key;
            s >> key;

            // the key is empty if that was actually a separator byte
            // This is a special case for key lengths 0 as those are not allowed (except for separator)
            if (key.empty()) {
                found_sep = true;
                break;
            }

            // First byte of key is the type
            unsigned char type = key[0];

            // Do stuff based on type
            switch(type) {
                case PSBT_GLOBAL_UNSIGNED_TX:
                {
                    if (!key_lookup.emplace(key).second) {
                        throw std::ios_base::failure("Duplicate Key, unsigned tx already provided");
                    } else if (key.size() != 1) {
                        throw std::ios_base::failure("Global unsigned tx key is more than one byte type");
                    }
                    CMutableTransaction mtx;
                    // Set the stream to serialize with non-witness since this should always be non-witness
                    OverrideStream<Stream> os(&s, s.GetType(), s.GetVersion() | SERIALIZE_TRANSACTION_NO_WITNESS);
                    UnserializeFromVector(os, mtx);
                    tx = std::move(mtx);
                    // Make sure that all scriptSigs and scriptWitnesses are empty
                    for (const CTxIn& txin : tx->vin) {
                        if (!txin.scriptSig.empty() || !txin.scriptWitness.IsNull()) {
                            throw std::ios_base::failure("Unsigned tx does not have empty scriptSigs and scriptWitnesses.");
                        }
                    }
                    break;
                }
                // Unknown stuff
                default: {
                    if (unknown.count(key) > 0) {
                        throw std::ios_base::failure("Duplicate Key, key for unknown value already provided");
                    }
                    // Read in the value
                    std::vector<unsigned char> val_bytes;
                    s >> val_bytes;
                    unknown.emplace(std::move(key), std::move(val_bytes));
                }
            }
        }

        if (!found_sep) {
            throw std::ios_base::failure("Separator is missing at the end of the global map");
        }

        // Make sure that we got an unsigned tx
        if (!tx) {
            throw std::ios_base::failure("No unsigned transcation was provided");
        }

        // Read input data
        unsigned int i = 0;
        while (!s.empty() && i < tx->vin.size()) {
            PSBTInput input;
            s >> input;
            inputs.push_back(input);

            // Make sure the non-witness utxo matches the outpoint
            if (input.non_witness_utxo && input.non_witness_utxo->GetHash() != tx->vin[i].prevout.hash) {
                throw std::ios_base::failure("Non-witness UTXO does not match outpoint hash");
            }
            ++i;
        }
        // Make sure that the number of inputs matches the number of inputs in the transaction
        if (inputs.size() != tx->vin.size()) {
            throw std::ios_base::failure("Inputs provided does not match the number of inputs in transaction.");
        }

        // Read output data
        i = 0;
        while (!s.empty() && i < tx->vout.size()) {
            PSBTOutput output;
            s >> output;
            outputs.push_back(output);
            ++i;
        }
        // Make sure that the number of outputs matches the number of outputs in the transaction
        if (outputs.size() != tx->vout.size()) {
            throw std::ios_base::failure("Outputs provided does not match the number of outputs in transaction.");
        }
    }

    template <typename Stream>
    PartiallySignedTransaction(deserialize_type, Stream& s) {
        Unserialize(s);
    }
};

enum class PSGTRole {
    CREATOR,
    UPDATER,
    SIGNER,
    FINALIZER,
    EXTRACTOR
};

std::string PSGTRoleName(PSGTRole role);


//! Decode a base64ed PSGT into a PartiallySignedTransaction
bool DecodeBase64PSGT(PartiallySignedTransaction& decoded_psgt, const std::string& base64_psgt, std::string& error);
//! Decode a raw (binary blob) PSGT into a PartiallySignedTransaction
bool DecodeRawPSBT(PartiallySignedTransaction& decoded_psgt, const std::string& raw_psgt, std::string& error);


#endif // _PSGT_H