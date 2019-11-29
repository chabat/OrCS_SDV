#ifndef TL_H
#define TL_H
using namespace std;

class TL_t{
    private:
        const uint32_t N_SETS = 512;
        const uint32_t N_WAYS = 4;
        int *strideStats 

    public:
        TLSet_t *sets;

        TL_t();

        int tlFind(uint64_t pc); //Returns the line of the set if found, -1 otherwise
        void tlInsert(uint64_t pc, uint64_t last_address); //Insert a new load
        void tlUpdate(uint32_t line, uint32_t size, uint64_t pc, uint64_t address); //Update load entry
};

#endif // TL_H
