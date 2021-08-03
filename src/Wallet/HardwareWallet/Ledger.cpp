#include "Error.h"
#include "Ledger.h"
#include "Utils.h"
#include <iostream> 

namespace ledger {

    Ledger::Ledger() : transport(std::make_unique<Transport>(Transport::TransportType::HID)) {

    }

    Ledger::~Ledger() 
    {
	transport->close();
    }

    Error Ledger::open() 
    {
	return transport->open();
    }

// TODO: these functions are just examples
/*
    std::tuple<ledger::Error, std::vector<uint8_t>> Ledger::get_public_key(uint32_t account, bool confirm) {
	auto payload = utils::int_to_bytes(account, 4);
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_GET_PUBLIC_KEY, confirm, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }

    std::tuple<Error, std::vector<uint8_t>> Ledger::sign(uint32_t account, const std::vector<uint8_t>& msg) {
        auto payload = utils::int_to_bytes(account, 4);
	payload.insert(payload.end(), msg.begin(), msg.end());
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_SIGN, 0x00, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }
*/

    std::tuple<Error, std::vector<uint8_t>> SignSender(TxCommon txCommon)
    {
	auto payload = utils::int_to_bytes();
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_SIGN_SENDER, confirm, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }

    std::tuple<Error, std::vector<uint8_t>> SignReceiver(TxCommon txCommon)
    {	
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_SIGN_RECEIVER, confirm, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }

    std::tuple<Error, std::vector<uint8_t>> SignFinalize(TxCommon txCommon)
    {
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_SIGN_FINALIZE, confirm, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }


    void Ledger::close() {
	return transport->close();
    }

}
