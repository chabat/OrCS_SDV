#ifndef TL_SET_H
#define TL_SET_H

class TLSet_t{
    private:
        const uint32_t N_WAYS = 4;

    public:
        uint32_t nlines;
        uint32_t freeLines;
        TLLine_t *lines;

        TLSet_t(){
            this->nlines = this->N_WAYS;
            this->freeLines = this->nlines;
            this->lines = new TLLine_t[N_WAYS];
        }
};

#endif
