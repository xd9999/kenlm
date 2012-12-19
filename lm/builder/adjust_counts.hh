#ifndef LM_BUILDER_ADJUST_COUNTS__
#define LM_BUILDER_ADJUST_COUNTS__

#include "lm/builder/discount.hh"
#include "util/exception.hh"

#include <vector>

#include <stdint.h>

namespace lm {
namespace builder {

class ChainPositions;

class BadDiscountException : public util::Exception {
  public:
    BadDiscountException() throw();
    ~BadDiscountException() throw();
};

/* Compute adjusted counts.  
 * Input: unique suffix sorted N-grams (and just the N-grams) with raw counts.
 * Output: [1,N]-grams with adjusted counts.  
 * [1,N)-grams are in suffix order
 * N-grams are in undefined order (they're going to be sorted anyway).
 */
class AdjustCounts {
  public:
    // For testing, allow bad discounts to be passed through.  
    AdjustCounts(std::vector<uint64_t> &counts, std::vector<Discount> &discounts, bool inspect_discounts = true)
      : counts_(counts), discounts_(discounts), inspect_discounts_(inspect_discounts) {}

    void Run(const ChainPositions &positions);

  private:
    std::vector<uint64_t> &counts_;
    std::vector<Discount> &discounts_;
    bool inspect_discounts_;
};

} // namespace builder
} // namespace lm

#endif // LM_BUILDER_ADJUST_COUNTS__

