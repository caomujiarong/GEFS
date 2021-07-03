#include <cstddef>
#include <cstdint>

namespace WS {

    struct BlockHeader
    {
        // union-ed with data
        BlockHeader* pNext;
    };
    
    struct PageHeader
    {
        PageHeader* pNext;
        BlockHeader* Blocks() {
            return reinterpret_cast<BlockHeader*>(this + 1);
        }
    };
    
    class Allocator
    {
    private:
#if defined(_DEBUG)
        // fill a free page with debug patterns
        void FillFreePage(PageHeader* pPage);

        // fill a block with debug patterns
        void FillFreeBlock(BlockHeader* pBlock);

        // fill an allocated block with debug patterns
        void FillAllocatedBlock(BlockHeader* pBlock);
#endif
        // get the next block
        BlockHeader* NextBlock(BlockHeader* pBlock);

        // the page list
        PageHeader* m_pPageList;

        // the free block list
        BlockHeader* m_pFreeList;

        size_t m_szDataSize;
        size_t m_szPageSize;
        size_t m_szAlignmentSize;
        size_t m_szBlockSize;
        size_t m_nBlockPerPage;

        // statistics
        uint32_t m_nPages;
        uint32_t m_nBlocks;
        uint32_t m_nFreeBlocks;

        // disable copy & assignment
        Allocator(const Allocator& clone);
        Allocator &operator=(const Allocator &rhs);
    public:
        Allocator(/* args */);
        ~Allocator();
    };    
}