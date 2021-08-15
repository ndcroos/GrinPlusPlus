
#include "Ledger.h"
#include "Utils.h"
#include <iostream> 

namespace ledger {

    Ledger::Ledger() : transport(std::make_unique<Transport>(Transport::TransportType::HID)) 
    {

    }

    Ledger::~Ledger() 
    {
	this->transport->close();
    }

    Error Ledger::open() 
    {
	return this->transport->open();
    }

// TODO: these functions are just examples
/*
    std::tuple<ledger::Error, std::vector<uint8_t>> Ledger::get_public_key(uint32_t account, bool confirm) {
	auto payload = utils::int_to_bytes(account, 4);
	auto [err, buffer] = this->transport->exchange(APDU::CLA, APDU::INS_GET_PUBLIC_KEY, confirm, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }

    std::tuple<Error, std::vector<uint8_t>> Ledger::sign(uint32_t account, const std::vector<uint8_t>& msg) {
        std::vector<uint8_t> payload = utils::int_to_bytes(account, 4);
	payload.insert(payload.end(), msg.begin(), msg.end());
	auto [err, buffer] = transport->exchange(APDU::CLA, APDU::INS_SIGN, 0x00, 0x00, payload);
	if (err != Error::SUCCESS)
	    return {err, {}};
	return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
    }
*/

    std::tuple<Error, std::vector<uint8_t>> Ledger::SignSender(TxCommon txCommon)
    {
        
	std::vector<uint8_t> payload = utils::int_to_bytes();
        //payload.insert(payload.end(), 
	auto [err, buffer] = this->transport->exchange(Ledger::APDU::CLA, Ledger::APDU::INS_SIGN_SENDER, 0x00, payload);
	if (err != Error::SUCCESS)
	    return std::make_tuple(err, {});
	return std::make_tuple(err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end() ) );
    }

    std::tuple<Error, std::vector<uint8_t>> Ledger::SignReceiver(TxCommon txCommon)
    {	
        
        std::vector<uint8_t> payload = utils::int_to_bytes();
	auto [err, buffer] = this->transport->exchange(Ledger::APDU::CLA, Ledger::APDU::INS_SIGN_RECEIVER, 0x00, payload);
	if (err != Error::SUCCESS)
	    return std::make_tuple(err, {});
	return std::make_tuple(err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end()) );
    }

    std::tuple<Error, std::vector<uint8_t>> Ledger::SignFinalize(TxCommon txCommon)
    {
        
        std::vector<uint8_t> payload = utils::int_to_bytes();
	auto [err, buffer] = this->transport->exchange(Ledger::APDU::CLA, Ledger::APDU::INS_SIGN_FINALIZE, 0x00, payload);
	if (err != Error::SUCCESS)
	    return std::make_tuple(err, {});
	return std::make_tuple(err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end()) );
    }

    void Ledger::close() {
	return this->transport->close();
    }

}
