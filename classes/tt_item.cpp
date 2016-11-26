#include "tt_item.h"

unsigned long TT_Item::GetId() const { return this->id; }

void TT_Item::SetId(unsigned long i) {
    if (i > 0)
        this->id = i;
}
