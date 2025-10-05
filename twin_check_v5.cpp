
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <string>

using namespace std;

// Sieve of Eratosthenes
vector<bool> sievePrimes(uint64_t limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (uint64_t i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (uint64_t j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Extract twin primes from a prime sieve
vector<pair<uint64_t, uint64_t>> extractTwinPrimes(const vector<bool>& is_prime) {
    vector<pair<uint64_t, uint64_t>> twins;
    for (uint64_t i = 2; i + 2 < is_prime.size(); ++i) {
        if (is_prime[i] && is_prime[i + 2]) {
            twins.emplace_back(i, i + 2);
        }
    }
    return twins;
}

// Count twin pairs where second twin ≤ x
uint64_t countTwinPrimes(const vector<pair<uint64_t, uint64_t>>& twins, uint64_t x) {
    return count_if(twins.begin(), twins.end(), [&](const pair<uint64_t, uint64_t>& p) {
        return p.second <= x;
    });
}

// Write checkpoint file
void writeCheckpoint(uint64_t index, uint64_t n, uint64_t twin1, uint64_t twin2) {
    ofstream ckpt("checkpoint.txt");
    ckpt << "last_checked_index: " << index << "\n";
    ckpt << "last_n: " << n << "\n";
    ckpt << "last_twin1: " << twin1 << "\n";
    ckpt << "last_twin2: " << twin2 << "\n";
    ckpt.flush();
}

// Read checkpoint if exists
bool readCheckpoint(uint64_t& index, uint64_t& n, uint64_t& twin1, uint64_t& twin2) {
    ifstream ckpt("checkpoint.txt");
    if (!ckpt.is_open()) return false;
    string line;
    while (getline(ckpt, line)) {
        istringstream iss(line);
        string label;
        if (line.find("last_checked_index") != string::npos) {
            iss >> label >> index;
        } else if (line.find("last_n") != string::npos) {
            iss >> label >> n;
        } else if (line.find("last_twin1") != string::npos) {
            iss >> label >> twin1;
        } else if (line.find("last_twin2") != string::npos) {
            iss >> label >> twin2;
        }
    }
    return true;
}

int main() {
    const uint64_t START = 2;
    const uint64_t END = 100000000000ULL;      // 10^11
    const uint64_t CHUNK_SIZE = 1000000000ULL; // 10^9
    const uint64_t BUFFER = 1000000;           // for safe twin triplet search

    uint64_t resume_index = 1, resume_n = 0, resume_twin1 = 0, resume_twin2 = 0;
    bool resumed = readCheckpoint(resume_index, resume_n, resume_twin1, resume_twin2);

    uint64_t global_index = resume_index;
    
    // If resuming, jump directly to the chunk that contains resume_n
    uint64_t START_CHUNK = START;
    if (resumed) {
       START_CHUNK = (resume_n / CHUNK_SIZE) * CHUNK_SIZE + 2;
    }

    for (uint64_t chunk_start = START_CHUNK; chunk_start < END; chunk_start += CHUNK_SIZE) {
        uint64_t chunk_end = min(chunk_start + CHUNK_SIZE - 1, END);
        cout << "== Processing chunk: [" << chunk_start << ", " << chunk_end << "] ==" << endl;

        uint64_t sieve_limit = chunk_end + BUFFER;
        auto is_prime = sievePrimes(sieve_limit);
        auto twin_primes = extractTwinPrimes(is_prime);

        ostringstream fname;
        fname << "twin_table_range_" << chunk_start << "_" << chunk_end << ".csv";
        ofstream fout(fname.str(), ios::app); 
        if (fout.tellp() == 0) {
        fout << "Index,Twin1,Twin2,n,2*pi2(n),pi2(2n),Holds\n";
         }


        for (size_t i = 0; i + 2 < twin_primes.size(); ++i) {
            auto p1 = twin_primes[i];
            auto p2 = twin_primes[i + 1];
            auto p3 = twin_primes[i + 2];

            uint64_t n = p3.first - 1;

            // Skip previously processed triplets
            if (resumed && n <= resume_n)
                continue;

            if (n < chunk_start || n > chunk_end)
                continue;

            uint64_t pi2_n = countTwinPrimes(twin_primes, n);
            uint64_t pi2_2n = countTwinPrimes(twin_primes, 2 * n);
            bool holds = (2 * pi2_n >= pi2_2n);

            fout << global_index++ << ",";
            fout << p1.first << "," << p1.second << ",";
            fout << n << "," << 2 * pi2_n << "," << pi2_2n << "," << (holds ? "True" : "False") << "\n";

            if (global_index % 1000 == 0) {
                cout << "Checkpoint at index " << global_index << " (n = " << n << ")" << endl;
                writeCheckpoint(global_index, n, p1.first, p1.second);
                fout.flush();
            }
        }
        fout.close();
    }

    return 0;
}
