#ifndef UTIL_ALLOCATOR_H
#define UTIL_ALLOCATOR_H


#include "Exception.h"
#include <iostream>
#include <memory>
#include <vector>


namespace util
{

    template< typename T, size_t Exponent = 12 >
    class Allocator
    {

    public:
        using Pointer = T*;

        static constexpr size_t TypeSize = sizeof( T );
        static constexpr size_t Alignment = 16;
        static constexpr size_t HashReserve = 256;


        Allocator( size_t size )
        {
            ASSERT( size != 0, "Can not create pool pool with zero size." );

            size = ( size + 15 ) & ~0x0F; // get the next multiple of 16
            head_ = static_cast< Pointer >( aligned_alloc( 16, size ) );

            ASSERT( head_, "Error! Can not allocate memory of size " + std::to_string( size ) + " for Allocator." );

            next_ = head_;
            tail_ = head_ + size;

            for ( auto&& entry : cache_ )
            {
                entry.reserve( HashReserve );
            }
        }

        ~Allocator()
        {
            for ( auto& entry : cache_ )
            {
                entry.clear();
            }
            std::free( head_ );
        }

        Pointer get( size_t size )
        {
            ASSERT( size != 0, "Can not allocate memory of zero size in Allocator." );

            size_t chunkExponent = getChunkSize( size );
            size_t chunk = 1 << chunkExponent;

            Pointer ptr = nullptr;
            
            // Check if there is an allocated space with the correct size
            if ( !cache_[chunkExponent].empty() )
            {
                // in the memory cache, if so return the address
                ptr = cache_[chunkExponent].back();
                cache_[chunkExponent].pop_back();
            }
            else
            {
                // If there is no cache for that size, check if we still have enough
                // memory left in the pool, if not, default to malloc
                if ( next_ + chunk >= tail_ )
                {
                    ptr = static_cast< Pointer >( aligned_alloc( 16, chunk * sizeof( double ) ) );
                }
                else
                {
                    // Otherwise, return pointer from pool
                    ptr = next_;
                    next_ += chunk;
                }
            }

            return ptr;
        }

        void release( Pointer ptr, size_t size )
        {
            if ( ptr >= head_ && ptr < tail_ )
            {
                // Put freed memory to the cache if it was allocated by the pool
                size_t chunkExponent = getChunkSize( size );
                cache_[chunkExponent].push_back( ptr );
            }
            else
            {
                // Otherwise just call free
                std::free( ptr );
            }
        }

    private:
        static constexpr size_t MaxExponent = Exponent;

        using List = std::vector< Pointer >;
        using Cache = std::array< List, MaxExponent >;

        Pointer head_ = nullptr;

        Pointer tail_ = nullptr;

        Pointer next_ = nullptr;

        Cache cache_;


        static inline size_t getChunkSize( size_t size )
        {
            // @todo: This can be optimised a lot with bit tricks:
            // http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
            size--;
            size_t r = 1;
            while ( size >>= 1 ) // unroll for more speed...
            {
                r++;
            }

            // we want memory to be aligned to 16 bytes or two doubles so the minimum exponent is 4
            r = std::max( r, 4UL );
            return r;
        }
    };
}

#endif // UTIL_ALLOCATOR_H
