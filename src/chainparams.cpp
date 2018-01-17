// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xe3;
        pchMessageStart[3] = 0xf4;
        vAlertPubKey = ParseHex("1a53865b96e9056bc6b132a04b94acefeac5d5257fe028b80695c61f7c2f81f85d251a296df3be497653f457862f2d08c6314abd6ca3cbe5616262ca3e7a6ceaf0");
        nDefaultPort = 60081;
        nRPCPort = 70043;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "BY JORDAN VALINSKY - Microsoft's chip security fix is turning some PCs into bricks - January 10, 2018"; // Saturday, 15-Oct-16 12:00:00 UTC 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1515623352, vin, vout, 0); // Saturday, 15-Oct-16 12:00:00 UTC 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1515623352; // Saturday, 15-Oct-16 12:00:00 UTC 
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 7195;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 48c5e8653b0eb2993a78487b5148c30da7113e68b40b7523c59a6dae6c81ffa2
        block.nTime = 1515623352
        block.nNonce = 7195
        block.GetHash = 000011ce27bc5b732b78e253be638cc55156130a5b712effcc87ee326d2085ea
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000011ce27bc5b732b78e253be638cc55156130a5b712effcc87ee326d2085ea"));
        assert(genesis.hashMerkleRoot == uint256("0x48c5e8653b0eb2993a78487b5148c30da7113e68b40b7523c59a6dae6c81ffa2"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,46);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,28);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 5 * 60; // Initial
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 5 * 60;
        }
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
          if(nBestHeight <= nLastPoWBlock)
          {
            nTargetSpacing = 15 * 60;
          }
        }
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 50000;
        nStartPoSBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xe3;
        pchMessageStart[3] = 0xf4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 15);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 15);

        vAlertPubKey = ParseHex("02a46815b96e9056bc6b132a04b94acefeac5d5257fe028e81695c62f7c2f81e85d251a216df3af197653f454852a2d08c6314aad5ca3cde6716262ca2e8c6beef");
        nDefaultPort = 98765;
        nRPCPort = 54321;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime  = 1515623352+60;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 4695;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 48c5e8653b0eb2993a78487b5148c30da7113e68b40b7523c59a6dae6c81ffa2
        block.nTime = 1515623412
        block.nNonce = 4695
        block.GetHash = 00007d23ef8661d0b169412138084908781f574c161c0a88a6fc98615c2a04e9
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00007d23ef8661d0b169412138084908781f574c161c0a88a6fc98615c2a04e9"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,130);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,109);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,88);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 5 * 60;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 1;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xb4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1515623352;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 93549;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 48c5e8653b0eb2993a78487b5148c30da7113e68b40b7523c59a6dae6c81ffa2
        block.nTime = 1515623352
        block.nNonce = 8
        block.GetHash = 959b4388a8e1cb280c8a1829f49ee73c009e1189dafd1cbb9995a79d42069906
        */

        assert(hashGenesisBlock == uint256("0x959b4388a8e1cb280c8a1829f49ee73c009e1189dafd1cbb9995a79d42069906"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
