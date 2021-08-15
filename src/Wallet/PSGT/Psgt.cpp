#include "Psgt.h"

Psgt::Psgt()
{
    // TODO
/*
    inputs.resize(tx.vin.size());
    outputs.resize(tx.vout.size());
*/
}

bool Psgt::IsNull() const
{
    return !tx && inputs.empty() && outputs.empty() && unknown.empty();
}

Psgt::~Psgt()
{

}

Psgt::Serialize()
{


}

Psgt::SerializeMap()
{


}

bool PartiallySignedTransaction::AddInput(const CTxIn& txin, PsgtTInput& psgtin)
{
    if (std::find(tx->vin.begin(), tx->vin.end(), txin) != tx->vin.end()) {
        return false;
    }
    tx->vin.push_back(txin);
    inputs.push_back(psbtin);
    return true;
}

bool PartiallySignedTransaction::AddOutput(const CTxOut& txout, const PsgtOutput& psgtout)
{
    tx->vout.push_back(txout);
    outputs.push_back(psbtout);
    return true;
}

bool DecodeBase64PSBT(PartiallySignedTransaction& psgt, const std::string& base64_tx, std::string& error)
{
    bool invalid;
    std::string tx_data = DecodeBase64(base64_tx, &invalid);
    if (invalid) {
        error = "invalid base64";
        return false;
    }
    return DecodeRawPSBT(psbt, tx_data, error);
}

bool DecodeRawPSBT(PartiallySignedTransaction& psgt, const std::string& tx_data, std::string& error)
{
    // TODO
    try {
        ss_data >> psgt;
        if (!ss_data.empty()) {
            error = "extra data after PSGT";
            return false;
        }
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
    return true;
}