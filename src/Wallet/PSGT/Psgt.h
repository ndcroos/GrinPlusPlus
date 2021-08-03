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

class Psgt
{
public:
	Psgt();
	~Psgt();

	Serialize();
	SerializeMap();
	Parse();

private:

}

/** A structure for PSGTs which contain per-input information */
struct PSGTInput
{
    PSGTInput() {}
    bool IsNull() const;

    template <typename Stream>
    inline void Serialize(Stream& s) const {

    }

    template <typename Stream>
    inline void Unserialize(Stream& s) {

    }

};

/** A structure for PSGTs which contain per-output information */
struct PSGTOutput
{
    PSGTOutput() {}
    bool IsNull() const;

    template <typename Stream>
    inline void Serialize(Stream& s) const {

    }

    template <typename Stream>
    inline void Unserialize(Stream& s) {

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


    bool IsNull() const;
    bool AddInput(PSGTInput& psbtin);
    bool AddOutput(const PSGTOutput& psbtout);
    PartiallySignedTransaction() {}

    inline void Serialize(Stream& s) const {

    }

    template <typename Stream>
    inline void Unserialize(Stream& s) 

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

#endif // _PSGT_H