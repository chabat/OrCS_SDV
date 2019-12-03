#ifndef VRMT_SET_H
#define VRMT_SET_H

class VRMTSet_t{
    private:
        const uint32_t N_WAYS = 4;

    public:
        uint32_t nlines;
        uint32_t freeLines;
        VRMTLine_t *lines;

        VRMTSet_t(){
            this->nlines = this->N_WAYS;
            this->freeLines = this->nlines;
            this->lines = new VRMTLine_t[N_WAYS];
        }
};

#endif
