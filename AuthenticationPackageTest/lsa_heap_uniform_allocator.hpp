#pragma once

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A uniform allocator for the LSA heap within a continuous memory block.
        /// </summary>
        class lsa_heap_uniform_allocator
        {
        public:
            lsa_heap_uniform_allocator(const LSA_SECPKG_FUNCTION_TABLE& table, size_t block_size) : lsa_heap_uniform_allocator{ table, block_size, false }
            {
            }

            lsa_heap_uniform_allocator(const LSA_SECPKG_FUNCTION_TABLE& table, size_t block_size, bool auto_free) : auto_free_{ auto_free }, table_ { table }, block_size_{ block_size }
            {
                base_address_ = static_cast<uint8_t*>(table_.AllocateLsaHeap(static_cast<uint32_t>(block_size_)));
                current_ptr_ = base_address_;
            }

            virtual ~lsa_heap_uniform_allocator()
            {
                if (auto_free_ && base_address_ != nullptr)
                {
                    table_.FreeLsaHeap(base_address_);
                }

                current_ptr_ = nullptr;
                base_address_ = nullptr;
            }

            /// <summary>
            /// Get the allocated size.
            /// </summary>
            /// <returns>The allocated size</returns>
            inline size_t size() const
            {
                return current_ptr_ - base_address_;
            }

            /// <summary>
            /// Allocate a structure and zero the memory block.
            /// </summary>
            /// <returns>The allocated structure</returns>
            template<typename TAny>
            inline TAny* allocate_zero()
            {
                return allocate_zero<TAny>(sizeof(TAny));
            }

            /// <summary>
            /// Allocate a structure with additional data and zero the memory block.
            /// </summary>
            /// <param name="additional_size">The additional data size</param>
            /// <returns>The allocated structure</returns>
            template<typename TAny>
            TAny* allocate_zero_extra(size_t additional_size)
            {
                return allocate_zero<TAny>(sizeof(TAny) + additional_size);
            }
            
            /// <summary>
            /// Allocate a memory block and zero it.
            /// </summary>
            /// <param name="size">The block size</param>
            /// <returns>The allocated memory block</returns>
            template<typename TAny>
            TAny* allocate_zero(size_t size)
            {
                if (current_ptr_ + size >= base_address_ + block_size_)
                {
                    return nullptr;
                }

                // Zero the memory block.
                auto allocated_ptr = current_ptr_;
                memset(allocated_ptr, 0, size);
                current_ptr_ += size;

                return reinterpret_cast<TAny*>(allocated_ptr);
            }
        protected:
            LSA_SECPKG_FUNCTION_TABLE table_;
        private:
            bool auto_free_;
            size_t block_size_;
            uint8_t* current_ptr_;
            uint8_t* base_address_;
        };
    }
}
