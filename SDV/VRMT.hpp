#ifndef VRMT_H
#define VRMT_H
using namespace std;

class VRMT_t{
    private:
        const uint32_t N_SETS = 64;
        const uint32_t N_WAYS = 4;

    public:
        VRMTSet_t *sets;

        VRMT_t();
};

#endif // VRMT_H
