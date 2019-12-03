#ifndef TL_H
#define TL_H
using namespace std;

class TL_t{
    private:
        const uint32_t N_SETS = 512;
        const uint32_t N_WAYS = 4;
        const uint32_t MAX_STRIDE_STATS = 1000000; //Maximum number of elements considered for the stats of the TL

        //Variables for TL statistics
        uint64_t *strideStats; //Strides for each number of elements
        uint64_t totalStrides; //Total number of strided loads

    public:
        TLSet_t *sets;

        TL_t();

        int tlFind(uint64_t pc); //Returns the line of the set if found, -1 otherwise
        void tlInsert(uint64_t pc, uint64_t last_address); //Insert a new load
        void tlUpdate(uint32_t line, uint32_t readSize, uint64_t pc, uint64_t address); //Update load entry
        void statistics(void); //Print statistics for the table of loads
};

#endif // TL_H
