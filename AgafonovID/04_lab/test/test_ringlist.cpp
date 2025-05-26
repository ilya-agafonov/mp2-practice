#include <gtest.h>
#include "RingList.h"

TEST(RingList, can_create_empty_ring_list) {
    ASSERT_NO_THROW(RingList<int> l);
}
